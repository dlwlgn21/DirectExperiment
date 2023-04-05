#include "globals.hlsli"


VertexOut main(VertexIn vIn)
{
    VertexOut vOut;
   // vOut.Position = mul(vIn.Position, WorldMat);
    
    const float MESH_SCALE = 2.0f;
    float4 worldPos = mul(vIn.Position, WorldMat);
    float4 viewPos = mul(worldPos, ViewMat);
    float4 projectionPos = mul(viewPos, ProjectionMat);
    
    //vOut.Position = float4(worldPos.xy * MESH_SCALE, 10.0f, 1.0f);
    //vOut.Position = float4(vIn.Position.xy, 30.0f, 1.0f);
    vOut.Position = worldPos;
    vOut.UV = vIn.UV;
    return vOut;
}