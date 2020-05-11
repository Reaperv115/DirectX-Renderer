#include "Shader.h"

bool VertexShader::Initialize(Microsoft::WRL::ComPtr<ID3D11Device>& device, std::wstring shaderpath, D3D11_INPUT_ELEMENT_DESC* layoutdesc, UINT numElements)
{
	HRESULT hr = D3DReadFileToBlob(shaderpath.c_str(), this->shaderBuffer.GetAddressOf());
	if (FAILED(hr))
	{
		std::wstring errormsg = L"Failed to load shader: ";
		errormsg += shaderpath;
		ErrorLogger::Log(hr, errormsg);
		return false;
	}

	hr = device->CreateVertexShader(this->shaderBuffer.Get()->GetBufferPointer(), this->shaderBuffer.Get()->GetBufferSize(), NULL, this->shader.GetAddressOf());
	if (FAILED(hr))
	{
		std::wstring errormsg = L"failed to create shader: ";
		errormsg += shaderpath;
		ErrorLogger::Log(hr, errormsg);
		return false;
	}

	hr = device->CreateInputLayout(layoutdesc, numElements, this->shaderBuffer->GetBufferPointer(), this->shaderBuffer->GetBufferSize(), this->inputLayout.GetAddressOf());
	if (FAILED(hr))
	{
		ErrorLogger::Log(hr, "Failed to create input layout");
		return false;
	}

	return true;
}

ID3D11VertexShader* VertexShader::getShader()
{
	return this->shader.Get();
}

ID3D10Blob* VertexShader::getBuffer()
{
	return this->shaderBuffer.Get();
}

ID3D11InputLayout* VertexShader::getLayout()
{
	return this->inputLayout.Get();
}

bool PixelShader::Initialize(Microsoft::WRL::ComPtr<ID3D11Device>& device, std::wstring shaderpath)
{
	HRESULT hr = D3DReadFileToBlob(shaderpath.c_str(), this->shaderBuffer.GetAddressOf());
	if (FAILED(hr))
	{
		std::wstring errormsg = L"Failed to load shader: ";
		errormsg += shaderpath;
		ErrorLogger::Log(hr, errormsg);
		return false;
	}

	hr = device->CreatePixelShader(this->shaderBuffer.Get()->GetBufferPointer(), this->shaderBuffer.Get()->GetBufferSize(), NULL, this->shader.GetAddressOf());
	if (FAILED(hr))
	{
		std::wstring errormsg = L"Failed to create pixel shader: ";
		errormsg += shaderpath;
		ErrorLogger::Log(hr, errormsg);
		return false;
	}

	return true;
}

ID3D11PixelShader* PixelShader::getShader()
{
	return this->shader.Get();
}

ID3D10Blob* PixelShader::getBuffer()
{
	return this->shaderBuffer.Get();
}
