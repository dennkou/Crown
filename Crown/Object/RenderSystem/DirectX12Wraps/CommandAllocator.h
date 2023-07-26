#pragma once
#ifndef CROWN_RENDEROBJECT_COMMANDALLOCATOR
#define CROWN_RENDEROBJECT_COMMANDALLOCATOR
#include <d3d12.h>
#include <wrl.h>
#include <vector>
namespace Crown
{
	namespace RenderObject
	{
		//================================================
		// 作成日 : 2023/6/21
		// 作成者 : 服部颯澄
		// 
		// コマンドリストをラップするクラスだよ☆
		// 
		//================================================
		class CommandAllocator
		{
		public:
			CommandAllocator(ID3D12Device* device, D3D12_COMMAND_LIST_TYPE type);
			~CommandAllocator();

			/// <summary>
			/// GUP側の処理が終わったか確認するよ☆
			/// </summary>
			/// <returns></returns>
			bool NotDrewEnd();

			/// <summary>
			/// GPU側の処理が終るまで待機するよ☆
			/// </summary>
			/// <param name="waitEvent"></param>
			void WaitForGpu(HANDLE waitEvent) noexcept;

			/// <summary>
			///	描画に使用中のリソースが誤って解放されないように保持しておくよ☆
			/// </summary>
			/// <param name="lockResource"></param>
			inline void LockResource(const Microsoft::WRL::ComPtr<ID3D12Resource>& lockResource) { m_resourceHolder.push_back(lockResource); }

			void Reset();

			inline ID3D12CommandAllocator* GetCommandAllocator() const noexcept { return m_commandAllocator.Get(); }
			inline ID3D12Fence* GetFence() const noexcept { return m_fence.Get(); }
			inline UINT64 GetFenceValue() const noexcept { return m_fenceValue; }
			void CountUp() noexcept { ++m_fenceValue; }
		private:
			Microsoft::WRL::ComPtr<ID3D12CommandAllocator>		m_commandAllocator;
			Microsoft::WRL::ComPtr<ID3D12Fence>					m_fence;
			UINT64												m_fenceValue;
			std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>>	m_resourceHolder;		//	描画中に誤って解放されないようにシェアポインタを保持しておくよ☆
		};
	}
}
#endif // !CROWN_RENDEROBJECT_COMMANDALLOCATOR