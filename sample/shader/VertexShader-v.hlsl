cbuffer MatrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};

struct VertexInput
{
	float3 position : Position;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
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
	output.position = float4(input.position, 1.0f);
	output.uv = input.uv;
	return output;
}