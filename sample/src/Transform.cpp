#include "pch.h"
#include "Transform.h"
#define PI 3.14f
#define DEG_RAD PI / 180
namespace FluidEngine
{
	Transform::Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) : m_Position(position),
		m_Rotation(rotation), m_Scale(scale) { }

	glm::mat4 Transform::CalcTransformMatrix()
	{
		if (m_Position == m_TransformCache["position"] && m_Rotation == m_TransformCache["rotation"] 
			&& m_Scale == m_TransformCache["scale"])
		{
			return m_Transform;
		}
		m_TransformCache["position"] = m_Position;
		m_TransformCache["rotation"] = m_Rotation;
		m_TransformCache["scale"] = m_Scale;
		glm::mat4 transform = glm::translate(glm::mat4(1.0), m_Position);
		transform = glm::rotate(transform, m_Rotation.z * DEG_RAD , glm::vec3(0, 0, 1));
		transform = glm::rotate(transform, m_Rotation.y * DEG_RAD, glm::vec3(0, 1, 0));
		transform = glm::rotate(transform, m_Rotation.x * DEG_RAD, glm::vec3(1, 0, 0));
		transform = glm::scale(transform, m_Scale);
		m_Transform = transform;
		return m_Transform;
	}
}