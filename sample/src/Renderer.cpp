#include "pch.h"
#include "Renderer.h"

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

namespace FluidEngine {
	Renderer::Renderer()
	{
		m_Timer.Reset();
	}

	void Renderer::Draw(VertexArray& va, IndexBuffer& ib, ImGuiPanel& panel) const
	{
		va.Bind();
		ib.Bind();
		GL_CHECK_ERROR(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, 0));
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