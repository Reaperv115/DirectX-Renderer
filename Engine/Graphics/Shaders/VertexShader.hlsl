cbuffer Matrices : register(b0)
{
    float xOffset;
    float yOffset;
}

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
    
    input.inpos.x += xOffset;
    input.inpos.y += yOffset;
    
    toPShader.outposition = float4(input.inpos, 1.0f);
    toPShader.outtexCoord = input.intexCoord;
    return toPShader;
}