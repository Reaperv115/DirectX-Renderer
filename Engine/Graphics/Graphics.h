#pragma once
#include "ReadAdapter.h"
#include "Shader.h"
#include "Vertex.h"
#include <WICTextureLoader.h>
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "Camera.h"
#include "ImGUI/imgui.h"
#include "ImGUI/imgui_impl_win32.h"
#include "ImGUI/imgui_impl_dx11.h"
#include "../Engine/Model.h"

class Graphics
{
public:
	bool Initialize(HWND hwnd, int width, int height);
	void Render();
	Camera camera;
private:
	bool InitializeDirectX(HWND hwnd);
	bool InitializeShaders();
	bool InitializeScene();

	Microsoft::WRL::ComPtr<ID3D11Device> device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> devicecontext;
	Microsoft::WRL::ComPtr<IDXGISwapChain> swapchain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> rendertargetview;

	VertexShader vertexshader;
	PixelShader pixelshader;
	ConstantBuffer<CB_VS_VertexShader> constantBuffer;

	VertexBuffer<Vertex> vertexBuffer;
	IndexBuffer indicesBuffer;

	VertexShader cubevertexShader;
	PixelShader cubepixelShader;
	VertexBuffer<Vertex> cubevertexBuffer;
	IndexBuffer cubeindexBuffer;

	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depthstencilView;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> depthstencilBuffer;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthstencilState;
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerState;
	Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;

	int windowwidth;
	int windowheight;

	Model model;
	std::vector<DirectX::XMFLOAT3> vertexes;
	std::vector<DirectX::XMFLOAT2> UVs;
	std::vector<DirectX::XMFLOAT3> normals;
};

