#include "Data.hlsli"
float4 DefaultPixelShader(float4 pos : SV_Position) : SV_TARGET
{
	return float4(0, 1, 0, 1);
}