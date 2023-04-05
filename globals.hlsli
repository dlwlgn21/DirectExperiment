cbuffer MatrixBuffer : register(b0)
{
    row_major matrix WorldMat;
    row_major matrix ViewMat;
    row_major matrix ProjectionMat;
};

cbuffer AnimationBuffer : register(b1)
{
    float2 LeftTop;
    float2 AnimSize;
    float2 Offset;
    float2 AtlasImageSize;
    
    uint AnimationType;
    uint IsAnimFlip;
}

cbuffer UVTranslationBuffer : register(b2)
{
    float4 UVTranslationPostion;
}

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

SamplerState PointSampler : register(s0);
Texture2D DefaultTexture : register(t0);
Texture2D AtlasTexture : register(t12);