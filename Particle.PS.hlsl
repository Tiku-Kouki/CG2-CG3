#include "Particle.hlsli"

struct Material {
	float32_t4 color;
	int32_t enableLighting;
};

struct DirectionalLight {
	float32_t4 color;//!<ライトの色
	float32_t3 direction;//!<ライトの向き
	float intensity;//!<輝度
};


ConstantBuffer<Material> gMaterial : register(b0);
ConstantBuffer<DirectionalLight> gDirectionalLight : register(b1);

struct PixelShaderOutput {
	float32_t4 color : SV_TARGET0;
};

Texture2D<float32_t4> gTexture : register(t0);
SamplerState gSampler : register(s0);


PixelShaderOutput main(VertexShaderOutput input)
{
	PixelShaderOutput output;
	float32_t4 textureColor = gTexture.Sample(gSampler, transformedUV.xy);
	output.color = gMaterial.color * textureColor;
	if (output.color.a == 0.0) {
		discard;

	}

	output.color = gMaterial.color * textureColor;

	return output;
}