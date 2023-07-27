#include "Data.hlsli"

Texture2D<float4> tex : register(t0);
Texture2D<float4> sph : register(t1);
Texture2D<float4> spa : register(t2);
Texture2D<float4> toon : register(t3);

SamplerState smp : register(s0);
SamplerState smpToon : register(s1);

float4 main(Output input) : SV_TARGET
{
	float3 light = normalize(float3(1, -1, 1)); //光の向かうベクトル(平行光線)

	//ディフューズ計算
	float diffuseB = saturate(dot(-light, input.normal.xyz));
	float4 toonDif = toon.Sample(smpToon, float2(0, 1.0 - diffuseB));

	//光の反射ベクトル
	float3 refLight = normalize(reflect(light, input.vnormal.xyz));
	float specularB = pow(saturate(dot(refLight, input.ray)), specular.a);
	
	//スフィアマップ用UV
	float2 sphereMapUV = input.vnormal.xy;
	sphereMapUV = (sphereMapUV + float2(1, -1)) * float2(0.5, -0.5);

	float4 texColor = tex.Sample(smp, input.uv); //テクスチャカラー
	
	return max(saturate(
				toonDif //輝度(トゥーン)
				* diffuse //ディフューズ色
				* texColor //テクスチャカラー
				* sph.Sample(smp, sphereMapUV)) //スフィアマップ(乗算)
			+ saturate(spa.Sample(smp, sphereMapUV) * texColor //スフィアマップ(加算)
			+ float4(specularB * specular.rgb, 1)) //スペキュラー
			, float4(texColor.rgb * ambient, 1)); //アンビエント
}