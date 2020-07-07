#pragma once
#include <vector>
#include "Renderer.h"

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
		unsigned int LoadCompileShader(Shader shader);
		void AddShader(Shader shader);
		void CreateShaderProgram();
		void UseShaderProgram();
	private:
		std::vector<unsigned int> shaders;
		unsigned int m_RenderID;
	};
}