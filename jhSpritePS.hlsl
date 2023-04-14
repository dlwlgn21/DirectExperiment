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
        color = AtlasTexture.Sample(PointBorderSampler, uv);
        //if (color.x == 1.0f && color.y == 1.0f && color.z == 1.0f)
        //{
        //    discard;
        //}
    }
    else
    {
        color = DefaultTexture.Sample(PointBorderSampler, vIn.UV);
    }

    //return float4(color.x + 0.5f, color.y + 0.5f, color.z + 0.5f, color.w);
    return color;
}