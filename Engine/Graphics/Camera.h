#pragma once
#include <DirectXMath.h>
using namespace DirectX;

class Camera
{
public:
	Camera();
	void setprojectionValues(float fovdegs, float aspectrat, float enarz, float farz);

	const XMMATRIX& getviewMat() const;
	const XMMATRIX& getprojectionMat() const;
	
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
	void UpdateViewMat();
	XMVECTOR posVector;
	XMVECTOR rotVector;
	XMFLOAT3 pos;
	XMFLOAT3 rot;
	XMMATRIX viewMat;
	XMMATRIX projectionMat;

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

