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

	void Material::CompileRunShaders()
	{
		m_Shader->CreateShaderProgram();
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

	void Material::BindTexture(unsigned int slot)
	{
		m_Texture->Bind(slot);
	}
}