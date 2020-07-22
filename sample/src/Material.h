#pragma once
#include "ShaderControler.h"
#include "Texture.h"

namespace FluidEngine
{
	class Material
	{
	public:
		Material();
		~Material();
		void AppendVertexShader(std::string filePath);
		void AppendPixelShader(std::string filePath);
		void CompileRunShaders();
		void Blend(unsigned int dest, unsigned int src);
		void SetTexture(const char* path, const char* texName, int texSlot, bool invert);
		void SetColor(const std::string& blockName, std::vector<float> color);
		void BindTexture(unsigned int slot = 0);

	private:
		std::unique_ptr<ShaderControler> m_Shader;
		std::unique_ptr<Texture> m_Texture;
	};
}