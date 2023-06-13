struct VertexOut
{
    float4 Position : SV_POSITION;
    float2 UV : TEXCOORD0;
};

SamplerState PointBorderSampler : register(s0);

Texture2D DefaultTexture : register(t0);

float4 main(VertexOut vIn) : SV_TARGET
{
    float4 color = DefaultTexture.Sample(PointBorderSampler, vIn.UV);
    if (color.w == 0.0f)
    {
        discard;
    }
    return color;
}