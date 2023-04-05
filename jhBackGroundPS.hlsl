#include "globals.hlsli"

float4 main(VertexOut vIn) : SV_TARGET
{
    float4 color = DefaultTexture.Sample(PointSampler, vIn.UV + UVTranslationPostion.xy);
    return color;
}