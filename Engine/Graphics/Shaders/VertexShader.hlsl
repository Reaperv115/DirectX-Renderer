struct VShaderIn
{
    float3 pos : POSITION;
    float3 color : COLOR;
};

struct PShaderIn
{
    float4 position : SV_Position;
    float3 col : COLOR;
};

PShaderIn main(VShaderIn input)
{
    PShaderIn toPShader;
    toPShader.position = float4(input.pos, 1.0f);
    toPShader.col = input.color;
    return toPShader;
}