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
	Renderer::Renderer(Window* window)
	{
		m_WindowWidth = window->GetWidth();
		m_WindowHeight = window->GetHeight();
		m_ImguiPanel = std::make_unique<ImGuiPanel>(window->GetWindow());
		m_Timer.Reset();
		m_VertexArray = std::make_unique<VertexArray>();
		m_VertexBuffers[VERTEX_ATTRIB_VB] = std::make_unique<VertexBuffer>();
		m_VertexBuffers[WVP_MATRIX_VB] = std::make_unique<VertexBuffer>();
		m_VertexBuffers[WORLD_MATRIX_VB] = std::make_unique<VertexBuffer>();
		m_BufferLayout = std::make_unique<BufferLayout>();
		m_BufferLayout->Push<float>(3);
		m_BufferLayout->Push<float>(3);
		m_BufferLayout->Push<float>(3);
		m_BufferLayout->Push<float>(2);
		m_VertexArray->AddBuffer(*m_BufferLayout, *m_VertexBuffers[VERTEX_ATTRIB_VB]);
		int nextID = m_BufferLayout->GetElements().size();
		m_BufferLayout->Clear();
		for (int i = 0; i < 4; i++)
		{
			m_BufferLayout->Push<float>(4);
		}
		m_VertexArray->AddBuffer(nextID, *m_BufferLayout, *m_VertexBuffers[WVP_MATRIX_VB]);
		nextID += m_BufferLayout->GetElements().size();
		m_BufferLayout->Clear();
		for (int i = 0; i < 4; i++)
		{
			m_BufferLayout->Push<float>(4);
		}
		m_VertexArray->AddBuffer(nextID, *m_BufferLayout, *m_VertexBuffers[WORLD_MATRIX_VB]);
	}

	Renderer::~Renderer()
	{
		std::cout << "Renderer is destroyed" << std::endl;
	}

	void Renderer::RenderImgui(Window* window)
	{
		m_ImguiPanel->RenderImguiFrame(window, m_Objects, m_Camera.get());
	}

	void Renderer::InstertObject(Object* object)
	{
		m_Objects.push_back(object);
	}

	Material* Renderer::CreateMaterial(std::string vertexShader, std::string pixelShader, std::string texturePath, glm::vec4 color)
	{
		std::unique_ptr<Material> material = std::make_unique<Material>();
		m_Materials.push_back(std::move(material));
		m_Materials[m_Materials.size() - 1]->AppendVertexShader(vertexShader);
		m_Materials[m_Materials.size() - 1]->AppendPixelShader(pixelShader);
		m_Materials[m_Materials.size() - 1]->CompileRunShaders();
		m_Materials[m_Materials.size() - 1]->SetTexture(texturePath.c_str(), "SPIRV_Cross_CombinedshaderTexturesampleType", 0, false);
		m_Materials[m_Materials.size() - 1]->SetColor("ColorBuffers", std::vector<float>{color.r, color.g, color.b, color.a});
		m_Materials[m_Materials.size() - 1]->Blend(GL_ONE, GL_ZERO);
		m_Materials[m_Materials.size() - 1]->BindTexture(0);
		return m_Materials[m_Materials.size() - 1].get();
	}

	void Renderer::SetUpGPUInstancing(Mesh* mesh, int instanceNumber)
	{
		InstantiateInstanceTransforms(instanceNumber);
		SetUpInstancingBuffers(mesh);
	}

	void Renderer::InstantiateInstanceTransforms(int instanceNumber)
	{
		m_InstanceNumber = instanceNumber;
		for (int i = 0; i < instanceNumber; i++)
		{
			Transform transform(glm::vec3(-11 * i, 0, 0), glm::vec3(0.0), glm::vec3(1.0));
			m_Worlds.push_back(transform.CalcTransformMatrix());
			m_WVPs.push_back(m_Projection * m_View * transform.CalcTransformMatrix());
		}
	}

	void Renderer::SetUpInstancingBuffers(Mesh* mesh)
	{
		auto& vertices = mesh->Vertices();
		auto& indices = mesh->Indices();
		m_VertexBuffers[VERTEX_ATTRIB_VB]->Bind();
		m_VertexBuffers[VERTEX_ATTRIB_VB]->BufferData(sizeof(GeometryGenerator::Vertex) * vertices.size(), &vertices[0], GL_DYNAMIC_DRAW);
		m_IndexBuffer = std::make_unique<IndexBuffer>(&indices[0], indices.size());
	}

	void Renderer::UpdateTransforms()
	{
		m_Projection = m_Camera->CalcProjectionMatrix();
		m_View = m_Camera->CalcViewMatrix();
		for (int i = 0; i < m_InstanceNumber; i++)
		{
			m_WVPs[i] = m_Projection * m_View * m_Worlds[i];
		}
		m_VertexBuffers[WVP_MATRIX_VB]->Bind();
		m_VertexBuffers[WVP_MATRIX_VB]->BufferData(sizeof(glm::mat4) * m_WVPs.size(), &m_WVPs[0], GL_DYNAMIC_DRAW);
		m_VertexBuffers[WORLD_MATRIX_VB]->Bind();
		m_VertexBuffers[WORLD_MATRIX_VB]->BufferData(sizeof(glm::mat4) * m_Worlds.size(), &m_Worlds[0], GL_DYNAMIC_DRAW);
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

	void Renderer::InstanceDraw() const
	{
		m_VertexArray->Bind();
		m_IndexBuffer->Bind();
		GL_CHECK_ERROR(glDrawElementsInstanced(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, 0, m_InstanceNumber));
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
}