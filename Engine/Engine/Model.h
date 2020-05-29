#pragma once
#include "../Graphics/Vertex.h"
#include "../Utilities/ErrorLogger.h"
#include <string>
#include <vector>
#include <sstream>
#include <fstream>


class Model
{
public:
	bool LoadModel(const std::string& filepath, std::vector<DirectX::XMFLOAT3>& outVerts,
		 std::vector<DirectX::XMFLOAT2>& outUvs,
		 std::vector<DirectX::XMFLOAT3>& outNorms);

public:
	std::vector<Vertex> getVertices();
	unsigned int getnumVerts();
	std::vector<unsigned int> getIndices();
	unsigned int getnumIndices();

public:
	std::vector<DirectX::XMFLOAT3> vertexes;
	std::vector<DirectX::XMFLOAT2> UVs;
	std::vector<DirectX::XMFLOAT3> normals;

private:
	unsigned int i_numVerts = 0;
	std::vector<Vertex> vertices;

	std::vector<unsigned int> vertexposIndices;
	std::vector<unsigned int> uvIndices;
	std::vector<unsigned int> normIndices;

	std::vector<DirectX::XMFLOAT3> tvertPositions;
	std::vector<DirectX::XMFLOAT2> tuvs;
	std::vector<DirectX::XMFLOAT3> tnorms;
	unsigned int tInt;
};

