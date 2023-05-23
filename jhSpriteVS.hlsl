#include "globals.hlsli"

struct SpriteVertexOut
{
    float4 Position : SV_POSITION;
    float3 WorldPos : POSITION;
    float2 UV       : TEXCOORD0;
};

SpriteVertexOut main(VertexIn vIn)
{
    SpriteVertexOut vOut;
    
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
	return vOut;
}