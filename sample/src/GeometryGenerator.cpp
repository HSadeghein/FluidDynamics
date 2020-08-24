#include "pch.h"
#include "GeometryGenerator.h"

namespace FluidEngine
{
	GeometryGenerator::MeshData GeometryGenerator::CreateBox(float width, float height, float depth, int numOfSubdivision)
	{
		MeshData meshData;

		//Create vertices

		Vertex v[24];

		float w = width * 0.5f;
		float h = height * 0.5f;
		float d = depth * 0.5f;
		//***********************
		//Clockwise
		//***********************
		float w2 = 0.5f * width;
		float h2 = 0.5f * height;
		float d2 = 0.5f * depth;

		// Fill in the front face vertex data.
		v[0] = Vertex(-w2, -h2, -d2, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
		v[1] = Vertex(-w2, +h2, -d2, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
		v[2] = Vertex(+w2, +h2, -d2, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
		v[3] = Vertex(+w2, -h2, -d2, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);

		// Fill in the back face vertex data.
		v[4] = Vertex(-w2, -h2, +d2, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
		v[5] = Vertex(+w2, -h2, +d2, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
		v[6] = Vertex(+w2, +h2, +d2, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
		v[7] = Vertex(-w2, +h2, +d2, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f);

		// Fill in the top face vertex data.
		v[8] = Vertex(-w2, +h2, -d2, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
		v[9] = Vertex(-w2, +h2, +d2, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
		v[10] = Vertex(+w2, +h2, +d2, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
		v[11] = Vertex(+w2, +h2, -d2, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);

		// Fill in the bottom face vertex data.
		v[12] = Vertex(-w2, -h2, -d2, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
		v[13] = Vertex(+w2, -h2, -d2, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
		v[14] = Vertex(+w2, -h2, +d2, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
		v[15] = Vertex(-w2, -h2, +d2, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f);

		// Fill in the left face vertex data.
		v[16] = Vertex(-w2, -h2, +d2, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
		v[17] = Vertex(-w2, +h2, +d2, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
		v[18] = Vertex(-w2, +h2, -d2, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
		v[19] = Vertex(-w2, -h2, -d2, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);

		// Fill in the right face vertex data.
		v[20] = Vertex(+w2, -h2, -d2, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f);
		v[21] = Vertex(+w2, +h2, -d2, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
		v[22] = Vertex(+w2, +h2, +d2, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
		v[23] = Vertex(+w2, -h2, +d2, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);

		meshData.Vertices.assign(&v[0], &v[24]);

		uint32_t i[36];

		// Fill in the front face index data
		i[0] = 0;
		i[1] = 1;
		i[2] = 2;
		i[3] = 0;
		i[4] = 2;
		i[5] = 3;

		// Fill in the back face index data
		i[6] = 4;
		i[7] = 5;
		i[8] = 6;
		i[9] = 4;
		i[10] = 6;
		i[11] = 7;

		// Fill in the top face index data
		i[12] = 8;
		i[13] = 9;
		i[14] = 10;
		i[15] = 8;
		i[16] = 10;
		i[17] = 11;

		// Fill in the bottom face index data
		i[18] = 12;
		i[19] = 13;
		i[20] = 14;
		i[21] = 12;
		i[22] = 14;
		i[23] = 15;

		// Fill in the left face index data
		i[24] = 16;
		i[25] = 17;
		i[26] = 18;
		i[27] = 16;
		i[28] = 18;
		i[29] = 19;

		// Fill in the right face index data
		i[30] = 20;
		i[31] = 21;
		i[32] = 22;
		i[33] = 20;
		i[34] = 22;
		i[35] = 23;
		meshData.Indices.assign(&i[0], &i[36]);

		for (int i = 0; i < numOfSubdivision; i++)
		{
			Subdivide(meshData);
		}

		return meshData;
	}

	GeometryGenerator::MeshData GeometryGenerator::CreateSphere(float radius, int stackCount, int sectorCount)
	{
		MeshData meshData;
		std::vector<Vertex> vertices;
		float x, y, z, xz, nx, ny, nz, tx, ty, tz, u, v;
		float inv_rad = 1.0 / radius;
		float thetaStep = 2 * PI / sectorCount;
		float phiStep = PI / stackCount;
		float phi, theta;

		Vertex northPoleVertex(glm::vec3(0, radius, 0), glm::vec3(0, 1, 0), glm::vec3(1, 0, 0), glm::vec2(0));
		Vertex southPoleVertex(glm::vec3(0, -radius, 0), glm::vec3(0, -1, 0), glm::vec3(-1, 0, 0), glm::vec2(0, 1));

		vertices.push_back(northPoleVertex);
		for (int i = 1; i <= stackCount - 1; i++)
		{
			phi = phiStep * (float)i;
			for (int j = 0; j <= sectorCount; j++)
			{
				theta = j * thetaStep;
				x = radius * glm::sin(phi) * glm::cos(theta);
				y = radius * glm::cos(phi);
				z = radius * glm::sin(phi) * glm::sin(theta);

				tx = -radius * glm::sin(phi) * glm::sin(theta);
				ty = 0;
				tz = radius * glm::sin(phi) * glm::cos(theta);
				glm::vec3 tangent = glm::normalize(glm::vec3(tx, ty, tz));

				nx = x * inv_rad;
				ny = y * inv_rad;
				nz = -z * inv_rad;
				glm::vec3 normal = glm::normalize(glm::vec3(nx, ny, nz));

				v = (float)i / stackCount;
				u = (float)j / sectorCount;

				vertices.push_back(Vertex(glm::vec3(x, y, z), normal, tangent, glm::vec2(u, v)));
			}
		}
		vertices.push_back(southPoleVertex);

		meshData.Vertices.assign(vertices.begin(), vertices.end());
		std::vector<int> indices;

		for (int i = 1; i <= sectorCount; i++)
		{
			indices.push_back(0);
			indices.push_back(i);
			indices.push_back(i + 1);
		}

		int baseIndex = 1;
		int ringVertex = sectorCount + 1;
		for (int i = 0; i < stackCount - 2; i++)
		{
			for (int j = 0; j < sectorCount; j++)
			{
				indices.push_back(baseIndex + ringVertex * i + j);
				indices.push_back(baseIndex + ringVertex * (i + 1) + j);
				indices.push_back(baseIndex + ringVertex * i + j + 1);

				indices.push_back(baseIndex + ringVertex * i + j + 1);
				indices.push_back(baseIndex + ringVertex * (i + 1) + j);
				indices.push_back(baseIndex + ringVertex * (i + 1) + j + 1);
			}
		}

		int southPoleIndex = meshData.Vertices.size() - 1;
		baseIndex = southPoleIndex - ringVertex;
		for (int i = 0; i < sectorCount; i++)
		{
			indices.push_back(southPoleIndex);
			indices.push_back(baseIndex + i + 1);
			indices.push_back(baseIndex + i);
		}

		meshData.Indices.assign(indices.begin(), indices.end());
		return meshData;
	}

	void GeometryGenerator::Subdivide(MeshData &meshData)
	{
		//				v1
		//			   /  \
		//			  /	   \
		//			m0-----m1
		//          /		 \
		//         /		  \
		//		  v0----m2----v2

		std::cout << "HI";
		MeshData meshDataCopy = meshData;

		meshData.Vertices.resize(0);
		meshData.Indices.resize(0);

		uint32_t numTris = (uint32_t)meshDataCopy.Indices.size() / 3;
		for (uint32_t i = 0; i < numTris; i++)
		{
			Vertex v0 = meshDataCopy.Vertices[meshDataCopy.Indices[3 * i + 0]];
			Vertex v1 = meshDataCopy.Vertices[meshDataCopy.Indices[3 * i + 1]];
			Vertex v2 = meshDataCopy.Vertices[meshDataCopy.Indices[3 * i + 2]];

			Vertex m0 = CreateMidPoint(v0, v1);
			Vertex m1 = CreateMidPoint(v1, v2);
			Vertex m2 = CreateMidPoint(v0, v2);

			meshData.Vertices.push_back(v0); //0
			meshData.Vertices.push_back(v1); //1
			meshData.Vertices.push_back(v2); //2
			meshData.Vertices.push_back(m0); //3
			meshData.Vertices.push_back(m1); //4
			meshData.Vertices.push_back(m2); //5

			meshData.Indices.push_back(i * 6 + 0);
			meshData.Indices.push_back(i * 6 + 3);
			meshData.Indices.push_back(i * 6 + 5);

			meshData.Indices.push_back(i * 6 + 3);
			meshData.Indices.push_back(i * 6 + 1);
			meshData.Indices.push_back(i * 6 + 4);

			meshData.Indices.push_back(i * 6 + 5);
			meshData.Indices.push_back(i * 6 + 3);
			meshData.Indices.push_back(i * 6 + 4);

			meshData.Indices.push_back(i * 6 + 5);
			meshData.Indices.push_back(i * 6 + 4);
			meshData.Indices.push_back(i * 6 + 2);
		}
	}

	GeometryGenerator::Vertex GeometryGenerator::CreateMidPoint(const Vertex &v0, const Vertex &v1)
	{
		glm::vec3 pos0 = v0.Position;
		glm::vec3 pos1 = v1.Position;

		glm::vec3 norm0 = v0.Normal;
		glm::vec3 norm1 = v1.Normal;

		glm::vec3 tan0 = v0.Tangent;
		glm::vec3 tan1 = v1.Tangent;

		glm::vec2 tex0 = v0.UV;
		glm::vec2 tex1 = v1.UV;

		glm::vec3 midPos = 0.5f * (pos0 + pos1);
		glm::vec3 midNorm = glm::normalize(0.5f * (norm0 + norm1));
		glm::vec3 midTang = glm::normalize(0.5f * (tan0 + tan1));
		glm::vec2 midTex = 0.5f * (tex1 + tex0);

		Vertex v(midPos, midNorm, midTang, midTex);

		return v;
	}

} // namespace FluidEngine