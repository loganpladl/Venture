struct VertexOut {
	float4 pos : SV_POSITION;
	float3 color : COLOR;
};

VertexOut main(float2 pos : POSITION, float3 color : COLOR)
{
	VertexOut vOut;
	vOut.pos = float4(pos.x, pos.y, 0.0f, 1.0f);
	vOut.color = color;
	return vOut;
}