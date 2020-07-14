#include "Graphics.h"





bool Graphics::Initialize(HWND hwnd, int width, int height)
{
	this->windowwidth = width;
	this->windowheight = height;

	if (!InitializeDirectX(hwnd))
		return false;

	if (!InitializeShaders())
		return false;

	if (!InitializeScene())
		return false;

	// SETUP IMGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplWin32_Init(hwnd);
	ImGui_ImplDX11_Init(this->device.Get(), this->devicecontext.Get());
	ImGui::StyleColorsDark();

	return true;
}

void Graphics::Render()
{
	float bgcolor[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	this->devicecontext->ClearRenderTargetView(this->rendertargetview.Get(), bgcolor);
	this->devicecontext->ClearDepthStencilView(this->depthstencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	this->devicecontext->IASetInputLayout(this->vertexshader.getLayout());
	this->devicecontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	this->devicecontext->OMSetDepthStencilState(this->depthstencilState.Get(), 0);
	this->devicecontext->PSSetSamplers(0, 1, this->samplerState.GetAddressOf());
	this->devicecontext->VSSetShader(this->vertexshader.getShader(), NULL, 0);
	this->devicecontext->PSSetShader(this->pixelshader.getShader(), NULL, 0);

	
	this->model.Draw(camera.getviewMat() * camera.getprojectionMat());
	

	// start the Dear ImGui frame
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	//create ImGui test window
	ImGui::Begin("Test");
	ImGui::End();

	// Assemble together draw data
	ImGui::Render();

	// render draw data
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	this->swapchain->Present(1, NULL);
}

bool Graphics::InitializeDirectX(HWND hwnd)
{
	std::vector<AdapterData> adapters = ReadAdapter::getAdapters();

	if (adapters.size() < 1)
	{
		ErrorLogger::Log("No DXGI adapters found");
		return false;
	}
	DXGI_SWAP_CHAIN_DESC swapchaindescription;
	ZeroMemory(&swapchaindescription, sizeof(DXGI_SWAP_CHAIN_DESC));

	swapchaindescription.BufferDesc.Width = this->windowwidth;
	swapchaindescription.BufferDesc.Height = this->windowheight;
	swapchaindescription.BufferDesc.RefreshRate.Numerator = 60;
	swapchaindescription.BufferDesc.RefreshRate.Denominator = 1;
	swapchaindescription.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	swapchaindescription.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapchaindescription.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	swapchaindescription.SampleDesc.Count = 1;
	swapchaindescription.SampleDesc.Quality = 0;

	swapchaindescription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapchaindescription.BufferCount = 1;
	swapchaindescription.OutputWindow = hwnd;
	swapchaindescription.Windowed = TRUE;
	swapchaindescription.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapchaindescription.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

#if defined(_DEBUG)
	creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	HRESULT hr;
	hr = D3D11CreateDeviceAndSwapChain( adapters[0].pAdapter, //IDXGI adapter
								   D3D_DRIVER_TYPE_UNKNOWN,
								   NULL, // for software driver type
								   creationFlags, // flags for runtime layers
								   NULL, // feature levels array
								   0, // # of feature levels in array
								   D3D11_SDK_VERSION,
								   &swapchaindescription, // swapchain description
								   this->swapchain.GetAddressOf(), // swapchain address
								   this->device.GetAddressOf(), // device address
								   NULL, // supported feature levels
								   this->devicecontext.GetAddressOf()); // device context address

	if (FAILED(hr))
	{
		ErrorLogger::Log(hr, "Failed to initialize device and swapchain");
		return false;
	}

	Microsoft::WRL::ComPtr<ID3D11Texture2D> backbuffer;
	hr = this->swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(backbuffer.GetAddressOf()));
	if (FAILED(hr))
	{
		ErrorLogger::Log(hr, "GetBuffer failed");
		return false;
	}

	hr = this->device->CreateRenderTargetView(backbuffer.Get(), NULL, this->rendertargetview.GetAddressOf());
	if (FAILED(hr))
	{
		ErrorLogger::Log(hr, "Failed to create render target view");
		return false;
	}

	D3D11_TEXTURE2D_DESC depthstencildesc;
	depthstencildesc.Width = this->windowwidth;
	depthstencildesc.Height = this->windowheight;
	depthstencildesc.MipLevels = 1;
	depthstencildesc.ArraySize = 1;
	depthstencildesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthstencildesc.SampleDesc.Count = 1;
	depthstencildesc.SampleDesc.Quality = 0;
	depthstencildesc.Usage = D3D11_USAGE_DEFAULT;
	depthstencildesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthstencildesc.CPUAccessFlags = 0;
	depthstencildesc.MiscFlags = 0;

	hr = this->device->CreateTexture2D(&depthstencildesc, NULL, this->depthstencilBuffer.GetAddressOf());
	if (FAILED(hr))
	{
		ErrorLogger::Log(hr, "Failed to create depth stencil buffer");
		return false;
	}

	hr = this->device->CreateDepthStencilView(this->depthstencilBuffer.Get(), NULL, this->depthstencilView.GetAddressOf());

	this->devicecontext->OMSetRenderTargets(1, this->rendertargetview.GetAddressOf(), this->depthstencilView.Get());

	D3D11_DEPTH_STENCIL_DESC depthstencilDesc;
	ZeroMemory(&depthstencilDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));

	depthstencilDesc.DepthEnable = true;
	depthstencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthstencilDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;

	hr = this->device->CreateDepthStencilState(&depthstencilDesc, this->depthstencilState.GetAddressOf());
	if (FAILED(hr))
	{
		ErrorLogger::Log(hr, "Failed to create depth stencil state");
		return false;
	}

	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = this->windowwidth;
	viewport.Height = this->windowheight;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	this->devicecontext->RSSetViewports(1, &viewport);

	// create rasterizer state
	D3D11_RASTERIZER_DESC rasterizerDesc;
	ZeroMemory(&rasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));
	rasterizerDesc.FillMode = D3D11_FILL_SOLID;
	rasterizerDesc.CullMode = D3D11_CULL_BACK;
	hr = this->device->CreateRasterizerState(&rasterizerDesc, this->rasterizerState.GetAddressOf());
	if (FAILED(hr))
	{
		ErrorLogger::Log(hr, "Failed to create rasterizer state");
		return false;
	}

	D3D11_SAMPLER_DESC sampleDesc;
	ZeroMemory(&sampleDesc, sizeof(sampleDesc));
	sampleDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampleDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampleDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampleDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampleDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampleDesc.MinLOD = 0;
	sampleDesc.MaxLOD = D3D11_FLOAT32_MAX;
	hr = this->device->CreateSamplerState(&sampleDesc, this->samplerState.GetAddressOf()); // create sampler state
	if (FAILED(hr))
	{
		ErrorLogger::Log(hr, "Failed to create sampler state");
		return false;
	}

	return true;
}

bool Graphics::InitializeShaders()
{
	std::wstring shaderfolder = L"";
#pragma region determineShaderPath
	if (IsDebuggerPresent() == TRUE)
	{
#ifdef _DEBUG
	#ifdef _WIN64
		shaderfolder = L"../x64/debug/";
	#else
		shaderfolder = L"../Debug/";
	#endif
	#else
	#ifdef _WIN64
		shaderfolder = L"../x64/Release/";
	#else
		shaderfolder = L"../Release/";
	#endif
#endif
	}

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	UINT numElements = _ARRAYSIZE(layout);

	if (!vertexshader.Initialize(this->device, shaderfolder + L"VertexShader.cso", layout, numElements))
		return false;

	if (!pixelshader.Initialize(this->device, shaderfolder + L"PixelShader.cso"))
		return false;
	

	return true;
}

bool Graphics::InitializeScene()
{
	// load texture
	HRESULT hr = DirectX::CreateWICTextureFromFile(this->device.Get(), L"textures/bloody slayer mark.jpg", nullptr, slayersmark.GetAddressOf());
	if (FAILED(hr))
	{
		ErrorLogger::Log(hr, "failed to create WICTexture");
		return false;
	}

	// Initialize constant buffer(s)
	hr = this->VSconstantBuffer.Initialize(this->device.Get(), this->devicecontext.Get());
	if (FAILED(hr))
	{
		ErrorLogger::Log(hr, "Failed to initialize the constant buffer");
		return false;
	}

	// Initialize Models
	if (model.Initialize(this->device.Get(), this->devicecontext.Get(), this->slayersmark.Get(), VSconstantBuffer))
		return false;

	camera.setPosition(0.0f, 0.0f, -2.0f);
	camera.setprojectionValues(90.0f, static_cast<float>(windowwidth) / static_cast<float>(windowheight), 0.1f, 1000.0f);

	return true;
}
