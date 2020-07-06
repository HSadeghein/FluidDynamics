#pragma once
#include <windows.h>

using namespace std;

namespace FluidEngine {

	class ShaderLanConverter {
	public:
		ShaderLanConverter() {}
		ShaderLanConverter(LPCWSTR glslangDir, LPCWSTR spirvCrossDir, LPCWSTR sourceName, LPCWSTR targetSPVName, LPCWSTR targetName);
		~ShaderLanConverter() {}
		virtual void ConvertToSPVFrom(LPWSTR inputParams) = 0;
		virtual void ConvertWithExeFromSPVTo(LPWSTR inputParams) = 0;
		virtual void ConvertWithAPIFromSPVTo() = 0;

		LPCWSTR m_GlslangExecuteDirection;
		LPCWSTR m_SpirvCrossExecuteDirection;
		LPCWSTR m_SourceFileName;
		LPCWSTR m_TargetSPVName;
		LPCWSTR m_TargetFileName;
	};
}
