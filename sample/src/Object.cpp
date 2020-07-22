#include "pch.h"
#include "Object.h"
#include <stdlib.h>
#include <time.h>

namespace FluidEngine
{
	Object::Object(GeometryGenerator::MeshData meshData, std::string name)
	{
		srand(time(NULL));
		m_Name = name;
		m_Mesh = std::make_unique<Mesh>(meshData);
		m_Transform = std::make_unique<Transform>(glm::vec3(0), glm::vec3(0), glm::vec3(1));
	}

	Object::~Object()
	{
		std::cout << "object is deleted." << std::endl;
	}
}