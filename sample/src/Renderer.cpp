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
	Renderer::Renderer(const std::vector<GeometryGenerator::Vertex> vertices, const std::vector<unsigned int> indices, Window* window)
	{
		m_WindowWidth = window->GetWidth();
		m_WindowHeight = window->GetHeight();
		m_ImguiPanel = std::make_unique<ImGuiPanel>(window->GetWindow());
		m_Timer.Reset();
		const std::vector<float> verticesArray = ConvertVerticesToArray(vertices);
		m_VertexArray = std::make_unique<VertexArray>();
		m_VertexBuffer = std::make_unique<VertexBuffer>(&verticesArray[0], verticesArray.size() * sizeof(float));
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

	void Renderer::RenderImgui(Window* window)
	{
		m_ImguiPanel->RenderImguiFrame(window, m_Transform.get(), m_Camera.get());
	}

	const std::vector<float> Renderer::ConvertVerticesToArray(std::vector<GeometryGenerator::Vertex> vertices) const
	{
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
		return v;
	}

	void Renderer::SetCamera(CameraType cameraType)
	{
		if (cameraType == CameraType::Orthogonal)
		{
			float width = m_WindowWidth;
			float height = m_WindowHeight;
			m_Camera = std::make_unique<OrthogonalCamera>(glm::vec3(0), cameraType, -width / 2, width / 2,
				-height / 2, height / 2);
			m_View = m_Camera->CalcViewMatrix();
			m_Projection = m_Camera->CalcProjectionMatrix();
		}
		else
		{
			std::cout << "Wrong Camera Type" << std::endl;
			ASSERT(false);
		}
	}

	void Renderer::SetCamera(CameraType cameraType, float fov, float aspect, float zNear, float zFar)
	{
		if (cameraType == CameraType::Perspective)
		{
			m_Camera = std::make_unique<PerspectiveCamera>(glm::vec3(0, 0, -50), cameraType, aspect, fov, zNear, zFar, glm::vec3(0));
			m_View = m_Camera->CalcViewMatrix();
			m_Projection = m_Camera->CalcProjectionMatrix();
		}
		else
		{
			std::cout << "Wrong Camera Type" << std::endl;
			ASSERT(false);
		}
	}

	void Renderer::Model(const glm::vec3 translation, const glm::vec3 rotaion, const glm::vec3 scale)
	{
		m_Transform = std::make_unique<Transform>(translation, rotaion, scale);
		m_Model = m_Transform->CalcTransformMatrix();
	}

	void Renderer::MVP(const std::string& blockName)
	{
		m_Model = m_Transform->CalcTransformMatrix();
		m_View = m_Camera->CalcViewMatrix();
		m_Projection = m_Camera->CalcProjectionMatrix();
		if (m_Projection == prevTransforms["projection"] && m_Model == prevTransforms["model"] 
			&& m_View == prevTransforms["view"])
		{
			return;
		}
		prevTransforms["projection"] = m_Projection;
		prevTransforms["model"] = m_Model;
		prevTransforms["view"] = m_View;
		glm::mat4 mvp = m_Projection * m_View * m_Model;
		m_Shader->SetUniformBlockBindingMat4(blockName.c_str(), mvp, 0);
	}

	void Renderer::SetColor(const std::string& blockName, std::vector<float> color)
	{
		m_Shader->SetUniformBlockBindingFloat(blockName.c_str(), color, 1);
	}

	void Renderer::SetTexture(const char* path, const char* texName, int texSlot, bool invert)
	{
		m_Texture = std::make_unique<Texture>(path, invert);
		m_Texture->Bind(texSlot);
		m_Shader->SetUniformInt(texName, texSlot);
	}

	void Renderer::Draw() const
	{
		m_VertexArray->Bind();
		m_Texture->Bind();
		m_IndexBuffer->Bind();
		GL_CHECK_ERROR(glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, 0));
		m_ImguiPanel->DrawImgui();
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

	void Renderer::Blend(unsigned int src, unsigned int dest) {
		GL_CHECK_ERROR(glBlendFunc(src, dest));
		GL_CHECK_ERROR(glEnable(GL_BLEND));
	}
}