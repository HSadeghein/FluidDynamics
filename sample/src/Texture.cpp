#include "Texture.h" 
#include "stb_image/Stb_Image.h"
#include "Renderer.h"

namespace FluidEngine 
{
	Texture::Texture(const std::string& filePath) : 
		m_RenderID(0), m_FilePath(filePath), m_Width(0), m_Height(0), m_LocalBuffer(nullptr), m_BPP(0)
	{
		GL_CHECK_ERROR(glGenTextures(1, &m_RenderID));
		GL_CHECK_ERROR(glBindTexture(GL_TEXTURE_2D, m_RenderID));

		GL_CHECK_ERROR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
		GL_CHECK_ERROR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
		GL_CHECK_ERROR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GL_CHECK_ERROR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

		//stbi_set_flip_vertically_on_load(1);
		m_LocalBuffer = stbi_load("res/image/tex1.jpg", &m_Width, &m_Height, &m_BPP, 0);
		if (stbi_failure_reason())
			std::cout << stbi_failure_reason();
		GL_CHECK_ERROR(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_LocalBuffer));
		glGenerateMipmap(GL_TEXTURE_2D);
		GL_CHECK_ERROR(glBindTexture(GL_TEXTURE_2D, 0));
		if (m_LocalBuffer)
			stbi_image_free(m_LocalBuffer);
	}

	Texture::~Texture()
	{
		
		GL_CHECK_ERROR(glDeleteTextures(1, &m_RenderID));
		std::cout << "Texture is destroyed" << std::endl;
	}

	void Texture::Bind(unsigned int slot) const
	{
		GL_CHECK_ERROR(glActiveTexture(GL_TEXTURE0 + slot));
		GL_CHECK_ERROR(glBindTexture(GL_TEXTURE_2D, m_RenderID));
	}

	void Texture::Unbind(unsigned int slot) const
	{
		GL_CHECK_ERROR(glBindTexture(GL_TEXTURE_2D, 0));
	}
}