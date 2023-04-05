#include "globals.hlsli"

float4 main(VertexOut vIn) : SV_TARGET
{
    float4 color = (float) 0.0f;
    const uint SECOND_DIMENTION = 1;
    const uint THIRD_DIMENTION = 2;
    
    if (AnimationType == SECOND_DIMENTION)
    {
        float2 diff = (AtlasImageSize - AnimSize) * 0.5f;
        float2 uv = (LeftTop - diff - Offset) + (AtlasImageSize * vIn.UV);
        if (uv.x < LeftTop.x ||
            uv.y < LeftTop.y ||
            uv.x > LeftTop.x + AnimSize.x ||
            uv.y > LeftTop.y + AnimSize.y)
        {
            discard;
        }
        color = AtlasTexture.Sample(PointSampler, uv);
    }
    else
    {
        color = DefaultTexture.Sample(PointSampler, vIn.UV);
    }

    return color;
}