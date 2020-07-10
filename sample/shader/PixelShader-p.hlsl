Texture2D shaderTexture;
SamplerState sampleType;

cbuffer ColorBuffers
{
	float4 color;
};

struct FragmentInput {
	float4 position : SV_Position;
	float2 uv : TEXCOORD0;
};

float4 main(FragmentInput input) : SV_TARGET
{
	float4 texColor = shaderTexture.Sample(sampleType, input.uv);
	return texColor;
}