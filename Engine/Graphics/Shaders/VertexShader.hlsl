struct VShaderIn
{
    float3 inpos : POSITION;
    float3 intexCoord : TEXCOORD;
};

struct PShaderIn
{
    float4 outposition : SV_Position;
    float2 outtexCoord : TEXCOORD;
};

PShaderIn main(VShaderIn input)
{
    PShaderIn toPShader;
    toPShader.outposition = float4(input.inpos, 1.0f);
    toPShader.outtexCoord = input.intexCoord;
    return toPShader;
}