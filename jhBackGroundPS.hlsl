#include "globals.hlsli"

float4 main(VertexOut vIn) : SV_TARGET
{
    const float ADD = 0.01f;
    //float4 color = DefaultTexture.Sample(PointBorderSampler, vIn.UV + UVTranslationPostion.xy);
    float4 color = DefaultTexture.Sample(PointBorderSampler, vIn.UV);
    //if (color.x == 1.0f && color.y == 0.0f && color.z == 1.0f)
    //{
    //    discard;
    //}
    
    if (color.w == 0.0f)
    {
        discard;
    }
    //return color;
    return color;
    
}