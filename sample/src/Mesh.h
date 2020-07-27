#pragma once
#include <iostream>
#include <vector>
#include "GeometryGenerator.h"

namespace FluidEngine
{
	class Mesh {
	public:
		Mesh(GeometryGenerator::MeshData& meshData);
		~Mesh() {}

		inline const std::vector<uint32_t> Indices() const { return m_MeshData.Indices; }
		inline const std::vector<GeometryGenerator::Vertex> Vertices() const { return m_MeshData.Vertices; }
	private:
		GeometryGenerator::MeshData m_MeshData;
	};
}