#include "StackTrace.hpp"
#include <winternl.h>
#include <DbgHelp.h>

namespace YimMenu
{
	StackTrace::StackTrace() :
	    m_FramePointers(32)
	{
		// IL2CPP (GameAssembly.dll) calls SymInitialize for its own native stack capture,
		// so ours can return FALSE if it got there first. Refresh the module list so
		// modules loaded after IL2CPP's init (including ours) get covered.
		if (!SymInitialize(GetCurrentProcess(), nullptr, TRUE))
			SymRefreshModuleList(GetCurrentProcess());
	}

	StackTrace::~StackTrace()
	{
		// Intentionally no SymCleanup — DbgHelp state is shared with IL2CPP and
		// tearing it down on DLL unload would crash IL2CPP's own stack-trace path.
	}

	const std::vector<uint64_t>& StackTrace::GetFramePointers()
	{
		return m_FramePointers;
	}

	void StackTrace::NewStackTrace(EXCEPTION_POINTERS* exception_info)
	{
		// static std::mutex m;
		// std::lock_guard lock(m);

		m_ExceptionInfo = exception_info;

		m_Dump << ExceptionCodeToString(exception_info->ExceptionRecord->ExceptionCode) << '\n';

		DumpModuleInfo();
		DumpStacktrace();
		DumpCPPExceptionInfo();

		m_Dump << "\n--------End of exception--------\n";
	}

	std::string StackTrace::GetString() const
	{
		return m_Dump.str();
	}

	// I'd prefer to make some sort of global instance that cache all modules once instead of doing this every time
	void StackTrace::DumpModuleInfo()
	{
		// modules cached already
		if (m_Modules.size())
			return;

		m_Dump << "Dumping modules:\n";

		const auto peb = reinterpret_cast<PPEB>(NtCurrentTeb()->ProcessEnvironmentBlock);
		if (!peb)
			return;

		const auto ldr_data = peb->Ldr;
		if (!ldr_data)
			return;

		const auto module_list = &ldr_data->InMemoryOrderModuleList;
		auto module_entry      = module_list->Flink;
		for (; module_list != module_entry; module_entry = module_entry->Flink)
		{
			const auto table_entry = CONTAINING_RECORD(module_entry, LDR_DATA_TABLE_ENTRY, InMemoryOrderLinks);
			if (!table_entry)
				continue;

			if (table_entry->FullDllName.Buffer)
			{
				auto mod_info = ModuleInfo(table_entry->FullDllName.Buffer, table_entry->DllBase);

				m_Dump << mod_info.m_Path.filename().string() << " Base Address: " << HEX(mod_info.m_Base)
				       << " Size: " << mod_info.m_Size << '\n';

				m_Modules.emplace_back(std::move(mod_info));
			}
		}
	}

	void StackTrace::DumpStacktrace()
	{
		m_Dump << "Dumping stacktrace:";
		GrabStacktrace();

		// alloc once
		char buffer[sizeof(SYMBOL_INFO) + MAX_SYM_NAME];
		auto symbol          = reinterpret_cast<SYMBOL_INFO*>(buffer);
		symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
		symbol->MaxNameLen   = MAX_SYM_NAME;

		DWORD64 displacement64;
		DWORD displacement;


		IMAGEHLP_LINE64 line;
		line.SizeOfStruct = sizeof(IMAGEHLP_LINE64);

		for (size_t i = 0; i < m_FramePointers.size() && m_FramePointers[i]; ++i)
		{
			const auto addr = m_FramePointers[i];

			m_Dump << "\n[" << i << "]\t";
			if (SymFromAddr(GetCurrentProcess(), addr, &displacement64, symbol))
			{
				if (SymGetLineFromAddr64(GetCurrentProcess(), addr, &displacement, &line))
				{
					m_Dump << line.FileName << " L: " << line.LineNumber << " " << std::string_view(symbol->Name, symbol->NameLen);

					continue;
				}
				const auto module_info = GetModuleByAddress(addr);

				if (module_info->m_Base == (uint64_t)GetModuleHandle(0))
					m_Dump << module_info->m_Path.filename().string() << " " << std::string_view(symbol->Name, symbol->NameLen) << " ("
					       << module_info->m_Path.filename().string() << "+" << HEX(addr - module_info->m_Base) << ")";
				else
					m_Dump << module_info->m_Path.filename().string() << " " << std::string_view(symbol->Name, symbol->NameLen);

				continue;
			}
			const auto module_info = GetModuleByAddress(addr);
			m_Dump << module_info->m_Path.filename().string() << "+" << HEX(addr - module_info->m_Base) << " " << HEX(addr);
		}
	}

	void StackTrace::DumpCPPExceptionInfo()
	{
		constexpr DWORD msvc_exception_code = 0xe06d7363;
		if (m_ExceptionInfo->ExceptionRecord->ExceptionCode == msvc_exception_code)
		{
			m_Dump
			    << reinterpret_cast<const std::exception*>(m_ExceptionInfo->ExceptionRecord->ExceptionInformation[1])->what() << '\n';
		}
	}

	void StackTrace::GrabStacktrace()
	{
		CONTEXT context = *m_ExceptionInfo->ContextRecord;

		STACKFRAME64 frame{};
		frame.AddrPC.Mode      = AddrModeFlat;
		frame.AddrFrame.Mode   = AddrModeFlat;
		frame.AddrStack.Mode   = AddrModeFlat;
		frame.AddrPC.Offset    = context.Rip;
		frame.AddrFrame.Offset = context.Rbp;
		frame.AddrStack.Offset = context.Rsp;

		for (size_t i = 0; i < m_FramePointers.size(); ++i)
		{
			if (!StackWalk64(IMAGE_FILE_MACHINE_AMD64, GetCurrentProcess(), GetCurrentThread(), &frame, &context, nullptr, SymFunctionTableAccess64, SymGetModuleBase64, nullptr))
			{
				break;
			}
			m_FramePointers[i] = frame.AddrPC.Offset;
		}
	}

	const StackTrace::ModuleInfo* StackTrace::GetModuleByAddress(uint64_t addr) const
	{
		for (auto& mod_info : m_Modules)
		{
			if (mod_info.m_Base < addr && addr < mod_info.m_Base + mod_info.m_Size)
			{
				return &mod_info;
			}
		}
		return nullptr;
	}

	std::string StackTrace::ExceptionCodeToString(const DWORD code)
	{
#define MAP_PAIR_STRINGIFY(x) \
	{                         \
		x, #x                 \
	}
		static const std::map<DWORD, std::string> exceptions = {MAP_PAIR_STRINGIFY(EXCEPTION_ACCESS_VIOLATION), MAP_PAIR_STRINGIFY(EXCEPTION_ARRAY_BOUNDS_EXCEEDED), MAP_PAIR_STRINGIFY(EXCEPTION_DATATYPE_MISALIGNMENT), MAP_PAIR_STRINGIFY(EXCEPTION_FLT_DENORMAL_OPERAND), MAP_PAIR_STRINGIFY(EXCEPTION_FLT_DIVIDE_BY_ZERO), MAP_PAIR_STRINGIFY(EXCEPTION_FLT_INEXACT_RESULT), MAP_PAIR_STRINGIFY(EXCEPTION_FLT_INEXACT_RESULT), MAP_PAIR_STRINGIFY(EXCEPTION_FLT_INVALID_OPERATION), MAP_PAIR_STRINGIFY(EXCEPTION_FLT_OVERFLOW), MAP_PAIR_STRINGIFY(EXCEPTION_FLT_STACK_CHECK), MAP_PAIR_STRINGIFY(EXCEPTION_FLT_UNDERFLOW), MAP_PAIR_STRINGIFY(EXCEPTION_ILLEGAL_INSTRUCTION), MAP_PAIR_STRINGIFY(EXCEPTION_IN_PAGE_ERROR), MAP_PAIR_STRINGIFY(EXCEPTION_INT_DIVIDE_BY_ZERO), MAP_PAIR_STRINGIFY(EXCEPTION_INT_OVERFLOW), MAP_PAIR_STRINGIFY(EXCEPTION_INVALID_DISPOSITION), MAP_PAIR_STRINGIFY(EXCEPTION_NONCONTINUABLE_EXCEPTION), MAP_PAIR_STRINGIFY(EXCEPTION_PRIV_INSTRUCTION), MAP_PAIR_STRINGIFY(EXCEPTION_STACK_OVERFLOW), MAP_PAIR_STRINGIFY(EXCEPTION_BREAKPOINT), MAP_PAIR_STRINGIFY(EXCEPTION_SINGLE_STEP)};

		if (const auto& it = exceptions.find(code); it != exceptions.end())
			return it->second;

		return "UNKNOWN_EXCEPTION: CODE: " + std::to_string(code);
	}
}
