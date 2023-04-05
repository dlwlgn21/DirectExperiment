#include "globals.hlsli"

VertexOut main(VertexIn vIn)
{
    VertexOut vOut;
    
    float4 wolrdPos = mul(vIn.Position, WorldMat);
    float4 viewPos = mul(wolrdPos, ViewMat);
    float4 projectionPos = mul(viewPos, ProjectionMat);
    
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