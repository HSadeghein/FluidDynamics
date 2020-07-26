#include "pch.h"
#include "Object.h"
#include <stdlib.h>
#include <time.h>
#include "Renderer.h"

namespace FluidEngine
{
	Object::Object(Mesh* mesh, std::string name, std::shared_ptr<Material> material)
	{
		srand(time(NULL));
		m_Name = name;
		m_Mesh = std::unique_ptr<Mesh>(mesh);
		m_Transform = std::make_unique<Transform>(glm::vec3(0), glm::vec3(0), glm::vec3(1));
		m_Material = std::shared_ptr<Material>(material);
		m_VertexArray = std::make_unique<VertexArray>();
		m_VertexBuffers = std::make_unique<VertexBuffer>();
		m_BufferLayout = std::make_unique<BufferLayout>();
		m_BufferLayout->Push<float>(3);
		m_BufferLayout->Push<float>(3);
		m_BufferLayout->Push<float>(3);
		m_BufferLayout->Push<float>(2);
		m_VertexArray->AddBuffer(*m_BufferLayout, *m_VertexBuffers);
		auto& vertices = mesh->Vertices();
		auto& indices = mesh->Indices();
		m_VertexBuffers->Bind();
		m_VertexBuffers->BufferData(sizeof(GeometryGenerator::Vertex) * vertices.size(), &vertices[0], GL_DYNAMIC_DRAW);
		m_IndexBuffer = std::make_unique<IndexBuffer>(&indices[0], indices.size());
		m_Material->SetUniformMat4("model", m_Transform->CalcTransformMatrix());
	}

	Object::~Object()
	{
		std::cout << "object is deleted." << std::endl;
	}

	void Object::Draw()
	{
		m_VertexArray->Bind();
		m_IndexBuffer->Bind();
		GL_CHECK_ERROR(glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, 0));
	}

	void Object::OnUpdate(glm::mat4 projection, glm::mat4 view)
	{
		m_Material->SetUniformMat4("projection", projection);
		m_Material->SetUniformMat4("view", view);
		
	}
}