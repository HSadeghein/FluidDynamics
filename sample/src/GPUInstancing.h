#pragma once
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Mesh.h"
#include "Material.h"

#define VERTEX_ATTRIB_VB 0
#define WORLD_MATRIX_VB 1

namespace FluidEngine
{
	class GPUInstancing
	{
	public:
		GPUInstancing(int instanceNumber, Mesh* mesh, std::shared_ptr<Material> material);
		~GPUInstancing();
		void OnUpdate(glm::mat4 projection, glm::mat4 view);
		void UpdateMaterial(glm::vec3 cameraPosition);
		void Draw();

	private:
		int m_InstanceNumber;
		std::unique_ptr<VertexBuffer> m_VertexBuffers[2];
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<VertexArray> m_VertexArray;
		std::unique_ptr<BufferLayout> m_BufferLayout;
		std::shared_ptr<Material> m_Material;
		std::vector<glm::mat4> m_Worlds;
	};
}