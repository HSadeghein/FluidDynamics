#include "pch.h"
#include "PerspectiveCamera.h"
#define PI 3.14f
#define DEG_RAD PI / 180

namespace FluidEngine
{
	glm::mat4 PerspectiveCamera::CalcViewMatrix()
	{
		if (m_PropertyCache["rotation"].x != m_Rotation.x)
		{
			float diffAngleX = m_Rotation.x - m_PropertyCache["rotation"].x;
			m_Forward = glm::rotateX(m_Forward, diffAngleX * DEG_RAD);
			m_PropertyCache["rotation"].x = m_Rotation.x;
		}
		if (m_PropertyCache["rotation"].y != m_Rotation.y)
		{
			float diffAngleY = m_Rotation.y - m_PropertyCache["rotation"].y;
			m_Forward = glm::rotateY(m_Forward, diffAngleY * DEG_RAD);
			m_PropertyCache["rotation"].y = m_Rotation.y;
		}
		if (m_PropertyCache["rotation"].z != m_Rotation.z)
		{
			float diffAngleZ = m_Rotation.z - m_PropertyCache["rotation"].z;
			m_Forward = glm::rotateZ(m_Forward, diffAngleZ * DEG_RAD);
			m_PropertyCache["rotation"].z = m_Rotation.z;
		}
		return glm::lookAt(m_Position, m_Position + m_Forward, m_Up);
	}

	glm::mat4 PerspectiveCamera::CalcProjectionMatrix()
	{
		return glm::perspective(m_FOV, m_AspectRatio, m_ZNear, m_ZFar);
	}
}