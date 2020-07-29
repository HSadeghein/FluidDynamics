#pragma once
#include "glm/glm.hpp"

namespace FluidEngine
{
	class Light
	{
	public:
		Light(glm::vec3 position, glm::vec4 color, float specularStrength, float ambientStrength) : m_Direction(position),
			m_Color(color), m_SpecularStrength(specularStrength), m_AmbientStrength(ambientStrength) {}
			~Light() {}

			inline void SetLightDirection(glm::vec3 direction) { m_Direction = direction; }
			inline void SetLightColor(glm::vec4 color) { m_Color = color; }
			inline void SetSpecularStrength(float specStrength) { m_SpecularStrength = specStrength; }
			inline void SetAmbientStrength(float ambientStrength) { m_AmbientStrength = ambientStrength; }
			inline glm::vec3 LightDirection() { return m_Direction; }
			inline glm::vec4 LightColor() { return m_Color; }
			inline float SpecularStrength() { return m_SpecularStrength; }
			inline float AmbientStrength() { return m_AmbientStrength; }
	private:
		glm::vec3 m_Direction;
		glm::vec4 m_Color;
		float m_SpecularStrength;
		float m_AmbientStrength;
	};
}