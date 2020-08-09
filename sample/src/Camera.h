#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/rotate_vector.hpp"

namespace FluidEngine
{
	enum CameraType
	{
		Orthogonal,
		Perspective
	};

	class Camera
	{
	public:
		Camera(glm::vec3 pos, CameraType type) : m_Position(glm::vec3(pos)), m_CameraType(type) {}
		~Camera() {}
		virtual glm::mat4 CalcViewMatrix() = 0;
		virtual glm::mat4 CalcProjectionMatrix() = 0;

		inline glm::vec3 Position() { return m_Position; }
		inline CameraType GetCameraType() { return m_CameraType; }
		inline void SetPosition(glm::vec3 position) { m_Position = position;}
		inline void SetCameraType(CameraType type) { m_CameraType = type; }
		inline glm::vec3 GetCameraPosition() { return m_Position; }

	protected:
		CameraType m_CameraType;
		glm::vec3 m_Position;
	};

}
