#include "ExceptionHandler.hpp"

#include "StackTrace.hpp"

namespace YimMenu
{
	// Unity's filter, captured when we install ours. We chain to it after logging so
	// UnityCrashHandler64.exe still gets to write its minidump and show the crash UI.
	static LPTOP_LEVEL_EXCEPTION_FILTER g_PreviousFilter = nullptr;

	ExceptionHandler::ExceptionHandler()
	{
		LOG(INFO) << "ExceptionHandler initialized";
		m_OldErrorMode   = SetErrorMode(0);
		m_Handler        = SetUnhandledExceptionFilter(&UnhandledExceptionHandler);
		g_PreviousFilter = m_Handler;
	}

	ExceptionHandler::~ExceptionHandler()
	{
		SetErrorMode(m_OldErrorMode);
		SetUnhandledExceptionFilter(m_Handler);
		g_PreviousFilter = nullptr;
	}

	LONG WINAPI UnhandledExceptionHandler(EXCEPTION_POINTERS* exception_info)
	{
		const auto code = exception_info->ExceptionRecord->ExceptionCode;
		if (code == EXCEPTION_BREAKPOINT || code == DBG_PRINTEXCEPTION_C || code == DBG_PRINTEXCEPTION_WIDE_C)
			return EXCEPTION_CONTINUE_SEARCH;

		static StackTrace trace;
		trace.NewStackTrace(exception_info);
		LOG(FATAL) << trace;
		Logger::FlushQueue();

		if (g_PreviousFilter)
			return g_PreviousFilter(exception_info);

		return EXCEPTION_CONTINUE_SEARCH;
	}
}
