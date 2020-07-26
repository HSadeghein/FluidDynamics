#pragma once
#include <iostream>
#include "Transform.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "Mesh.h"
#include "Material.h"
#include "glm/glm.hpp"

namespace FluidEngine
{
	class Object
	{
	public:
		Object(Mesh* mesh, std::string name, std::shared_ptr<Material> material);
		~Object();
		void Draw();
		void OnUpdate(glm::mat4 projection, glm::mat4 view);

		inline const glm::mat4 ModelMatrix() const { return m_Transform->CalcTransformMatrix(); }
		inline const Mesh* GetMesh() const { return m_Mesh.get(); }
		inline Transform* GetTransform() const { return m_Transform.get(); }
		inline const std::string GetName() const { return m_Name; }

	protected:
		std::string m_Name;
		std::unique_ptr<Transform> m_Transform;
		std::unique_ptr<Mesh> m_Mesh;
		std::shared_ptr<Material> m_Material;
		std::unique_ptr<VertexBuffer> m_VertexBuffers;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<VertexArray> m_VertexArray;
		std::unique_ptr<BufferLayout> m_BufferLayout;
	};
}
