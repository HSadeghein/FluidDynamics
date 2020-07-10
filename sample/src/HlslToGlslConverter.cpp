#include "pch.h"
#include "HlslToGlslConverter.h"


namespace FluidEngine {
	void HlslToGlslConverter::ConvertToSPVFrom(LPWSTR inputParams)
	{
		STARTUPINFO info = { sizeof(info) };
		PROCESS_INFORMATION processInfo;
		if (CreateProcess(m_GlslangExecuteDirection, inputParams,
			NULL, NULL, TRUE, 0, NULL, NULL, &info, &processInfo))
		{
			WaitForSingleObject(processInfo.hProcess, INFINITE);
			CloseHandle(processInfo.hProcess);
			CloseHandle(processInfo.hThread);
		}
	}

	void HlslToGlslConverter::ConvertWithExeFromSPVTo(LPWSTR inputParams)
	{
		STARTUPINFO info = { sizeof(info) };
		PROCESS_INFORMATION processInfo;
		if (CreateProcess(m_SpirvCrossExecuteDirection, inputParams,
			NULL, NULL, TRUE, 0, NULL, NULL, &info, &processInfo))
		{
			WaitForSingleObject(processInfo.hProcess, INFINITE);
			CloseHandle(processInfo.hProcess);
			CloseHandle(processInfo.hThread);
		}
	}

	void HlslToGlslConverter::ConvertWithAPIFromSPVTo() {

	}

}