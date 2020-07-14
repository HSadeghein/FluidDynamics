#pragma once
#include "Camera.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace FluidEngine
{
	class OrthogonalCamera : public Camera {
	public:
		OrthogonalCamera(glm::vec3 pos, CameraType type, float left, float right, float down, float up) : m_Left(left), m_Right(right),
			m_Up(up), m_Down(down), m_Near(-1.0), m_Far(1.0), Camera(pos, type) { }
		~OrthogonalCamera() { }
		glm::mat4 CalcViewMatrix() override;
		glm::mat4 CalcProjectionMatrix() override;

	protected:
		float m_Left, m_Right, m_Up, m_Down, m_Near, m_Far;
	};
}