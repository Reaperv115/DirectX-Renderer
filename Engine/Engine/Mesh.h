#pragma once
#include "../Graphics/Vertex.h"
#include "../Graphics/VertexBuffer.h"
#include "../Graphics/IndexBuffer.h"
#include "../Graphics/ConstantBuffer.h"
#include "../Utilities/ErrorLogger.h"
#include <sstream>
#include <fstream>
#include <iostream>

class Mesh
{
public:
	Mesh(ID3D11Device* device, ID3D11DeviceContext* deviceContext, std::vector<Vertex> vertices, std::vector<DWORD>& indices);
	Mesh(const Mesh& mesh);
	void Draw();
private:
	VertexBuffer<Vertex> vertexBuffer;
	IndexBuffer indexBuffer;
	ID3D11Device* device;
	ID3D11DeviceContext* devicecontext;

};

