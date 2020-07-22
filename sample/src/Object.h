#pragma once
#include <iostream>
#include "Transform.h"
#include "Mesh.h"
#include "glm/glm.hpp"

namespace FluidEngine
{
	class Object
	{
	public:
		Object(GeometryGenerator::MeshData meshData, std::string name);
		~Object();

		inline const glm::mat4 ModelMatrix() const { return m_Transform->CalcTransformMatrix(); }
		inline const Mesh* GetMesh() const { return m_Mesh.get(); }
		inline Transform* GetTransform() const { return m_Transform.get(); }
		inline const std::string GetName() const { return m_Name; }

	protected:
		std::string m_Name;
		std::unique_ptr<Transform> m_Transform;
		std::unique_ptr<Mesh> m_Mesh;
	};
}
