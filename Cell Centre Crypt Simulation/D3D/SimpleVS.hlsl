cbuffer UIConstants : register(cb0)
{
	float2 screenSize;
	float2 sixteenByteAlignPad;
};

cbuffer PositionBuffer : register(cb1)
{
	float4 positionsAndSizes[4096];
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
};

PixelInputType main(VertexInputType input)
{
    PixelInputType output;
    
	float4 pos = mul(input.world, input.position);

    output.position = pos;
    
    return output;
}