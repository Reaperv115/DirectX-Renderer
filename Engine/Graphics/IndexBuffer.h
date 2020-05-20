#include <d3d11.h>
#include <wrl/client.h>
#include <vector>

class IndexBuffer
{
private:
	IndexBuffer(const IndexBuffer& rhs);

private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
	UINT buffersize = 0;
public:
	IndexBuffer() {}

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
		return this->buffersize;
	}

	HRESULT Initialize(ID3D11Device* device, DWORD* data, UINT numIndices)
	{
		this->buffersize = numIndices;

		D3D11_BUFFER_DESC indexbufferdesc;
		ZeroMemory(&indexbufferdesc, sizeof(indexbufferdesc));
		indexbufferdesc.Usage = D3D11_USAGE_DEFAULT;
		indexbufferdesc.ByteWidth = sizeof(DWORD) * numIndices;
		indexbufferdesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indexbufferdesc.CPUAccessFlags = 0;
		indexbufferdesc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA indexbufferData;
		indexbufferData.pSysMem = data;
		HRESULT hr = device->CreateBuffer(&indexbufferdesc, &indexbufferData, buffer.GetAddressOf());
		return hr;
	}
};
