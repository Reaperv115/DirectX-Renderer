#include "Model.h"

bool Model::Initialize(const std::string& filepath, ID3D11Device* device, ID3D11DeviceContext* devicecontext, ID3D11ShaderResourceView* texture, ConstantBuffer<CB_VS_VertexShader>& cb_vs_vertexshader)
{
	this->device = device;
	this->devicecontext = devicecontext;
	this->texture = texture;
	this->cb_vs_vertexshader = &cb_vs_vertexshader;

	if (!this->loadModel(filepath))
		return false;

	this->setPosition(0.0f, 0.0f, 0.0f);
	this->setRotation(0.0f, 0.0f, 0.0f);
	this->updateworldMat();
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

bool Model::loadModel(const std::string& filepath)
{
	std::stringstream ss;
	std::ifstream inFile(filepath);
	std::string line = "";
	std::string prefix = "";

	XMFLOAT3 tvec3;
	XMFLOAT2 tvec2;
	int tint = 0;

	if (!inFile.is_open())
	{
		ErrorLogger::Log("model folder could not be opened");
		return false;
	}
	
	while (std::getline(inFile, line))
	{
		ss.clear();
		ss.str(line);
		ss >> prefix;

		if (prefix == "v")
		{
			ss >> tvec3.x >> tvec3.y >> tvec3.z;
			vertexPositions.push_back(tvec3);
		}
		else if (prefix == "vt")
		{
			ss >> tvec2.x >> tvec2.y;
			vertexTexcoord.push_back(tvec2);
		}
		else if (prefix == "vn")
		{
			ss >> tvec3.x >> tvec3.y >> tvec3.z;
			vertexNormals.push_back(tvec3);
		}
	}

	return false;
}

void Model::updateworldMat()
{
	this->worldMatrix = XMMatrixRotationRollPitchYaw(this->rot.x, this->rot.y, this->rot.z) * XMMatrixTranslation(this->pos.x, this->pos.y, this->pos.z);
	XMMATRIX vecrotationMat = XMMatrixRotationRollPitchYaw(0.0f, this->rot.y, 0.0f);
	this->vecForward = XMVector3TransformCoord(this->DEFAULT_FORWARD_VECTOR, vecrotationMat);
	this->vecBackward = XMVector3TransformCoord(this->DEFAULT_BACKWARD_VECTOR, vecrotationMat);
	this->vecLeft = XMVector3TransformCoord(this->DEFAULT_LEFT_VECTOR, vecrotationMat);
	this->vecRight = XMVector3Transform(this->DEFAULT_RIGHT_VECTOR, vecrotationMat);
}

const DirectX::XMVECTOR& Model::getposVector() const
{
	return this->posVector;
}

const DirectX::XMFLOAT3& Model::getposFloat3() const
{
	return this->pos;
}

const DirectX::XMVECTOR& Model::getrotationVector() const
{
	return this->rotVector;
}

const DirectX::XMFLOAT3& Model::getrotationFloat3() const
{
	return this->rot;
}

void Model::setPosition(const XMVECTOR& pos)
{
	XMStoreFloat3(&this->pos, pos);
	this->posVector = pos;
	this->updateworldMat();
}

void Model::setPosition(const XMFLOAT3& pos)
{
	this->pos = pos;
	this->posVector = XMLoadFloat3(&this->pos);
	this->updateworldMat();
}

void Model::setPosition(float x, float y, float z)
{
	this->pos = XMFLOAT3(x, y, z);
	this->posVector = XMLoadFloat3(&this->pos);
	this->updateworldMat();
}

void Model::adjustPosition(const XMVECTOR& pos)
{
	this->posVector += pos;
	XMStoreFloat3(&this->pos, this->posVector);
	this->updateworldMat();
}

void Model::adjustPosition(const XMFLOAT3& pos)
{
	this->pos.x += pos.x;
	this->pos.y += pos.y;
	this->pos.z += pos.z;
	this->posVector = XMLoadFloat3(&this->pos);
	this->updateworldMat();
}

void Model::adjustPosition(float x, float y, float z)
{
	this->pos.x += x;
	this->pos.y += y;
	this->pos.z += z;
	this->posVector = XMLoadFloat3(&this->pos);
	this->updateworldMat();
}

void Model::setRotation(const XMVECTOR& rot)
{
	this->rotVector = rot;
	XMStoreFloat3(&this->rot, rot);
	this->updateworldMat();
}

void Model::setRotation(const XMFLOAT3& rot)
{
	this->rot = rot;
	this->rotVector = XMLoadFloat3(&this->rot);
	this->updateworldMat();
}

void Model::setRotation(float x, float y, float z)
{
	this->rot = XMFLOAT3(x, y, z);
	this->rotVector = XMLoadFloat3(&this->rot);
	this->updateworldMat();
}

void Model::adjustRotation(const XMVECTOR& rot)
{
	this->rotVector += rot;
	XMStoreFloat3(&this->rot, this->rotVector);
	this->updateworldMat();
}

void Model::adjustRotation(const XMFLOAT3& rot)
{
	this->rot.x += rot.x;
	this->rot.y += rot.y;
	this->rot.z += rot.z;
	this->rotVector = XMLoadFloat3(&this->rot);
	this->updateworldMat();
}

void Model::adjustRotation(float x, float y, float z)
{
	this->rot.x += x;
	this->rot.y += y;
	this->rot.z += z;
	this->rotVector = XMLoadFloat3(&this->rot);
	this->updateworldMat();
}

void Model::setlookatPos(XMFLOAT3 lookatPos)
{
	if (lookatPos.x == this->pos.x && lookatPos.y == this->pos.y && lookatPos.z == this->pos.z)
		return;

	lookatPos.x = this->pos.x - lookatPos.x;
	lookatPos.y = this->pos.y - lookatPos.y;
	lookatPos.z = this->pos.z - lookatPos.z;

	float pitch = 0;
	if (lookatPos.y != 0.0f)
	{
		const float distance = sqrt(lookatPos.x * lookatPos.x + lookatPos.z * lookatPos.z);
		pitch = atan(lookatPos.y / distance);
	}

	float yaw = 0.0f;
	if (lookatPos.x != 0.0f)
	{
		yaw = atan(lookatPos.x / lookatPos.z);
	}
	if (lookatPos.z > 0)
		yaw += XM_PI;

	this->setRotation(pitch, yaw, 0.0f);
}

const DirectX::XMVECTOR& Model::getforwardVector()
{
	return this->vecForward;
}

const DirectX::XMVECTOR& Model::getrightVector()
{
	return this->vecRight;
}

const DirectX::XMVECTOR& Model::getbackwardVector()
{
	return this->vecBackward;
}

const DirectX::XMVECTOR& Model::getleftVector()
{
	return this->vecLeft;
}
