struct Output
{
	float4 pos : POSITION;
	float4 svpos : SV_POSITION;
	float4 normal : NORMAL0;
	float4 vnormal : NORMAL1;
	float2 uv : TEXCOORD;
	float3 ray : VECTOR; //ベクトル
};

cbuffer materialBuffer : register(b2)
{
	float4 diffuse;
	float4 specular; //スペキュラ
	float3 ambient; //アンビエント
};