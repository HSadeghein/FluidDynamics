#include "pch.h"
#include "GPUInstancing.h"
#include "Transform.h"
#include "Renderer.h"

namespace FluidEngine
{
	GPUInstancing::GPUInstancing(int instanceNumber, Mesh* mesh, std::shared_ptr<Material> material)
	{
		m_InstanceNumber = instanceNumber;
		m_Material = std::shared_ptr<Material>(material);
		m_VertexArray = std::make_unique<VertexArray>();
		m_VertexBuffers[VERTEX_ATTRIB_VB] = std::make_unique<VertexBuffer>();
		m_VertexBuffers[WORLD_MATRIX_VB] = std::make_unique<VertexBuffer>();
		m_BufferLayout = std::make_unique<BufferLayout>();
		m_BufferLayout->Push<float>(3);
		m_BufferLayout->Push<float>(3);
		m_BufferLayout->Push<float>(3);
		m_BufferLayout->Push<float>(2);
		m_VertexArray->AddBuffer(*m_BufferLayout, *m_VertexBuffers[VERTEX_ATTRIB_VB]);
		int nextID = m_BufferLayout->GetElements().size();
		m_BufferLayout->Clear();
		for (int i = 0; i < 4; i++)
		{
			m_BufferLayout->Push<float>(4);
		}
		m_VertexArray->AddBuffer(nextID, *m_BufferLayout, *m_VertexBuffers[WORLD_MATRIX_VB]);

		for (int i = 0; i < instanceNumber; i++)
		{
			Transform transform(glm::vec3(i * 10, 0, 0), glm::vec3(0.0), glm::vec3(1.0));
			m_Worlds.push_back(transform.CalcTransformMatrix());
		}
		auto& vertices = mesh->Vertices();
		auto& indices = mesh->Indices();
		m_VertexBuffers[VERTEX_ATTRIB_VB]->Bind();
		m_VertexBuffers[VERTEX_ATTRIB_VB]->BufferData(sizeof(GeometryGenerator::Vertex) * vertices.size(), &vertices[0], GL_DYNAMIC_DRAW);
		m_IndexBuffer = std::make_unique<IndexBuffer>(&indices[0], indices.size());
		m_VertexBuffers[WORLD_MATRIX_VB]->Bind();
		m_VertexBuffers[WORLD_MATRIX_VB]->BufferData(sizeof(glm::mat4) * m_Worlds.size(), &m_Worlds[0], GL_DYNAMIC_DRAW);
	}

	GPUInstancing::~GPUInstancing()
	{
		std::cout << "GPU Instancing is deleted" << std::endl;
	}

	void GPUInstancing::OnUpdate(glm::mat4 projection, glm::mat4 view)
	{
		m_Material->SetUniformMat4("projection", projection);
		m_Material->SetUniformMat4("view", view);
	}

	void GPUInstancing::UpdateMaterial()
	{
		m_Material->RunShader();
		glm::vec4 color = m_Material->Color();
		m_Material->SetColor("ColorBuffers", std::vector<float>{color.r, color.g, color.b, color.a});
		m_Material->SetUniformBool("isInstancing", m_Material->IsInstancing());
	}

	void GPUInstancing::Draw()
	{
		m_VertexArray->Bind();
		m_IndexBuffer->Bind();
		GL_CHECK_ERROR(glDrawElementsInstanced(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, 0, m_InstanceNumber));
	}
}