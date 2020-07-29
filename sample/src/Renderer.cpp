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
	}

	Renderer::~Renderer()
	{
		std::cout << "Renderer is destroyed" << std::endl;
	}

	void Renderer::RenderImgui(Window* window)
	{
		m_ImguiPanel->RenderImguiFrame(window, m_Camera.get());
	}

	std::shared_ptr<Material> Renderer::CreateMaterial(std::string nameID, std::string vertexShader, std::string pixelShader, std::string texturePath, glm::vec4 color, bool isInstancing)
	{
		std::shared_ptr<Material> material = std::make_shared<Material>();
		m_Materials[nameID] = std::move(material);
		m_Materials[nameID]->AppendVertexShader(vertexShader);
		m_Materials[nameID]->AppendPixelShader(pixelShader);
		m_Materials[nameID]->CompileShaders();
		m_Materials[nameID]->RunShader();
		m_Materials[nameID]->SetInstancing(isInstancing);
		m_Materials[nameID]->SetColor(color);
		if (texturePath != "")
		{
			m_Materials[nameID]->SetTexture(texturePath.c_str(), "_sampler", 0, false);
			m_Materials[nameID]->BindTexture(0);
		}
		m_Materials[nameID]->Blend(GL_ONE, GL_ZERO);
		m_Materials[nameID]->SetUniformFloat("ambientStrength", m_Light->AmbientStrength());
		m_Materials[nameID]->SetUniformFloat("specularStrength", m_Light->SpecularStrength());
		m_Materials[nameID]->SetUniformFloat3("lightDirection", m_Light->LightPosition());
		m_Materials[nameID]->SetUniformFloat3("cameraPosition", m_Camera->Position());
		m_Materials[nameID]->SetUniformFloat4("lightColor", m_Light->LightColor());
		return m_Materials[nameID];
	}

	void Renderer::SetUpGPUInstancing(Mesh* mesh, int instanceNumber, std::shared_ptr<Material> material)
	{
		std::unique_ptr<GPUInstancing> gpuInstancing = std::make_unique<GPUInstancing>(instanceNumber, mesh, material);
		m_GPUInstancings.push_back(std::move(gpuInstancing));
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

	void Renderer::SetLight(glm::vec3 position, glm::vec4 color, float ambientStrength, float specularStrength)
	{
		m_Light = std::make_unique<Light>(position, color, ambientStrength, specularStrength);
	}

	void Renderer::Draw()
	{
		
		m_Projection = m_Camera->CalcProjectionMatrix();
		m_View = m_Camera->CalcViewMatrix();
		for (auto& gpuInstancing : m_GPUInstancings)
		{
			gpuInstancing->UpdateMaterial();
			gpuInstancing->OnUpdate(m_Projection, m_View);
			gpuInstancing->Draw();
		}
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