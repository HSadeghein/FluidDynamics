cbuffer MatrixBuffer 
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};

struct VertexInput
{
	float4 position : Position;
	float2 uv : TEXCOORD0;
};

struct FragmentInput
{
	float4 position : SV_Position;
	float2 uv : TEXCOORD0;
};

FragmentInput main(VertexInput input) 
{
	FragmentInput output;
	output.position = input.position;
	output.uv = input.uv;
	return output;
}