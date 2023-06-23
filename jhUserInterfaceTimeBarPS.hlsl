#include "globals.hlsli"

float4 main(VertexOut vIn) : SV_TARGET
{
    if (vIn.UV.x < TimeRatio.x)
    {
        float4 color = DefaultTexture.Sample(PointBorderSampler, vIn.UV);
        if (color.w == 0.0f)
        {
            discard;
        }
        return color;
    }
    return float4(0.0f, 0.0f, 0.0f, 1.0f);

}