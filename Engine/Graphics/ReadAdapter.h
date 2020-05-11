#pragma once
#include "../Utilities/ErrorLogger.h"
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "DirectXTK.lib")
#pragma comment(lib, "DXGI.lib")
#include <wrl/client.h>
#include <vector>

class AdapterData
{
public:
	AdapterData(IDXGIAdapter* pAdapter);
	IDXGIAdapter* pAdapter = nullptr;
	DXGI_ADAPTER_DESC adapterdescription;
};

class ReadAdapter
{
public:
	static std::vector<AdapterData> getAdapters();
private:
	static std::vector<AdapterData> adapters;
};

