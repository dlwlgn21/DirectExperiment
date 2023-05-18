#include "globals.hlsli"

struct SpriteVertexOut
{
    float4 Position : SV_POSITION;
    float3 WorldPos : POSITION;
    float2 UV : TEXCOORD0;
};

cbuffer NumberOfLight : register(b4)
{
    uint NumberOfLighting;
};
struct Light
{
    float4 Diffuse;
    float4 Specular;
    float4 Ambient;
};

struct LightAttribute
{
    Light LightElement;
    float4 Position;
    float4 Direction;

    int ELightType;
    float Radius;
    float Angle;
    int Padding;
};

StructuredBuffer<LightAttribute> lightAttributes : register(t13);


void CalculateLight(in out Light outLight, float3 position, uint idx)
{
    const int DIRECTIONAL = 0;
    const int POINT = 1;
    const int SPOT_LIGHT = 2;
    if (lightAttributes[idx].ELightType == DIRECTIONAL)
    {
        outLight.Diffuse += lightAttributes[idx].LightElement.Diffuse;
    }
    else if (lightAttributes[idx].ELightType == POINT)
    {
        float dist = distance(lightAttributes[idx].Position.xy, position.xy);
        
        if (dist < lightAttributes[idx].Radius)
        {
            float ratio = 1.0f - (dist / lightAttributes[idx].Radius);
            outLight.Diffuse += lightAttributes[idx].LightElement.Diffuse * ratio;
        }
    }

}
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
    //return float4(color.x + 0.5f, color.y + 0.5f, color.z + 0.5f, color.w);
    color *= light.Diffuse;
    return color;
}