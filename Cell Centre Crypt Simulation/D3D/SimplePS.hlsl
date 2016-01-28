struct PixelInputType
{
    float4 position : SV_POSITION;
	float3 normal	: NORMAL;
};

float4 main(PixelInputType input) : SV_TARGET
{
	float3 lightDir = float3(1, 1, 1);
	lightDir = normalize(lightDir);

    return dot(input.normal, lightDir);
}