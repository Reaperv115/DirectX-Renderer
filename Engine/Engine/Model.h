#pragma once
#include "../Graphics/Vertex.h"
#include "../Graphics/VertexBuffer.h"
#include "../Graphics/IndexBuffer.h"
#include "../Graphics/ConstantBuffer.h"

using namespace DirectX;

class Model
{
public:
	bool Initialize(ID3D11Device* device, ID3D11DeviceContext* devicecontext, ID3D11ShaderResourceView* texture, ConstantBuffer<CB_VS_VertexShader>& cb_vs_vertexshader);
	void setTexture(ID3D11ShaderResourceView* texture);
	void Draw(const XMMATRIX& viewprojectionMatrix);
private:
	void updateworldMatrix();

	ID3D11Device* device = nullptr;
	ID3D11DeviceContext* devicecontext = nullptr;
	ConstantBuffer<CB_VS_VertexShader>* cb_vs_vertexshader = nullptr;
	ID3D11ShaderResourceView* texture = nullptr;

	VertexBuffer<Vertex> vertexbuffer;
	IndexBuffer indexbuffer;

	XMMATRIX worldMatrix = XMMatrixIdentity();
};