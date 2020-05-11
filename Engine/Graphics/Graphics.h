#pragma once
#include "ReadAdapter.h"
#include "Shader.h"
#include "Vertex.h"

class Graphics
{
public:
	bool Initialize(HWND hwnd, int width, int height);
	void Render();
private:
	bool InitializeDirectX(HWND hwnd, int width, int height);
	bool InitializeShaders();
	bool InitializeScene();

	Microsoft::WRL::ComPtr<ID3D11Device> device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> devicecontext;
	Microsoft::WRL::ComPtr<IDXGISwapChain> swapchain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> rendertargetview;

	VertexShader vertexshader;
	PixelShader pixelshader;

	Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer2;

	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depthstencilView;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> depthstencilBuffer;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthstencilState;
};

