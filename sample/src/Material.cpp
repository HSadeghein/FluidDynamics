#include "pch.h"
#include "Renderer.h"
#include "Material.h"

namespace FluidEngine
{
	Material::Material()
	{
		m_Shader = std::make_unique<ShaderControler>();
	}

	Material::~Material()
	{
		std::cout << "matrial is destroyed" << std::endl;
	}

	void Material::AppendVertexShader(std::string filePath)
	{
		m_Shader->AddShader({ filePath.c_str(), GL_VERTEX_SHADER, true });
	}

	void Material::AppendPixelShader(std::string filePath)
	{
		m_Shader->AddShader({ filePath.c_str(), GL_FRAGMENT_SHADER, true });
	}

	void Material::CompileShaders()
	{
		m_Shader->CreateShaderProgram();	
	}

	void Material::RunShader()
	{
		m_Shader->UseShaderProgram();
	}

	void Material::Blend(unsigned int src, unsigned int dest)
	{
		GL_CHECK_ERROR(glBlendFunc(src, dest));
		GL_CHECK_ERROR(glEnable(GL_BLEND));
	}

	void Material::SetTexture(const char* path, const char* texName, int texSlot, bool invert)
	{
		m_Texture = std::make_unique<Texture>(path, invert);
		m_Texture->Bind(texSlot);
		m_Shader->SetUniformInt(texName, texSlot);
	}

	void Material::SetColor(const std::string& blockName, std::vector<float> color)
	{
		m_Shader->SetUniformBlockBindingFloat(blockName.c_str(), color, 1);
	}

	void Material::SetUniformMat4(const std::string& uniformName, const glm::mat4 matrix)
	{
		m_Shader->SetUniformMat4(uniformName.c_str(), matrix);
	}

	void Material::SetUniformBool(const std::string& uniformName, const bool value)
	{
		m_Shader->SetUniformBool(uniformName, value);
	}

	void Material::SetUniformFloat(const std::string& uniformName, const float value)
	{
		m_Shader->SetUniformFloat(uniformName, value);
	}

	void Material::SetUniformFloat2(const std::string& uniformName, const glm::vec2 value)
	{
		m_Shader->SetUniformFloat2(uniformName, value);
	}

	void Material::SetUniformFloat3(const std::string& uniformName, const glm::vec3 value)
	{
		m_Shader->SetUniformFloat3(uniformName, value);
	}

	void Material::SetUniformFloat4(const std::string& uniformName, const glm::vec4 value)
	{
		m_Shader->SetUniformFloat4(uniformName, value);
	}

	void Material::BindTexture(unsigned int slot)
	{
		m_Texture->Bind(slot);
	}

	void Material::GetRenderID()
	{
		std::cout << m_Shader->RenderID() << std::endl;
	}
}