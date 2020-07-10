#pragma once
#include <vector>
#include <Windows.h>
#include "HlslToGlslConverter.h"
#include <iostream>
#include "UniformBuffer.h"

namespace FluidEngine {

	struct Shader {
		const char* filename;
		unsigned int shaderType;
		bool checkError;
	};

	class ShaderControler {
	public:
		ShaderControler();
		~ShaderControler();
		void AddShader(Shader shader);
		void CreateShaderProgram();
		void UseShaderProgram();
		void ConvAllHlslToGlsl();
		void SetUniformBlockBindingFloat(const char* blockName, std::vector<float> data);
		void SetUniformInt(const char* name, int value);
	private:
		unsigned int LoadCompileShader(Shader shader);
		void ConvHlslToGlsl(LPCWSTR sourceName, LPCWSTR targetSPVName, LPCWSTR targetName, LPCWSTR glslangArgs[2],
			LPCWSTR spirvArgs[2]);

		std::vector<unsigned int> shaders;
		std::unique_ptr<UniformBuffer> m_UniformBuffer;
		unsigned int m_RenderID;
		std::unique_ptr<HlslToGlslConverter> m_HlslToGlslConverter;
		LPCWSTR glslangExeDir = L"..\\vendors\\SPIRV-Cross\\external\\glslang-build\\output\\bin\\glslangValidator.exe";
		LPCWSTR spirvCrossExeDir = L"..\\vendors\\SPIRV-Cross\\build\\Debug\\spirv-cross.exe";
	};
}