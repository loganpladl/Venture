struct VertexOut {
	float4 pos : SV_POSITION;
	float3 color : COLOR;
};

float4 main(VertexOut input) : SV_TARGET
{
	return float4(input.color, 1.0f);
}