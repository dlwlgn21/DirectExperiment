struct VertexOut
{
    float4 Position : SV_POSITION;
    float2 UV : TEXCOORD0;
};
SamplerState PointSampler : register(s0);
Texture2D DefaultTexture : register(t0);

float4 main(VertexOut vIn) : SV_TARGET
{
    return DefaultTexture.Sample(PointSampler, vIn.UV);
}