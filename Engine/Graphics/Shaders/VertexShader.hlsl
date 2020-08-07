#pragma pack_matrix(row_major)

cbuffer Matrices : register(b0)
{
    float4x4 mat;
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
    
    toPShader.outposition = mul(float4(input.inpos, 1.0f), mat);
    toPShader.outtexCoord = input.intexCoord;
    return toPShader;
}