#pragma once

#include <d3d11.h>

class SwapChain;
class DeviceContext;

class GraphicsEngine
{
public:
	GraphicsEngine();
	~GraphicsEngine();
	
	// Initialize the graphics engine and the DirectX device;
	bool init();

	// Release all the loaded resources
	bool release();

	// Singleton pattern insures only 
	// a single instance of the GraphicsEngine is
	// running at any given time
	static GraphicsEngine* get();

	SwapChain* createSwapChain();
	DeviceContext* getImmediateDeviceContext();

protected:

private:

	// The device interface represents a virtual adapter;
	// it is used to create resources
	ID3D11Device* m_d3d_device = nullptr;

	// The set of features targeted by a Direct3D device.
	D3D_FEATURE_LEVEL m_feature_level;

	// An IDXGIDevice interface implements a derived class for DXGI (Microsoft DirectX Graphics Infrastructure) objects that produce image data.
	IDXGIDevice* m_dxgi_device = nullptr;

	// The IDXGIAdapter interface represents a display subsystem (including one or more GPUs, DACs and video memory).
	IDXGIAdapter* m_dxgi_adapter = nullptr;

	// An IDXGIFactory interface implements methods for generating DXGI objects (which handle full screen transitions).
	IDXGIFactory* m_dxgi_factory = nullptr;

	DeviceContext* m_imm_device_context = nullptr;

	friend class SwapChain;
};

