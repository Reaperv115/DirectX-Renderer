#include "Mesh.h"

Mesh::Mesh(ID3D11Device* device, ID3D11DeviceContext* deviceContext, std::vector<Vertex> vertices, std::vector<DWORD>& indices)
{
	this->devicecontext = deviceContext;

	HRESULT hr = this->vertexBuffer.Initialize(device, vertices.data(), vertices.size());
	if (hr == FALSE)
		ErrorLogger::Log(hr, "failed to initialize vertex buffer in mesh constructor.");

	hr = this->indexBuffer.Initialize(device, indices.data(), indices.size());
	if (hr == FALSE)
		ErrorLogger::Log(hr, "failed to initialize index buffer, in mesh constructor");
}

Mesh::Mesh(const Mesh& mesh)
{
	this->devicecontext = mesh.devicecontext;
	this->indexBuffer = mesh.indexBuffer;
	this->vertexBuffer = mesh.vertexBuffer;
}

void Mesh::Draw()
{
	UINT offset = 0;
	this->devicecontext->IASetVertexBuffers(0, 1, this->vertexBuffer.GetAddressOf(), this->vertexBuffer.StridePtr(), &offset);
	this->devicecontext->IASetIndexBuffer(this->indexBuffer.Get(), DXGI_FORMAT::DXGI_FORMAT_R32_UINT, 0);
	this->devicecontext->DrawIndexed(this->indexBuffer.BufferSize(), 0, 0);
}
