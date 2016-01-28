cbuffer UIConstants : register(cb0)
{
};

struct VertexInputType
{
    float4 position : POSITION;
	float4 normal	: NORMAL;
	float4x4 world	: TEXCOORD0;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
	float3 normal	: NORMAL;
};

PixelInputType main(VertexInputType input)
{
    PixelInputType output;
    
	float4 pos = mul(input.world, input.position);

    output.position = pos;
	output.normal = input.normal.xyz;
    
    return output;
}