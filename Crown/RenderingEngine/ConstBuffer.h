#pragma once
#include <initializer_list>
#include "assert.h"
#include "DirectX12.h"

#include "Resource.h"
//
//namespace Crown
//{
//	class ConstBuffer
//	{
//	public:
//		enum class DataType : const unsigned char
//		{
//			Int = 0,
//			Float = 1,
//			Float2 = 2,
//			Float3 = 3,
//			Float4 = 4,
//			Matrix = 5,
//
//			Num
//		};
//
//		ConstBuffer();
//		~ConstBuffer();
//
//		void CreateBuffer(Microsoft::WRL::ComPtr<ID3D12Device> device, std::initializer_list<DataType> dataTypes, std::shared_ptr<ResourceManager> resourceManager);
//
//		template<class Data>
//		Data* GetParameter(unsigned int parameterIndex);
//
//		template<class Data>
//		void SetParameter(unsigned int parameterIndex, const Data& data);
//
//		inline const Microsoft::WRL::ComPtr<ID3D12Resource> GetBuffer() noexcept { return m_constantBuffer; }
//	private:
//		byte* GetDataPointer(unsigned int parameterIndex);
//		void UploadConstantBuffer();
//
//		std::vector<DataType> m_dataTypeDescriptor;					//	データの種類と並びを指定する管理データだよ☆
//		std::vector<byte> m_constantBufferData;						//	定数バッファに転送するデータだよ☆
//		Resource* m_constantBuffer;	//	転送先の定数バッファだよ☆
//
//		static constexpr size_t DATA_SIZE[static_cast<unsigned char>(DataType::Num)] =
//		{
//			sizeof(int),							//	Int,
//			sizeof(float),							//	Float,
//			sizeof(float) << 1,						//	Float2,
//			(sizeof(float) << 1) + sizeof(float),	//	Float3,
//			sizeof(float) << 2,						//	Float4,
//			sizeof(float) << 4						//	Matrix,
//		};
//	};
//	template<class Data>
//	inline Data* ConstBuffer::GetParameter(unsigned int parameterIndex)
//	{
//		if (DATA_SIZE[static_cast<unsigned int>(m_dataTypeDescriptor[parameterIndex])] == sizeof(Data))
//		{
//			return reinterpret_cast<Data*>(GetDataPointer(parameterIndex));
//		}
//		else
//		{
//			assert(0);
//			return nullptr;
//		}
//	}
//	template<class Data>
//	inline void ConstBuffer::SetParameter(unsigned int parameterIndex, const Data& data)
//	{
//		if (DATA_SIZE[static_cast<unsigned int>(m_dataTypeDescriptor[parameterIndex])] == sizeof(Data))
//		{
//			(*reinterpret_cast<Data*>(GetDataPointer(parameterIndex))) = data;
//		}
//		UploadConstantBuffer();
//	}
//}