#include "pch.h"
#include "Renderer.h"
#include <vector>
#include "Texture.h"

void GlClearErrors()
{
	while (glGetError() != GL_NO_ERROR);
}

bool GlDisplayError()
{
	while (GLenum error = glGetError())
	{
		std::cout << error << std::endl;
		return false;
	}
	return true;
}

namespace FluidEngine
{
	Renderer::Renderer(const std::vector<GeometryGenerator::Vertex> vertices, const std::vector<unsigned int> indices)
	{
		m_Timer.Reset();
		std::vector<float> v;
		for (auto& x : vertices)
		{
			v.push_back(x.Position.x);
			v.push_back(x.Position.y);
			v.push_back(x.Position.z);
			v.push_back(x.Normal.x);
			v.push_back(x.Normal.y);
			v.push_back(x.Normal.z);
			v.push_back(x.Tangent.x);
			v.push_back(x.Tangent.y);
			v.push_back(x.Tangent.z);
			v.push_back(x.UV.x);
			v.push_back(x.UV.y);
		}
		/*GL_CHECK_ERROR(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		GL_CHECK_ERROR(glEnable(GL_BLEND));*/
		m_VertexArray = std::make_unique<VertexArray>();
		m_VertexBuffer = std::make_unique<VertexBuffer>(&v[0], v.size() * sizeof(float));
		// position attribute
		//glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		//glEnableVertexAttribArray(0);
		// texture coord attribute
		//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(4 * sizeof(float)));
		//glEnableVertexAttribArray(1);
		m_BufferLayout = std::make_unique<BufferLayout>();
		m_BufferLayout->Push<float>(3);
		m_BufferLayout->Push<float>(3);
		m_BufferLayout->Push<float>(3);
		m_BufferLayout->Push<float>(2);
		m_VertexArray->AddBuffer(*m_BufferLayout, *m_VertexBuffer);
		m_IndexBuffer = std::make_unique<IndexBuffer>(&indices[0], indices.size());
		m_Shader = std::make_unique<ShaderControler>();
		//m_Shader->ConvAllHlslToGlsl();
		m_Shader->AddShader({ "shader/vertex.vert", GL_VERTEX_SHADER, true });
		m_Shader->AddShader({ "shader/pixel.frag", GL_FRAGMENT_SHADER, true });
		m_Shader->CreateShaderProgram();
		m_Shader->UseShaderProgram();
	}

	Renderer::~Renderer()
	{
		std::cout << "Renderer is destroyed" << std::endl;
	}

	void Renderer::SetColor(const std::string& blockName, std::vector<float> color)
	{
		m_Shader->SetUniformBlockBindingFloat(blockName.c_str(), color);
	}

	void Renderer::SetTexture(const char* path, const char* texName, int texSlot)
	{
		m_Texture = std::make_unique<Texture>(path);
		m_Texture->Bind(texSlot);
		//m_Shader->SetUniformInt(texName, texSlot);
	}

	void Renderer::Draw(ImGuiPanel& panel) const
	{

		m_VertexArray->Bind();
		m_Texture->Bind();
		m_IndexBuffer->Bind();
		GL_CHECK_ERROR(glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, 0));
		panel.DrawImgui();
	}

	void Renderer::Clear() const
	{
		GL_CHECK_ERROR(glClear(GL_COLOR_BUFFER_BIT));
	}

	void Renderer::Tick()
	{
		m_Timer.Tick();
	}

	void Renderer::CalculateFrameStats()
	{
		static int frameCount = 0;
		static float timeElapsed = 0;

		frameCount++;

		if ((m_Timer.TotalTime() - timeElapsed) >= 1.0f)
		{
			float fps = (float)frameCount;
			float mspf = 1000.0f / fps;

			Log::GetCoreLogger()->info("FPS is {}", fps);
			Log::GetCoreLogger()->info("Frame per milisecond is {}", mspf);

			frameCount = 0;
			timeElapsed += 1.0f;
		}
	}
}