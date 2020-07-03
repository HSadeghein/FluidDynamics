struct FragmentInput {
	float4 position : Position;
};

float4 main(FragmentInput input) : SV_TARGET
{
	return float4(1, 0, 0, 1);
}