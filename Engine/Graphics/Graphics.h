#pragma once
#include "ReadAdapter.h"
#include "Shader.h"
#include <WICTextureLoader.h>
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

	Model model;

	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depthstencilView;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> depthstencilBuffer;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthstencilState;
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerState;
	Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;

	int windowwidth;
	int windowheight;
	
	UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

};

