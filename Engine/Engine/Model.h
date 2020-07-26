#pragma once
#include "Mesh.h"


using namespace DirectX;

class Model
{
public:
	bool Initialize(const std::string& filepath, ID3D11Device* device, ID3D11DeviceContext* devicecontext, ID3D11ShaderResourceView* texture, ConstantBuffer<CB_VS_VertexShader>& cb_vs_vertexshader);
	void setTexture(ID3D11ShaderResourceView* texture);
	void Draw(const XMMATRIX& viewprojectionMatrix);
public:
	std::vector<XMFLOAT3> vertexPositions;
	std::vector<XMFLOAT2> vertexTexcoord;
	std::vector<XMFLOAT3> vertexNormals;

	std::vector<int> vertexposIndices;
	std::vector<int> vertextexIndices;
	std::vector<int> vertexnormalIndices;

	std::vector<Vertex> vertices;

	const XMVECTOR& getposVector() const;
	const XMFLOAT3& getposFloat3() const;
	const XMVECTOR& getrotationVector() const;
	const XMFLOAT3& getrotationFloat3() const;

	void setPosition(const XMVECTOR& pos);
	void setPosition(const XMFLOAT3& pos);
	void setPosition(float x, float y, float z);
	void adjustPosition(const XMVECTOR& pos);
	void adjustPosition(const XMFLOAT3& pos);
	void adjustPosition(float x, float y, float z);
	void setRotation(const XMVECTOR& rot);
	void setRotation(const XMFLOAT3& rot);
	void setRotation(float x, float y, float z);
	void adjustRotation(const XMVECTOR& rot);
	void adjustRotation(const XMFLOAT3& rot);
	void adjustRotation(float x, float y, float z);
	void setlookatPos(XMFLOAT3 lookatPos);
	const XMVECTOR& getforwardVector();
	const XMVECTOR& getrightVector();
	const XMVECTOR& getbackwardVector();
	const XMVECTOR& getleftVector();
private:
	std::vector<Mesh> meshes;
	bool loadModel(const std::string& filepath);
	void updateworldMat();

	ID3D11Device* device = nullptr;
	ID3D11DeviceContext* devicecontext = nullptr;
	ConstantBuffer<CB_VS_VertexShader>* cb_vs_vertexshader = nullptr;
	ID3D11ShaderResourceView* texture = nullptr;

	VertexBuffer<Vertex> vertexBuffer;
	IndexBuffer indexBuffer;

	XMMATRIX worldMatrix = XMMatrixIdentity();

	XMVECTOR posVector;
	XMVECTOR rotVector;
	XMFLOAT3 pos;
	XMFLOAT3 rot;

	const XMVECTOR DEFAULT_FORWARD_VECTOR = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	const XMVECTOR DEFAULT_UP_VECTOR = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	const XMVECTOR DEFAULT_BACKWARD_VECTOR = XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f);
	const XMVECTOR DEFAULT_LEFT_VECTOR = XMVectorSet(-1.0f, 0.0f, 0.0f, 0.0f);
	const XMVECTOR DEFAULT_RIGHT_VECTOR = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);

	XMVECTOR vecForward;
	XMVECTOR vecLeft;
	XMVECTOR vecRight;
	XMVECTOR vecBackward;
};