#pragma once
#include<iostream>

namespace FluidEngine
{
	class Texture {
	public:
		Texture(const std::string& filePath, bool invert);
		~Texture();
		void Bind(unsigned int slot = 0) const;
		void Unbind(unsigned int slot = 0) const;

		inline const int Width() const { return m_Width; }
		inline const int Height() const { return m_Height; }
	private:
		unsigned int m_RenderID;
		std::string m_FilePath;
		unsigned char* m_LocalBuffer;
		int m_Width, m_Height, m_BPP;
	};
}
