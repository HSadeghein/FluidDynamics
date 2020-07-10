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



	}

}