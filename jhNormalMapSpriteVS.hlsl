#include "globals.hlsli"

struct NormalMapVertexIn
{
    float4 Position     : POSITION;
    float2 UV           : TEXCOORD0;
    float3 Normal       : NORMAL;
    float3 Tangent      : TANGENT;
};
struct NormalMapVertexOut
{
    float4 Position : SV_POSITION;
    float3 WorldPos : POSITION;
    float2 UV       : TEXCOORD0;
    float3 N        : TEXCOORD1;
    float3 T        : TEXCOORD2;
    float3 B        : TEXCOORD3;
};

NormalMapVertexOut main(NormalMapVertexIn vIn)
{
    NormalMapVertexOut vOut = (NormalMapVertexOut) 0.0f;
    float4 wolrdPos = mul(vIn.Position, WorldMat);
    float4 viewPos = mul(wolrdPos, ViewMat);
    float4 projectionPos = mul(viewPos, ProjectionMat);
    
    vOut.WorldPos = wolrdPos.xyz;
    vOut.Position = projectionPos;

    const uint FLIPEED = 1;
    const uint NO_FLIPEED = 0;
    if (IsAnimFlip == FLIPEED)
    {
        vIn.UV.x = 1 - vIn.UV.x;
    }
    vOut.UV = vIn.UV;
    
    //vOut.N = normalize(mul(vIn.Normal, (float3x3) WorldMat));

    //vOut.T = normalize(mul(vIn.Tangent, (float3x3) WorldMat));
    
    //float3 BiTangent = normalize( mul ( cross(vIn.Normal, vIn.Tangent), (float3x3) WorldMat));
    //vOut.B = BiTangent;
    
    vOut.N = mul(vIn.Normal, (float3x3) WorldMat);
    vOut.T = mul(vIn.Tangent, (float3x3) WorldMat);
    vOut.B = float3(0.0f, 0.0f, 0.0f);
    
    return vOut;
}