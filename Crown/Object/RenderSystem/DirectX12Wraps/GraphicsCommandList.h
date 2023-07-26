#pragma once
#ifndef CROWN_RENDER_OBJCET_GRAPHICSCOMMANDLIST
#define CROWN_RENDER_OBJCET_GRAPHICSCOMMANDLIST

#include <d3d12.h>
#include <vector>
#include "CommandAllocator.h"
#include <wrl.h>
#include <memory>
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
		class GraphicsCommandList
		{
		public:
			GraphicsCommandList();
			~GraphicsCommandList();

			/// <summary>
			/// コマンドリストを渡すよ☆
			/// </summary>
			/// <returns></returns>
			inline ID3D12GraphicsCommandList* GetGraphicsCommandList() const noexcept { return m_graphicsCommandList.Get(); }

			/// <summary>
			/// リソースのコピー専門のコマンドリストを渡すよ☆
			/// </summary>
			/// <returns></returns>
			inline ID3D12GraphicsCommandList* GetCopyCommandList() const noexcept { return m_copyCommandList.Get(); }

			/// <summary>
			/// コマンドキューを渡すよ☆
			/// </summary>
			/// <returns></returns>
			inline ID3D12CommandQueue* GetCommandQueue() const noexcept { return m_commandQueue.Get(); }

			/// <summary>
			/// 初期化をするよ☆
			/// </summary>
			/// <param name="device">コマンドリストの作成に使用するID3D12Deviceのポインタだよ☆</param>
			/// <param name="allocatorNum">作成するコマンドアロケーターの数だよ☆出来るだけ少ないほうがメモリ効率が良いけど少なすぎると処理効率が悪くなるよ☆</param>
			/// <param name="failedProcessingNum">処理落ちを許可するフレーム数だよ☆</param>
			void Initialize(ID3D12Device* device, unsigned int allocatorNum = 2, unsigned int failedProcessingNum = 1);

			/// <summary>
			///	描画に使用中のリソースが誤って解放されないように保持しておくよ☆
			/// </summary>
			/// <param name="lockResource"></param>
			inline void LockResource(const Microsoft::WRL::ComPtr<ID3D12Resource>& lockResource) { m_commandAllocators[m_index]->LockResource(lockResource); }

			/// <summary>
			/// GPU側の全ての処理が終了するまで待機するよ☆
			/// コマンドリストの実行はしないよ☆
			/// </summary>
			void WaitForGpu() noexcept;

			/// <summary>
			/// コマンドリストを実行するよ☆
			/// </summary>
			void RunCommandList();

			/// <summary>
			/// コマンドリストを実行し、処理が完了するまで待機するよ☆
			/// </summary>
			void RunAndWait();

		private:

			/// <summary>
			/// コマンドリストに積んだ処理を走らせるよ☆
			/// </summary>
			void Run();

			/// <summary>
			/// 次のコマンドアロケーターを取得するよ☆
			/// </summary>
			void NextCommandAllocator();

			unsigned int													m_addCommandAllocatorNum;						//	現在追加を許可されているコマンドアロケーターの数だよ☆
			const unsigned int												MAX_FAILEDPROCESSING_NUM;						//	処理落ちが許可されたフレーム数だよ☆
			unsigned int													m_failedProcessingNum;							//	現在の処理落ち数だよ☆
			unsigned int													m_index;										//	現在使用中のコマンドアロケーターのインデックスだよ☆
			unsigned int													m_copyIndex;									//	コピー専門のコマンドアロケーターのインデックスだよ☆
			Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>				m_graphicsCommandList;							//	コマンドリストだよ☆
			Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>				m_copyCommandList;								//	コピー用コマンドリストだよ☆
			Microsoft::WRL::ComPtr<ID3D12CommandQueue>						m_commandQueue;									//	コマンドキューだよ☆
			std::vector<std::unique_ptr<CommandAllocator>>					m_commandAllocators;							//	コマンドアロケーターの配列だよ☆
			std::vector<std::unique_ptr<CommandAllocator>>					m_copyAllocators;								//	コピー用コマンドアロケーターの配列だよ☆

			HANDLE															m_waitEvent;									//	描画狩猟まで待機する為のイベントだよ☆

			ID3D12Device*													m_device;
		};
	}
}
#endif // !CROWN_RENDER_OBJCET_GRAPHICSCOMMANDLIST