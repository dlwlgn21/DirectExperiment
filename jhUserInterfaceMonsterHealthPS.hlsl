#include "globals.hlsli"

struct MonsterUI
{
    float4 MonsterHPRatio;
};

StructuredBuffer<MonsterUI> MonsterUIStructuredBuffer : register(t14);

float4 main(VertexOut vIn) : SV_TARGET
{
    const float Y_RESTRICTION_VALUE = 0.3125f;
    const int MAX_MONSTER_COUNT_IN_SCENE = 32;;
    const int ITERRATION_COUNT = min(CountOfMonsterInScene, MAX_MONSTER_COUNT_IN_SCENE);
    
    float4 color = DefaultTexture.Sample(PointBorderSampler, vIn.UV);
    if (color.w == 0.0f)
    {
        discard;
    }
    
    for (int i = 0; i < ITERRATION_COUNT; i++)
    {
        if (vIn.UV.x > MonsterUIStructuredBuffer[i].MonsterHPRatio.x)
        {
            if (vIn.UV.y > Y_RESTRICTION_VALUE)
            {
                discard;
            }
            return float4(0.0f, 0.0f, 0.0f, 1.0f);
        }
    }
    
    return color;
}