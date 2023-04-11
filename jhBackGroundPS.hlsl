#include "globals.hlsli"

float4 main(VertexOut vIn) : SV_TARGET
{
    float4 color = DefaultTexture.Sample(PointBorderSampler, vIn.UV + UVTranslationPostion.xy);
    if (color.x == 1.0f && color.y == 0.0f && color.z == 1.0f)
    {
        discard;
    }
    return color;
}