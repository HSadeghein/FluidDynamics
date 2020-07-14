#include "pch.h"
#include "OrthogonalCamera.h"

namespace FluidEngine
{
	glm::mat4 OrthogonalCamera::CalcViewMatrix()
	{
		return glm::translate(glm::mat4(1.0f), -m_Position);
	}

	glm::mat4 OrthogonalCamera::CalcProjectionMatrix()
	{
		return glm::ortho(m_Left, m_Right, m_Down, m_Up, m_Near, m_Far);
	}
}