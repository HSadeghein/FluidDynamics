cbuffer MatrixBuffer 
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};

struct VertexInput
{
	float4 position : Position;
};

struct FragmentInput
{
	float4 position : SV_Position;
};

FragmentInput main(VertexInput input) 
{
	FragmentInput output;
	output.position = input.position;
	return output;
}