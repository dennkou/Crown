#pragma once
#include "IRenderEngine.h"
namespace Crown
{
	//	レンダーエンジンの内部オブジェクト用のインターフェースだよ☆
	class IRenderSystem : public IRenderEngine
	{
	public:
		IRenderSystem() {};
		~IRenderSystem() {};

		inline Microsoft::WRL::ComPtr<ID3D12Device> GetDevice() const noexcept { return m_device; }
	private:
		Microsoft::WRL::ComPtr<ID3D12Device> m_device;
	};
}