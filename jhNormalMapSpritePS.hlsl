#include "globals.hlsli"
#include "Light.hlsli"

Texture2D NormalMapTexture : register(t11);

float3 DecodeNormalMap(float3 normalMap)
{
    return normalize(normalMap * 2.0f - 1.0f);
}

void CalculateLightWithNormal(in out Light outLight, inout float3x3 tangentSpaceMat, float3 worldNormal, float3 playerPos, uint idx)
{
    const int DIRECTIONAL = 0;
    const int POINT = 1;
    const int SPOT_LIGHT = 2;
    float3 lightDir = normalize(playerPos.xyz - lightAttributes[idx].Position.xyz);
    lightDir = mul(lightDir, tangentSpaceMat);
    //float2 lightDir = normalize(playerPos.xy - lightAttributes[idx].Position.xy);
    
    float3 diffuse = saturate(dot(worldNormal, -lightDir));
    if (lightAttributes[idx].ELightType == DIRECTIONAL)
    {
        outLight.Diffuse.rgb = lightAttributes[idx].LightElement.Diffuse.rgb * diffuse;
    }
    else if (lightAttributes[idx].ELightType == POINT)
    {
        float dist = distance(lightAttributes[idx].Position.xy, playerPos.xy);
        
        if (dist < lightAttributes[idx].Radius)
        {
            float ratio = 1.0f - (dist / lightAttributes[idx].Radius);
            outLight.Diffuse.rgb += lightAttributes[idx].LightElement.Diffuse.rgb * ratio * diffuse;
        }
    }
}

struct NormalMapVertexOut
{
    float4 Position : SV_POSITION;
    float3 WorldPos : POSITION;
    float2 UV       : TEXCOORD0;
    float3 N        : TEXCOORD1;
    float3 T        : TEXCOORD2;
    float3 B        : TEXCOORD3;
};

float4 main(NormalMapVertexOut vIn) : SV_TARGET
{
    const float ADD = 0.1f;
    float4 albedo = (float) 0.0f;
    float3 lightDir;
    float3 diffsue;
    float3 tangentNormal;
    float3 worldNormal;
    
    const uint SECOND_DIMENTION = 1;
    
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
        albedo = AtlasTexture.Sample(PointBorderSampler, uv);
    }
    else
    {
        albedo = DefaultTexture.Sample(PointBorderSampler, vIn.UV);
        //return float4(albedo.rgb, 1.0f);
    }
    if (albedo.w == 0.0f)
    {
        discard;
    }
    
    
    float4 normalMapSample = NormalMapTexture.Sample(PointBorderSampler, vIn.UV);
    tangentNormal = DecodeNormalMap(normalMapSample.xyz);
    //worldNormal = mul(tangentNormal, (float3x3) WorldMat);
    tangentNormal.z = -tangentNormal.z;
    
    
    //Make sure tangent is completely orthogonal to normal
    vIn.T = normalize(vIn.T - dot(vIn.T, vIn.N) * vIn.N);

    //Create the biTangent
    float3 biTangent = cross(vIn.N, vIn.T);

    //Create the "Texture Space"
    float3x3 texSpace = float3x3(vIn.T, biTangent, vIn.N);

    //Convert normal from normal map to texture space and store in input.normal
    worldNormal = normalize(mul(tangentNormal, texSpace));
    
    //float3x3 TBN = float3x3(normalize(vIn.T), normalize(vIn.B), normalize(vIn.N));
    //TBN = transpose(TBN);
    
    //worldNormal = mul(TBN, tangentNormal);
    
    Light light = (Light) 0.0f;
    for (uint i = 0; i < NumberOfLighting; i++)
    {
        CalculateLightWithNormal(light, texSpace, worldNormal, vIn.WorldPos.xyz, i);
    }
    light.Diffuse.rgb *= albedo.rgb;
    //return color;
    
    
    return float4(light.Diffuse.rgb, 1.0f);
}