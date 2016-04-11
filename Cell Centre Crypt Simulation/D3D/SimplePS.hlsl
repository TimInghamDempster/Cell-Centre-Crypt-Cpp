struct PixelInputType
{
    float4 position : SV_POSITION;
	float3 normal	: NORMAL;
};

cbuffer Constants : register(b0)
{
	float4 colour;
}

float4 main(PixelInputType input) : SV_TARGET
{
	float3 lightDir = float3(1, 1, 1);
	lightDir = normalize(lightDir);
	float shading = dot(input.normal, lightDir);
	shading = max(shading, 0.1);
    return float4(shading * colour);
}