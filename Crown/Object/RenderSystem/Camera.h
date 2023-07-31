#pragma once
#ifndef CROWN_RENDEROBJECT_CAMERA
#define CROWN_RENDEROBJECT_CAMERA
#include <DirectXMath.h>
#include <d3d12.h>
#include <wrl.h>
#include "RenderCommands/SetDescriptor.h"
#include "DirectX12Wraps/ResourceUploader.h"
#include "RenderCommands/RenderCommandQueue.h"
namespace Crown
{
	namespace RenderObject
	{
		//================================================
		// 作成日 : 2023/6/28
		// 作成者 : 服部颯澄
		// 
		// カメラの制御を行うクラスだよ☆
		// 
		//================================================
		class Camera
		{
		public:
			static void CreateInstance(ID3D12Device* device);
			static Camera* GetInstance();
			static void DelteInstance();

			void SetView(DirectX::XMMATRIX view);
			inline DirectX::XMMATRIX GetView() const noexcept { return m_cpuSideCameraData.view; }

			inline unsigned int GetDescriptorOffset() { return m_descriptorOffset; }
			inline const Microsoft::WRL::ComPtr<ID3D12Resource> GetConstConstBuffer() { return m_resource; }
		private:
			Camera();
			~Camera();

			Camera(Camera& camera) = delete;
			Camera& operator=(Camera& camera) = delete;

			inline void DataUpload() { ResourceUploader::GetInstance()->UploadData<CameraData>(m_resource.Get(), ResourceUploader::GetInstance()->Get255AlignmentSize<CameraData>(1), [&](CameraData* gpuSideCameraData) { *gpuSideCameraData = m_cpuSideCameraData; }); };

			struct CameraData
			{
				DirectX::XMMATRIX view;							//	ビュー行列だよ☆
				DirectX::XMMATRIX projection;					//	プロジェクション行列だよ☆
				DirectX::XMMATRIX viewProjection;				//	ビュー行列とプロジェクション行列だよ☆
				DirectX::XMFLOAT3 eye;							//	カメラ位置だよ☆
				float fovAngle;									//	カメラの画角だよ☆
				float aspect;									//	アスペクト比だよ☆
				float nearZ;									//	ニアー面だよ☆
				float farZ;										//	ファー面だよ☆
				CameraData() 
					:
					fovAngle(DirectX::XMConvertToRadians(90)),
					aspect(1280.0f / 720.0f),
					nearZ(0.1f),
					farZ(1000.0f),
					view(DirectX::XMMatrixTranslation(0,0,-20)),
					projection(DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(120), (1280.0f / 720.0f), 0.01f, 1000.0f)),
					viewProjection(projection * view),
					eye(DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f))
				{
				}
			};

			static Camera* me;

			CameraData m_cpuSideCameraData;

			Microsoft::WRL::ComPtr<ID3D12Resource> m_resource;	//	コンストバッファだよ☆
			unsigned int m_descriptorOffset;					//	ディスクリプタオフセットだよ☆
		};
	}
}

#endif // !CROWN_RENDEROBJECT_CAMERA