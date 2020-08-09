#include "pch.h"
#include "ShaderControler.h"
#include "Renderer.h" 
#include<iostream>

namespace FluidEngine {

	ShaderControler::ShaderControler()
	{
		m_UniformBuffer = std::make_unique<UniformBuffer>();
	}

	ShaderControler::~ShaderControler()
	{
		GL_CHECK_ERROR(glDeleteProgram(m_RenderID));
		std::cout << "Shader Controller is destroyed" << std::endl;
	}

	unsigned int ShaderControler::LoadCompileShader(Shader shader)
	{
		unsigned int result = 0;
		FILE* fp;
		size_t filesize;
		char* data;
		fp = fopen(shader.filename, "rb");
		if (!fp)
			return 0;
		fseek(fp, 0, SEEK_END);
		filesize = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		data = new char[filesize + 1];
		if (!data)
			return 0;
		fread(data, 1, filesize, fp);
		data[filesize] = 0;
		fclose(fp);
		result = glCreateShader(shader.shaderType);
		if (!result)
			return 0;
		GL_CHECK_ERROR(glShaderSource(result, 1, &data, NULL));
		delete[] data;
		data = nullptr;

		GL_CHECK_ERROR(glCompileShader(result));
		if (shader.checkError)
		{
			int status = 0;
			GL_CHECK_ERROR(glGetShaderiv(result, GL_COMPILE_STATUS, &status));
			if (status == GL_FALSE)
			{
				int length;
				GL_CHECK_ERROR(glGetShaderiv(result, GL_INFO_LOG_LENGTH, &length));
				char* message = (char*)alloca(length * sizeof(char));
				GL_CHECK_ERROR(glGetShaderInfoLog(result, length, &length, message));
				std::cout << "failed to compile a shader !" << std::endl;
				std::cout << message << std::endl;
				GL_CHECK_ERROR(glDeleteShader(result));
				return 0;
			}
		}
		return result;
	}

	void ShaderControler::AddShader(Shader shader)
	{
		shaders.push_back(LoadCompileShader(shader));
	}

	void ShaderControler::CreateShaderProgram()
	{
		m_RenderID = glCreateProgram();
		for (unsigned int shader : shaders) 
		{
			GL_CHECK_ERROR(glAttachShader(m_RenderID, shader));
		}
		GL_CHECK_ERROR(glLinkProgram(m_RenderID));
		GL_CHECK_ERROR(glValidateProgram(m_RenderID));
		for (unsigned int shader : shaders)
		{
			GL_CHECK_ERROR(glDeleteShader(shader));
		}
	}

	void ShaderControler::UseShaderProgram()
	{
		GL_CHECK_ERROR(glUseProgram(m_RenderID));
	}

	void ShaderControler::ConvHlslToGlsl(LPCWSTR sourceName, LPCWSTR targetSPVName, LPCWSTR targetName, LPCWSTR glslangArgs[2],
		LPCWSTR spirvArgs[2])
	{
		m_HlslToGlslConverter = std::make_unique<HlslToGlslConverter>(glslangExeDir, spirvCrossExeDir, sourceName,
			targetSPVName, targetName);
		std::wstring wparams = glslangArgs[0] + std::wstring(m_HlslToGlslConverter->m_TargetSPVName) + glslangArgs[1] + std::wstring(m_HlslToGlslConverter->m_SourceFileName);
		m_HlslToGlslConverter->ConvertToSPVFrom(&wparams[0]);
		wparams = spirvArgs[0] + std::wstring(m_HlslToGlslConverter->m_TargetSPVName) + spirvArgs[1] + std::wstring(m_HlslToGlslConverter->m_TargetFileName);
		m_HlslToGlslConverter->ConvertWithExeFromSPVTo(&wparams[0]);
	}

	void ShaderControler::ConvAllHlslToGlsl()
	{
		LPCWSTR glslangArgs[2] = { L"glslangValidator.exe -S vert -e main -o ", L" -V -D " };
		LPCWSTR spirvArgs[2] = { L"spirv-cross.exe --version 330 --no-es ", L" --output " };
		ConvHlslToGlsl(L"shader\\VertexShader-v.hlsl", L"shader\\vertex.spv", L"shader\\vertex.vert", glslangArgs, spirvArgs);
		glslangArgs[0] = L"glslangValidator.exe -S frag -e main -o ";
		glslangArgs[1] = L" -V -D ";
		spirvArgs[0] = L"spirv-cross.exe --version 450 --no-es ";
		spirvArgs[1] = L" --output ";
		ConvHlslToGlsl(L"shader\\PixelShader-p.hlsl", L"shader\\pixel.spv", L"shader\\pixel.frag", glslangArgs, spirvArgs);
	}

	void ShaderControler::SetUniformBlockBindingFloat(const char* blockName, std::vector<float> data, unsigned int binding)
	{
		int blockIndex = GetUniformBlockIndex(blockName);
		GL_CHECK_ERROR(glUniformBlockBinding(m_RenderID, blockIndex, binding));
		m_UniformBuffer->Bind(&data[0], sizeof(float) * data.size(), binding);
	}

	void ShaderControler::SetUniformBlockBindingMat4(const char* blockName, glm::mat4 data, unsigned int binding)
	{
		int blockIndex = GetUniformBlockIndex(blockName);
		GL_CHECK_ERROR(glUniformBlockBinding(m_RenderID, blockIndex, binding));
		m_UniformBuffer->Bind(&data[0][0], sizeof(glm::mat4), binding);
	}

	void ShaderControler::SetUniformInt(const char* name, int value)
	{
		int location = GetUniformLocation(name);
		GL_CHECK_ERROR(glUniform1i(location, value));
	}

	void ShaderControler::SetUniformMat4(const char* name, glm::mat4 value)
	{
		int location = GetUniformLocation(name);
		GL_CHECK_ERROR(glUniformMatrix4fv(location, 1, false, &value[0][0]));
	}

	void ShaderControler::SetUniformBool(const std::string& uniformName, const bool value)
	{
		int location = GetUniformLocation(uniformName);
		GL_CHECK_ERROR(glUniform1i(location, value));
	}

	void ShaderControler::SetUniformFloat(const std::string& uniformName, const float value)
	{
		int location = GetUniformLocation(uniformName);
		GL_CHECK_ERROR(glUniform1f(location, value));
	}

	void ShaderControler::SetUniformFloat2(const std::string& uniformName, const glm::vec2 value)
	{
		int location = GetUniformLocation(uniformName);
		GL_CHECK_ERROR(glUniform2f(location, value.x, value.y));
	}

	void ShaderControler::SetUniformFloat3(const std::string& uniformName, const glm::vec3 value)
	{
		int location = GetUniformLocation(uniformName);
		GL_CHECK_ERROR(glUniform3f(location, value.x, value.y, value.z));
	}

	void ShaderControler::SetUniformFloat4(const std::string& uniformName, const glm::vec4 value)
	{
		int location = GetUniformLocation(uniformName);
		GL_CHECK_ERROR(glUniform4f(location, value.x, value.y, value.z, value.w));
	}

	int ShaderControler::GetUniformBlockIndex(std::string blockName)
	{
		if(uniformBlockCache.find(blockName) != uniformBlockCache.end())
		{
			return uniformBlockCache[blockName];
		}
		GL_CHECK_ERROR(unsigned int blockIndex = glGetUniformBlockIndex(m_RenderID, blockName.c_str()));
		ASSERT(blockIndex != GL_INVALID_INDEX);
		uniformBlockCache[blockName] = blockIndex;
		return blockIndex;
	}

	int ShaderControler::GetUniformLocation(std::string uniformName)
	{
		if (uniformCache.find(uniformName) != uniformCache.end())
		{
			return uniformCache[uniformName];
		}
		GL_CHECK_ERROR(int location = glGetUniformLocation(m_RenderID, uniformName.c_str()));
		ASSERT(location != GL_INVALID_INDEX);
		uniformCache[uniformName] = location;
		return location;
	}
}