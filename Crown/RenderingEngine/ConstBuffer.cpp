#include "ConstBuffer.h"
//
//Crown::ConstBuffer::ConstBuffer()
//{
//}
//
//Crown::ConstBuffer::~ConstBuffer()
//{
//}
//
//void Crown::ConstBuffer::CreateBuffer(Microsoft::WRL::ComPtr<ID3D12Device> device, std::initializer_list<DataType> dataTypes, std::shared_ptr<ResourceManager> resourceManager)
//{
//	m_constantBuffer = new Resource(resourceManager);
//}
//
//byte* Crown::ConstBuffer::GetDataPointer(unsigned int parameterIndex)
//{
//	unsigned int bufferIndex = 0;
//	unsigned int puttingByte = 16;
//	for (unsigned int i = 0; i < parameterIndex; ++i)
//	{
//		bufferIndex += static_cast<unsigned int>(DATA_SIZE[static_cast<unsigned char>(m_dataTypeDescriptor[i])]);
//
//		//	パティングは発生する？☆
//		if (puttingByte < DATA_SIZE[static_cast<unsigned char>(m_dataTypeDescriptor[i])] && puttingByte != 16)
//		{
//			//	発生したからパティング分ずらすよ☆
//			bufferIndex += puttingByte;
//			puttingByte = 16;
//		}
//		//	次のパティング位置を計算するよ☆
//		puttingByte -= static_cast<unsigned int>(DATA_SIZE[static_cast<unsigned char>(m_dataTypeDescriptor[i])]);
//		if (puttingByte <= 0)
//		{
//			puttingByte = 16;
//		}
//	}
//	//	パティングは発生する？☆
//	if (puttingByte < DATA_SIZE[static_cast<unsigned char>(m_dataTypeDescriptor[parameterIndex])] && puttingByte != 16)
//	{
//		//	発生したからパティング分ずらすよ☆
//		bufferIndex += puttingByte;
//	}
//
//	return &m_constantBufferData[bufferIndex];
//}
//
//void Crown::ConstBuffer::UploadConstantBuffer()
//{
//	m_constantBuffer->Upload<byte>(ResourceManager::Get255AlignmentSize<byte>(static_cast<unsigned int>(m_constantBufferData.size())), [&](byte* mapPointer)
//		{
//			for (unsigned int i = 0, size = static_cast<unsigned int>(m_constantBufferData.size()); i < size; ++i)
//			{
//				mapPointer[i] = m_constantBufferData[i];
//			}
//		});
//}