#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#include <memory>

template<class T>
class VertexBuffer
{
private:
	VertexBuffer(const VertexBuffer<T>& rhs);
private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
	std::unique_ptr<UINT> stride;
	UINT bufferSize = 0;

public:
	VertexBuffer() {}

	ID3D11Buffer* Get() const
	{
		return buffer.Get();
	}

	ID3D11Buffer* const* GetAddressOf() const
	{
		return buffer.GetAddressOf();
	}

	UINT BufferSize() const
	{
		return this->bufferSize;
	}

	const UINT Stride() const
	{
		return *this->stride.get();
	}

	const UINT* StridePtr() const
	{
		return this->stride.get();
	}

	HRESULT Initialize(ID3D11Device* device, T* data, UINT numVerts)
	{
		this->bufferSize = numVerts;
		this->stride = std::make_unique<UINT>(sizeof(T));

		D3D11_BUFFER_DESC vertexbufferDesc;
		ZeroMemory(&vertexbufferDesc, sizeof(vertexbufferDesc));

		vertexbufferDesc.Usage = D3D11_USAGE_DEFAULT;
		vertexbufferDesc.ByteWidth = sizeof(T) * numVerts;
		vertexbufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexbufferDesc.CPUAccessFlags = 0;
		vertexbufferDesc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA vertexbufferData;
		ZeroMemory(&vertexbufferData, sizeof(vertexbufferData));
		vertexbufferData.pSysMem = data;

		HRESULT hr = device->CreateBuffer(&vertexbufferDesc, &vertexbufferData, this->buffer.GetAddressOf());
		return hr;
	}
};

