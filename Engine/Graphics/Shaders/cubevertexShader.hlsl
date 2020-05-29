cbuffer Matrices : register(b0)
{
    float4x4 mat;
}

struct vertexshader_in
{
    float4 position : POS;
    float2 color : TEXTURE;
    float3 norm : NORMALS;
};

struct vertexshader_out
{
    float4 pos : SV_Position;
    float2 col : TEXTURE;
    float3 normals : NORMALS;
};

vertexshader_out main( vertexshader_in input )
{
    vertexshader_out output = (vertexshader_out)0;
    input.position = mul(input.position, mat);
    output.pos = input.position;
    output.col = input.color;
    output.normals = input.norm;
    return output;
}