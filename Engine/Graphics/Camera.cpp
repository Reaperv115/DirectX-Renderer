#include "Camera.h"

Camera::Camera()
{
	this->pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
	this->posVector = XMLoadFloat3(&this->pos);
	this->rot = XMFLOAT3(0.0f, 0.0f, 0.0f);
	this->rotVector = XMLoadFloat3(&this->rot);
	this->UpdateViewMat();
}

void Camera::setprojectionValues(float fovdegs, float aspectrat, float nearz, float farz)
{
	float fovRads = (fovdegs / 360.0f) * XM_2PI;
	this->projectionMat = XMMatrixPerspectiveFovLH(fovRads, aspectrat, nearz, farz);
}

const DirectX::XMMATRIX& Camera::getviewMat() const
{
	return this->viewMat;
}

const DirectX::XMMATRIX& Camera::getprojectionMat() const
{
	return this->projectionMat;
}

const DirectX::XMVECTOR& Camera::getposVector() const
{
	return this->posVector;
}

const DirectX::XMFLOAT3& Camera::getposFloat3() const
{
	return this->pos;
}

const DirectX::XMVECTOR& Camera::getrotationVector() const
{
	return this->rotVector;
}

const DirectX::XMFLOAT3& Camera::getrotationFloat3() const
{
	return this->rot;
}

void Camera::setPosition(const XMVECTOR& pos)
{
	XMStoreFloat3(&this->pos, pos);
	this->posVector = pos;
	this->UpdateViewMat();
}

void Camera::setPosition(float x, float y, float z)
{
	this->pos = XMFLOAT3(x, y, z);
	this->posVector = XMLoadFloat3(&this->pos);
	this->UpdateViewMat();
}

void Camera::adjustPosition(const XMVECTOR& pos)
{
	this->posVector += pos;
	XMStoreFloat3(&this->pos, this->posVector);
	this->UpdateViewMat();
}

void Camera::adjustPosition(float x, float y, float z)
{
	this->pos.x += x;
	this->pos.y += y;
	this->pos.z += z;
	this->posVector = XMLoadFloat3(&this->pos);
	this->UpdateViewMat();
}

void Camera::setRotation(const XMVECTOR& rot)
{
	this->rotVector = rot;
	XMStoreFloat3(&this->rot, rot);
	this->UpdateViewMat();
}

void Camera::setRotation(float x, float y, float z)
{
	this->rot = XMFLOAT3(x, y, z);
	this->rotVector = XMLoadFloat3(&this->rot);
	this->UpdateViewMat();
}

void Camera::adjustRotation(const XMVECTOR& rot)
{
	this->rotVector += rot;
	XMStoreFloat3(&this->rot, this->rotVector);
	this->UpdateViewMat();
}

void Camera::adjustRotation(float x, float y, float z)
{
	this->rot.x += x;
	this->rot.y += y;
	this->rot.z += z;
	this->rotVector = XMLoadFloat3(&this->rot);
	this->UpdateViewMat();
}

void Camera::setlookatPos(XMFLOAT3 lookatPos)
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

const DirectX::XMVECTOR& Camera::getforwardVector()
{
	return this->vecForward;
}

const DirectX::XMVECTOR& Camera::getrightVector()
{
	return this->vecRight;
}

const DirectX::XMVECTOR& Camera::getbackwardVector()
{
	return this->vecBackward;
}

const DirectX::XMVECTOR& Camera::getleftVector()
{
	return this->vecLeft;
}

void Camera::UpdateViewMat()
{
	XMMATRIX camrotationMat = XMMatrixRotationRollPitchYaw(this->rot.x, this->rot.y, this->rot.z);
	XMVECTOR camTarg = XMVector3TransformCoord(this->DEFAULT_FORWARD_VECTOR, camrotationMat);
	camTarg += this->posVector;
	XMVECTOR upDir = XMVector3TransformCoord(this->DEFAULT_UP_VECTOR, camrotationMat);
	this->viewMat = XMMatrixLookAtLH(this->posVector, camTarg, upDir);

	XMMATRIX vecrotationMat = XMMatrixRotationRollPitchYaw(0.0f, this->rot.y, 0.0f);
	this->vecForward = XMVector3TransformCoord(this->DEFAULT_FORWARD_VECTOR, vecrotationMat);
	this->vecBackward = XMVector3TransformCoord(this->DEFAULT_BACKWARD_VECTOR, vecrotationMat);
	this->vecLeft = XMVector3TransformCoord(this->DEFAULT_LEFT_VECTOR, vecrotationMat);
	this->vecRight = XMVector3Transform(this->DEFAULT_RIGHT_VECTOR, vecrotationMat);
}
