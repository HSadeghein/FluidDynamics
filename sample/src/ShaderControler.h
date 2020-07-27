#pragma once
#include <vector>
#include <Windows.h>
#include <iostream>
#include <unordered_map>
#include "HlslToGlslConverter.h"
#include "UniformBuffer.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

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
		void SetUniformBlockBindingFloat(const char* blockName, std::vector<float> data, unsigned int binding);
		void SetUniformBlockBindingMat4(const char* blockName, glm::mat4 data, unsigned int binding);
		void SetUniformInt(const char* name, int value);
		void SetUniformMat4(const char* name, glm::mat4 value);
		void SetUniformBool(const std::string& uniformName, const bool value);
		int GetUniformBlockIndex(std::string blockName);
		int GetUniformLocation(std::string blockName);
		inline int RenderID() { return m_RenderID; }
	private:
		unsigned int LoadCompileShader(Shader shader);
		void ConvHlslToGlsl(LPCWSTR sourceName, LPCWSTR targetSPVName, LPCWSTR targetName, LPCWSTR glslangArgs[2],
			LPCWSTR spirvArgs[2]);

		unsigned int m_RenderID;
		std::vector<unsigned int> shaders;
		std::unordered_map<std::string, int> uniformBlockCache;
		std::unordered_map<std::string, int> uniformCache;
		std::unique_ptr<UniformBuffer> m_UniformBuffer;
		std::unique_ptr<HlslToGlslConverter> m_HlslToGlslConverter;
		LPCWSTR glslangExeDir = L"..\\vendors\\SPIRV-Cross\\external\\glslang-build\\output\\bin\\glslangValidator.exe";
		LPCWSTR spirvCrossExeDir = L"..\\vendors\\SPIRV-Cross\\build\\Debug\\spirv-cross.exe";
	};
}