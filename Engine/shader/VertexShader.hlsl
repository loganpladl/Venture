struct VertexOut {
	float4 pos : SV_POSITION;
	float3 color : COLOR;
};

cbuffer cbPerObject : register(b0) {
	matrix world;
};

cbuffer cbPerFrame : register(b1) {
	matrix view;
};

cbuffer cbPerResize: register(b2) {
	matrix projection;
};

VertexOut main(float3 pos : POSITION, float3 color : COLOR)
{
	VertexOut vOut;
	matrix transform = mul(mul(world, view), projection);
	vOut.pos = mul(float4(pos.x, pos.y, pos.z, 1.0f), transform);
	vOut.color = color;
	return vOut;
}