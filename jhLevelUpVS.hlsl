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
    VertexOut vOut = (VertexOut) 0;
    vOut.Position = vIn.Position;
    vOut.UV = vIn.UV;
    return vOut;
}