#pragma once
#include "IRenderEngine.h"
namespace Crown
{
	//	�����_�[�G���W���̓����I�u�W�F�N�g�p�̃C���^�[�t�F�[�X���恙
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