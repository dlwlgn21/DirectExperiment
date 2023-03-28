cbuffer MatrixBuffer
{
    matrix worldMat;
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
    vOut.Position = mul(vIn.Position, worldMat);
    vOut.UV = vIn.UV;
	return vOut;
}