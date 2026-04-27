#pragma once

namespace YimMenu
{
	class ExceptionHandler final
	{
	public:
		ExceptionHandler();
		virtual ~ExceptionHandler();

	private:
		LPTOP_LEVEL_EXCEPTION_FILTER m_Handler;
		uint32_t m_OldErrorMode;
	};

	extern LONG WINAPI UnhandledExceptionHandler(EXCEPTION_POINTERS* exception_info);
}
