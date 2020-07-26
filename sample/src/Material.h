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
		void CompileShaders();
		void RunShader();
		void Blend(unsigned int dest, unsigned int src);
		void SetTexture(const char* path, const char* texName, int texSlot, bool invert);
		void SetColor(const std::string& blockName, std::vector<float> color);
		void SetUniformMat4(const std::string& uniformName, const glm::mat4 matrix);
		void SetUniformBool(const std::string& uniformName, const bool value);
		void BindTexture(unsigned int slot = 0);
		void GetRenderID();

		inline void SetTexturePath(std::string texturePath) { m_TexturePath = texturePath; }
		inline void SetColor(glm::vec4 color) { m_Color = color; }
		inline void SetInstancing(bool isInstancing) { m_IsInstancing = isInstancing; }
		inline glm::vec4 Color() { return m_Color; }
		inline bool IsInstancing() { return m_IsInstancing; }
	private:
		std::unique_ptr<ShaderControler> m_Shader;
		std::unique_ptr<Texture> m_Texture;
		std::string m_TexturePath;
		glm::vec4 m_Color;
		bool m_IsInstancing;
	};
}