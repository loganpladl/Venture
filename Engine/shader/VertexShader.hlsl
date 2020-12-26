struct VertexOut {
	float4 pos : SV_POSITION;
	float3 color : COLOR;
};

cbuffer CBuf {
	matrix transform;
};

VertexOut main(float3 pos : POSITION, float3 color : COLOR)
{
	VertexOut vOut;
	vOut.pos = mul(float4(pos.x, pos.y, pos.z, 1.0f), transform);
	vOut.color = color;
	return vOut;
}