#include "ReadAdapter.h"

std::vector<AdapterData> ReadAdapter::adapters;

std::vector<AdapterData> ReadAdapter::getAdapters()
{
	if (adapters.size() > 0)
		return adapters;

	Microsoft::WRL::ComPtr<IDXGIFactory> pFactory;

	HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(pFactory.GetAddressOf()));
	if (FAILED(hr))
	{
		ErrorLogger::Log(hr, "failed to create DXGIFactory for enumerating adapters.");
		exit(-1);
	}

	IDXGIAdapter* pAdapter;
	UINT index = 0;
	while (SUCCEEDED(pFactory->EnumAdapters(index, &pAdapter)))
	{
		adapters.push_back(AdapterData(pAdapter));
		index += 1;
	}
	return adapters;
}

AdapterData::AdapterData(IDXGIAdapter* pAdapter)
{
	this->pAdapter = pAdapter;
	HRESULT hr = pAdapter->GetDesc(&this->adapterdescription);
	if (FAILED(hr))
	{
		ErrorLogger::Log(hr, "Failed tog et description for IDXGIAdapter");
	}
}
