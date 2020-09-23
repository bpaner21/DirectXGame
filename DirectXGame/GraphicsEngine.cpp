#include "GraphicsEngine.h"

#include "SwapChain.h"
#include "DeviceContext.h"

GraphicsEngine::GraphicsEngine() {}

GraphicsEngine::~GraphicsEngine() {}

bool GraphicsEngine::init()
{

	// The driver type for Direct3D graphics
	D3D_DRIVER_TYPE driver_types[] {

		// Hardware driver, best performance and supports acceleration
		D3D_DRIVER_TYPE_HARDWARE,

		// WARP driver, high perofrmance software implementation
		D3D_DRIVER_TYPE_WARP,

		// Reference driver, software implementration that supports every Direct3D feature,
		// but values accuracy over performance speed
		D3D_DRIVER_TYPE_REFERENCE
	};

	UINT num_driver_types = ARRAYSIZE(driver_types);

	// The set of fatures targeted by a Direct3D device
	// Even if using only a single feature set, 
	// this must be an array to pass on to D3D11CreateDevice() below
	D3D_FEATURE_LEVEL feature_levels[] {

		// Targets features supported by Direct3D 11.0, including shader model 5.
		D3D_FEATURE_LEVEL_11_0
	};

	UINT num_feature_levels = ARRAYSIZE(feature_levels);

	HRESULT res = 0;

	ID3D11DeviceContext* m_imm_context = nullptr;

	// For loop to assign the best available driver from driver_types[] above
	for (UINT driver_type_index = 0; driver_type_index < num_driver_types;) {
		
		// Create a device that represents the display adapter.
		res = D3D11CreateDevice(nullptr, driver_types[driver_type_index], 0, 0, feature_levels, num_feature_levels, D3D11_SDK_VERSION, &m_d3d_device, &m_feature_level, &m_imm_context);

		if (SUCCEEDED(res)) { break; }

		++driver_type_index;
	}

	if (FAILED(res)) { return false; }

	m_imm_device_context = new DeviceContext(m_imm_context);

	// To create a Direct3D 11.1 device, retrieve the ID3D11Device1 interface
	// from the newly created ID3D11 device above
	m_d3d_device->QueryInterface(__uuidof(IDXGIDevice), (void**)&m_dxgi_device);

	m_dxgi_device->GetParent(__uuidof(IDXGIAdapter), (void**)&m_dxgi_adapter);
	m_dxgi_adapter->GetParent(__uuidof(IDXGIFactory), (void**)&m_dxgi_factory);

	return true;
}

bool GraphicsEngine::release()
{
	m_dxgi_device->Release();
	m_dxgi_adapter->Release();
	m_dxgi_factory->Release();

	m_imm_device_context->release();
	m_d3d_device->Release();

	return true;
}

GraphicsEngine* GraphicsEngine::get()
{
	static GraphicsEngine engine;

	return &engine;
}

SwapChain* GraphicsEngine::createSwapChain()
{
	return new SwapChain();
}

DeviceContext* GraphicsEngine::getImmediateDeviceContext()
{
	return this->m_imm_device_context;
}
