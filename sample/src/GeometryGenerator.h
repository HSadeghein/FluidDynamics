#pragma once

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/glm.hpp>

#define PI 3.14

namespace FluidEngine
{
	class GeometryGenerator
	{
	public:

		struct Vertex
		{
			Vertex() {}

			Vertex(glm::vec3 position, glm::vec3 normal, glm::vec3 tangent, glm::vec2 uv) : Position(position),
				Normal(normal), Tangent(tangent), UV(uv)
			{

			}

			Vertex(float px, float py, float pz,
				   float nx, float ny, float nz,
				   float tx, float ty, float tz,
				   float u, float v) : Position(px, py, pz), Normal(nx, ny, nz),
				Tangent(tx, ty, tz), UV(u, v)
			{

			}
			glm::vec3 Position;
			glm::vec3 Normal;
			glm::vec3 Tangent;
			glm::vec2 UV;

		};

		struct MeshData
		{
			std::vector<Vertex> Vertices;
			std::vector<uint32_t> Indices;
		};
		GeometryGenerator()
		{

		}

		MeshData CreateBox(float width, float height, float depth, int numOfSubdivision);
		MeshData CreateSphere(float radius, int stackCount, int sectorCount);
		void Subdivide(MeshData& meshData);
	private:
		Vertex CreateMidPoint(const Vertex& v0, const Vertex& v1);
	};
}
