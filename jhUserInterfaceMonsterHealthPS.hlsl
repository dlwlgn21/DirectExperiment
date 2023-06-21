#include "globals.hlsli"

float4 main(VertexOut vIn) : SV_TARGET
{
    const float Y_RESTRICTION_VALUE = 0.3125f;
    
    float4 color = DefaultTexture.Sample(PointBorderSampler, vIn.UV);
    if (color.w == 0.0f)
    {
        discard;
    }

    if (vIn.UV.x > MonsterHPRatio.x)
    {
        if (vIn.UV.y > Y_RESTRICTION_VALUE)
        {
            discard;
        }
        return float4(0.0f, 0.0f, 0.0f, 1.0f);
    }
    
    return color;
}