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
		//Front Face
		v[0] = Vertex(-w, -h, -d, 0., 0., -1., 1., 0., 0., 0., 1.);
		v[1] = Vertex(-w, h, -d, 0., 0., -1., 1., 0., 0., 0., 0.);
		v[2] = Vertex(w, h, -d, 0., 0., -1, 1., 0., 0., 1., 0.);
		v[3] = Vertex(w, -h, -d, 0., 0., -1., 1., 0., 0., 1., 1.);
		//Back Face
		v[4] = Vertex(w, -h, d, 0., 0., 1., -1., 0., 0., 1., 1.);
		v[5] = Vertex(-w, -h, d, 0., 0., 1., -1., 0., 0., 0., 1.);
		v[6] = Vertex(-w, h, d, 0., 0., 1, -1., 0., 0., 0., 0.);
		v[7] = Vertex(w, h, d, 0., 0., 1., -1., 0., 0., 1., 0.);
		//Top Face
		v[8] = Vertex(-w, h, -d, 0., 1., 0., 1., 0., 0., 0., 1.);
		v[9] = Vertex(-w, h, d, 0., 1., 0., 1., 0., 0., 0., 0.);
		v[10] = Vertex(w, h, d, 0., 1., 0, 1., 0., 0., 1., 0.);
		v[11] = Vertex(-w, h, -d, 0., 1., 0., 1., 0., 0., 1., 1.);
		//Bottom Face
		v[12] = Vertex(-w, -h, -d, 0., -1., 0., -1., 0., 0., 1., 1.);
		v[13] = Vertex(w, -h, -d, 0., -1., 0., -1., 0., 0., 0., 1.);
		v[14] = Vertex(w, -h, d, 0., -1., 0, -1., 0., 0., 0., 0.);
		v[15] = Vertex(-w, -h, d, 0., -1., 0., -1., 0., 0., 1., 0.);
		//Left Face
		v[16] = Vertex(-w, -h, d, -1., 0., 0., 0., 0., -1., 0., 1.);
		v[17] = Vertex(-w, h, d, -1., 0., 0., 0., 0., -1., 0., 0.);
		v[18] = Vertex(-w, h, -d, -1., 0., 0., 0., 0., -1., 1., 0.);
		v[19] = Vertex(-w, -h, -d, -1., 0., 0., 0., 0., -1., 1., 1.);
		//Right Face
		v[20] = Vertex(w, -h, -d, 1., 0., 0., 0., 0., 1., 0., 1.);
		v[21] = Vertex(w, h, -d, 1., 0., 0., 0., 0., 1., 0., 0.);
		v[22] = Vertex(w, h, d, 1., 0., 0, 0., 0., 1., 1., 0.);
		v[23] = Vertex(w, -h, d, 1., 0., 0., 0., 0., 1., 1., 1.);

		meshData.Vertices.assign(&v[0], &v[24]);

		uint32_t i[36];

		//Fill in the front face
		i[0] = 0; i[1] = 1; i[2] = 2;
		i[3] = 0; i[4] = 2; i[5] = 3;

		//Fill in the back face
		i[6] = 4; i[7] = 5; i[8] = 6;
		i[9] = 4; i[10] = 6; i[11] = 7;

		//Fill in the top face
		i[12] = 8; i[13] = 9; i[14] = 10;
		i[15] = 8; i[16] = 10; i[17] = 11;

		//Fill in the bottom face
		i[18] = 12; i[19] = 13; i[20] = 14;
		i[21] = 12; i[22] = 14; i[23] = 15;

		//Fill in the left side
		i[24] = 16; i[25] = 17; i[26] = 18;
		i[27] = 16; i[28] = 18; i[29] = 19;

		//Fill in the right side
		i[30] = 20; i[31] = 21; i[32] = 22;
		i[33] = 20; i[34] = 22; i[35] = 23;

		meshData.Indices.assign(&i[0], &i[36]);


		for (int i = 0; i < numOfSubdivision; i++)
		{
			Subdivide(meshData);
		}

		return meshData;
	}

	void GeometryGenerator::Subdivide(MeshData& meshData)
	{
		//				v1
		//			   /  \
		//			  /	   \
		//			m0-----m1
		//          /		 \
		//         /		  \
		//		  v0----m2----v2



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

	GeometryGenerator::Vertex GeometryGenerator::CreateMidPoint(const Vertex& v0, const Vertex& v1)
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

}