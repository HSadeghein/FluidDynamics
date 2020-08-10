#pragma once
#include "Camera.h"
#include <unordered_map>

namespace FluidEngine
{
	class PerspectiveCamera : public Camera
	{
	public:
		PerspectiveCamera(glm::vec3 pos, CameraType type, float aspect, float fov, float zNear, float zFar, glm::vec3 rotation)
			: m_AspectRatio(aspect), m_FOV(fov), m_ZNear(zNear), m_ZFar(zFar), m_Forward(glm::vec3(0, 0, 1)), m_Right(glm::vec3(-1, 0, 0)),
			m_Up(glm::vec3(0, 1, 0)), m_Rotation(rotation), Camera(pos, type)
		{
		}
		~PerspectiveCamera() {}
		glm::mat4 CalcViewMatrix() override;
		glm::mat4 CalcProjectionMatrix() override;

		inline float AspectRatio() { return m_AspectRatio; }
		inline float FOV() { return m_FOV; }
		inline float ZNear() { return m_ZNear; }
		inline float ZFar() { return m_ZFar; }
		inline glm::vec3 GetForward() { return m_Forward; }
		inline glm::vec3 GetUp() { return m_Up; }
		inline glm::vec3 GetRotation() { return m_Rotation; }
		inline glm::vec3 GetRight() { return m_Right; }
		inline void SetAspectRatio(float ratio) { m_AspectRatio = ratio; }
		inline void SetFOV(float fov) { m_FOV = fov; }
		inline void SetZNear(float zNear) { m_ZNear = zNear; }
		inline void SetZFar(float zFar) { m_ZFar = zFar; }
		inline void SetForward(glm::vec3 forward) { m_Forward = forward; }
		inline void SetUp(glm::vec3 up) { m_Up = up; }
		inline void SetRight(glm::vec3 right) { m_Right = right; }
		inline void SetRotation(glm::vec3 rotation) { m_Rotation = rotation; }
	protected:
		float m_AspectRatio, m_FOV, m_ZNear, m_ZFar;
		glm::vec3 m_Forward, m_Up, m_Rotation, m_Right;
		std::unordered_map<std::string, glm::vec3> m_PropertyCache;
	};
}