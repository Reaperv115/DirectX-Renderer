#pragma once
#include <DirectXMath.h>

struct Vertex
{
	Vertex(){}
	Vertex(float x, float y, float z, 
		   float u, float v, 
		   float nx, float ny, float nz, 
		   float fx, float fy, float fz)
		: _position(x, y, z), TexCoord(u, v), 
		  _normal(nx, ny, nz), _face(fx, fy, fz){}
	Vertex(float x, float y, float z,
					float u, float v)
		: _position(x, y, z), TexCoord(u, v){}

	DirectX::XMFLOAT3 _position;
	DirectX::XMFLOAT2 TexCoord;
	DirectX::XMFLOAT3 _normal;
	DirectX::XMFLOAT3 _face;
};

