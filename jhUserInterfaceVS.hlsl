#include "globals.hlsli"


VertexOut main(VertexIn vIn)
{
    VertexOut vOut;
    
    float4 worldPos = mul(vIn.Position, WorldMat);
    float4 viewPos = mul(worldPos, ViewMat);
    float4 projectionPos = mul(viewPos, ProjectionMat);
    
    vOut.Position = projectionPos;
    vOut.UV = vIn.UV;
    return vOut;
}