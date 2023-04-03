cbuffer MatrixBuffer : register (b0)
{
    row_major matrix WorldMat;
    row_major matrix ViewMat;
    row_major matrix ProjectionMat;
};

struct VertexIn
{
    float4 Position : POSITION;
	float2 UV : TEXCOORD0;
};

struct VertexOut
{
    float4 Position : SV_POSITION;
    float2 UV : TEXCOORD0;
};

VertexOut main(VertexIn vIn)
{
    VertexOut vOut;
    
    float4 wolrdPos = mul(vIn.Position, WorldMat);
    float4 viewPos = mul(wolrdPos, ViewMat);
    float4 projectionPos = mul(viewPos, ProjectionMat);
    
    vOut.Position = projectionPos;
    vOut.UV = vIn.UV;
	return vOut;
}