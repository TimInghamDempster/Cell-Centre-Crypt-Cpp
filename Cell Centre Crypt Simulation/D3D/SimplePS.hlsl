struct PixelInputType
{
    float4 position : SV_POSITION;
};

cbuffer TextureIndexBuffer
{
};

float4 main(PixelInputType input) : SV_TARGET
{
    return float4(0.5f, 0.5f, 0.5f, 1.0f);
}