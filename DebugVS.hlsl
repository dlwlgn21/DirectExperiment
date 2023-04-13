#include "globals.hlsli"

VertexOut main(VertexIn vIn)
{
    VertexOut vOut = (VertexOut) 0.0f;
    
    float4 wolrdPos = mul(vIn.Position, WorldMat);
    float4 viewPos = mul(wolrdPos, ViewMat);
    float4 projectionPos = mul(viewPos, ProjectionMat);
    
    vOut.Position = projectionPos;
    return vOut;
}