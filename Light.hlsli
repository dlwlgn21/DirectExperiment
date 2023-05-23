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