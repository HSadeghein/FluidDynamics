#pragma once
#include <unordered_map>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace FluidEngine
{
	class Transform
	{
	public:
		Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
		~Transform() {}
		
		glm::mat4 CalcTransformMatrix();
		inline glm::vec3 Position() { return m_Position; } 
		inline glm::vec3 Rotation() { return m_Rotation; }
		inline glm::vec3 Scale() { return m_Scale; }
		inline void SetPosition(glm::vec3 position) { m_Position = position; }
		inline void SetRotation(glm::vec3 rotation) { m_Rotation = rotation; }
		inline void SetScale(glm::vec3 scale) { m_Scale = scale; }
	private:
		glm::vec3 m_Position;
		glm::vec3 m_Rotation;
		glm::vec3 m_Scale;
		glm::mat4 m_Transform;
		std::unordered_map<std::string, glm::vec3> m_TransformCache;
	};
}
