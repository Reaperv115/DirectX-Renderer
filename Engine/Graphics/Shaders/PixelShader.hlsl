struct PShaderIn
{
    float4 position : SV_Position;
    float2 intexCoord : TEXCOORD;
};

Texture2D objTexture : TEXTURE : register(t0);
SamplerState objsamplerState : SAMPLER : register(s0);

float4 main(PShaderIn input) : SV_TARGET
{
    float3 pixelColor = objTexture.Sample(objsamplerState, input.intexCoord);
    
	return float4(pixelColor, 1.0f);
}