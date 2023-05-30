#include "globals.hlsli"
#include "Light.hlsli"

float4 main(SpriteVertexOut vIn) : SV_TARGET
{
    const float ADD = 0.1f;
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
        if (color.w == 0.0f)
        {
            discard;
        }
    }
    else
    {
        color = DefaultTexture.Sample(PointBorderSampler, vIn.UV);
    }

    Light light = (Light) 0.0f;
    for (uint i = 0; i < NumberOfLighting; i++)
    {
        CalculateLight(light, vIn.WorldPos.xyz, i);
    }
    color *= light.Diffuse;
    return color;
}