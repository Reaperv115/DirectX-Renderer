#include <iostream>
#include "Model.h"


bool Model::LoadModel(const std::string& filepath, std::vector<DirectX::XMFLOAT3>& outVerts, 
					 std::vector<DirectX::XMFLOAT2>& outUvs,
					 std::vector<DirectX::XMFLOAT3>& outNorms)
{
	std::stringstream ss;
	std::ifstream file(filepath);
	std::string line = "";
	std::string prefix = "";

	if (!file.is_open())
	{
		ErrorLogger::Log("Could not open the file specified.");
		return false;
	}

	while (std::getline(file, line))
	{
		ss.clear();
		ss.str(line);
		ss >> prefix;

		
		if (prefix == "v")
		{
			DirectX::XMFLOAT3 vertex;
			ss >> vertex.x >> vertex.y >> vertex.z;
			tvertPositions.push_back(vertex);
		}
		else if (prefix == "vt")
		{
			DirectX::XMFLOAT2 vertTex;
			ss >> vertTex.x >> vertTex.y;
			tuvs.push_back(vertTex);
		}
		else if (prefix == "vn")
		{
			DirectX::XMFLOAT3 normals;
			ss >> normals.x >> normals.y >> normals.z;
			tnorms.push_back(normals);
		}
		else if (prefix == "f")
		{
			int counter = 0;
			while (ss >> tInt)
			{
				if (counter == 0)
					vertexposIndices.push_back(tInt);
				else if (counter == 1)
					uvIndices.push_back(tInt);
				else if (counter == 2)
					normIndices.push_back(tInt);

				if (ss.peek() == '/')
				{
					++counter;
					ss.ignore(1, '/');
				}
				else if (ss.peek() == ' ')
				{
					++counter;
					ss.ignore(1, ' ');
				}

				if (counter > 2)
					counter = 0;
				
			}
		}

		std::cout << line << "\n";
		std::cout << "# of vertices: " << vertices.size() << "\n";
	}

	vertices.resize(vertexposIndices.size());

	for (size_t i = 0; i < vertices.size(); ++i)
	{
		vertices[i]._position = tvertPositions[vertexposIndices[i] - 1];
		vertices[i].TexCoord = tuvs[uvIndices[i] - 1];
		vertices[i]._normal = tnorms[normIndices[i] - 1];

		++i_numVerts;
	}

	return true;
}

std::vector<Vertex> Model::getVertices()
{
	return vertices;
}

unsigned int Model::getnumVerts()
{
	return i_numVerts;
}

std::vector<unsigned int> Model::getIndices()
{
	return vertexposIndices;
}

unsigned int Model::getnumIndices()
{
	return vertexposIndices.size();
}