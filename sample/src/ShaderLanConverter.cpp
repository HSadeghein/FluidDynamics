#include "ShaderLanConverter.h"

namespace FluidEngine {
	ShaderLanConverter::ShaderLanConverter(LPCWSTR glslangDir, LPCWSTR spirvCrossDir, LPCWSTR sourceName, LPCWSTR targetSPVName, LPCWSTR targetName) {
		m_GlslangExecuteDirection = glslangDir;
		m_SpirvCrossExecuteDirection = spirvCrossDir;
		m_SourceFileName = sourceName;
		m_TargetSPVName = targetSPVName;
		m_TargetFileName = targetName;
	}
}