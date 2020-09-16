#pragma once

#include <d3d11.h>

class SwapChain;

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

protected:

private:
	ID3D11Device* m_d3d_device;
	D3D_FEATURE_LEVEL m_feature_level;
	ID3D11DeviceContext* m_imm_context;
	IDXGIDevice* m_dxgi_device;
	IDXGIAdapter* m_dxgi_adapter;
	IDXGIFactory* m_dxgi_factory;

	friend class SwapChain;
};

