#pragma once
#include "ShaderLanConverter.h"

namespace FluidEngine {
    class HlslToGlslConverter : public ShaderLanConverter {
    public:
        HlslToGlslConverter() {}
        HlslToGlslConverter(LPCWSTR glslangDir, LPCWSTR spirvCrossDir, LPCWSTR sourceName, LPCWSTR targetSPVName, LPCWSTR targetName)
            : ShaderLanConverter(glslangDir, spirvCrossDir, sourceName, targetSPVName, targetName) {}
        ~HlslToGlslConverter() {}
        virtual void ConvertToSPVFrom(LPWSTR inputParams);
        virtual void ConvertWithExeFromSPVTo(LPWSTR inputParams);
        void ConvertWithAPIFromSPVTo();
    };
 }
