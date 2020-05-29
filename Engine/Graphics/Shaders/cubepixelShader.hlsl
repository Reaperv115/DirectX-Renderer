struct pixelshader_in
{
    float4 position : SV_Position;
    float2 texcoord : TEXTURE;
    float3 normals : NORMALS;
};

float4 main() : SV_TARGET
{
    pixelshader_in input = (pixelshader_in)0;
    return float4(input.texcoord, 1.0f, 1.0f);
}