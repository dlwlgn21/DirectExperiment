#include "globals.hlsli"

float4 main(VertexOut vIn) : SV_TARGET
{
    if (vIn.UV.x > UIuv.y)
    {
        discard;
    }
    
    float4 color = DefaultTexture.Sample(PointBorderSampler, vIn.UV);
    

    if (color.w == 0.0f)
    {
        discard;
    }
    return color;
}