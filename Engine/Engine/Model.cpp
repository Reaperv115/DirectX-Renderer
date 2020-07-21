#include "Model.h"

bool Model::Initialize(ID3D11Device* device, ID3D11DeviceContext* devicecontext, ID3D11ShaderResourceView* texture, ConstantBuffer<CB_VS_VertexShader>& cb_vs_vertexshader)
{
	this->device = device;
	this->devicecontext = devicecontext;
	this->texture = texture;
	this->cb_vs_vertexshader = &cb_vs_vertexshader;

	// red triangle
	Vertex vertex[] =
	{
		Vertex(-0.5f, -0.5f, -0.5f, 0.0f, 1.0f), //front bottom left - 0
		Vertex(-0.5f,  0.5f, -0.5f, 0.0f, 0.0f), //front top left    - 1
		Vertex(0.5f,  0.5f, -0.5f, 1.0f, 0.0f), //front top right   - 2
		Vertex(0.5f, -0.5f, -0.5f, 1.0f, 1.0f), //front bottom right - 3
		Vertex(-0.5f, -0.5f, 0.5f, 0.0f, 1.0f), //back bottom left - 0
		Vertex(-0.5f,  0.5f, 0.5f, 0.0f, 0.0f), //back top left    - 1
		Vertex(0.5f,  0.5f, 0.5f, 1.0f, 0.0f), //back top right   - 2
		Vertex(0.5f, -0.5f, 0.5f, 1.0f, 1.0f) //back bottom right - 3
	};


	HRESULT hr = this->vertexBuffer.Initialize(this->device, vertex, _ARRAYSIZE(vertex));
	if (FAILED(hr))
	{
		ErrorLogger::Log(hr, "Failed to create vertex buffer");
		return false;
	}

	DWORD indices[] =
	{
		0, 1, 2, // front
		0, 2, 3,// front
		4, 7, 6, //back
		4, 6, 5, //back
		3, 2, 6, // right side
		3, 6, 7, // right side
		4, 5, 1, // left side
		4, 1, 0, // left side
		1, 5, 6, // top
		1, 6, 2, // top
		0, 3, 7, // bottom
		0, 7, 4, // bottom
	};



	hr = this->indexBuffer.Initialize(this->device, indices, _ARRAYSIZE(indices));
	if (FAILED(hr))
	{
		ErrorLogger::Log(hr, "Failed to create index buffer");
		return false;
	}

	this->updateworldMatrix();
	return true;
}

void Model::setTexture(ID3D11ShaderResourceView* texture)
{
	this->texture = texture;
}

void Model::Draw(const XMMATRIX& viewprojectionMatrix)
{
	this->cb_vs_vertexshader->data.mat = this->worldMatrix * viewprojectionMatrix;
	this->cb_vs_vertexshader->data.mat = XMMatrixTranspose(this->cb_vs_vertexshader->data.mat);
	this->cb_vs_vertexshader->ApplyChanges();
	this->devicecontext->VSSetConstantBuffers(0, 1, this->cb_vs_vertexshader->GetAddressOf());

	this->devicecontext->PSSetShaderResources(0, 1, &this->texture);
	this->devicecontext->IASetIndexBuffer(this->indexBuffer.Get(), DXGI_FORMAT::DXGI_FORMAT_R32_UINT, 0);
	UINT offset = 0;
	this->devicecontext->IASetVertexBuffers(0, 1, this->vertexBuffer.GetAddressOf(), this->vertexBuffer.StridePtr(), &offset);
	this->devicecontext->DrawIndexed(this->indexBuffer.BufferSize(), 0, 0);
}

void Model::updateworldMatrix()
{
	this->worldMatrix = XMMatrixIdentity();
}
