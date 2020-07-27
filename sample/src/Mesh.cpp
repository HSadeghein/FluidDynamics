#include "pch.h"
#include "Mesh.h"

namespace FluidEngine
{
	Mesh::Mesh(GeometryGenerator::MeshData& meshData)
	{
		m_MeshData = meshData;
	}
}