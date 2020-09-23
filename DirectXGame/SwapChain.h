#pragma once

#include <d3d11.h>

class DeviceContext;

class SwapChain
{
public:

	SwapChain();
	~SwapChain();

	// Initialize a SwapChain for a window
	bool init(HWND hwnd, UINT width, UINT height);

	bool present(bool vsync);

	// Release the SwapChain
	bool release();

protected:

private:

	// An IDXGISwapChain interface implements one or more surfaces 
	// for storing rendered data before presenting it to an output.
	IDXGISwapChain* m_swap_chain = nullptr;

	// A render-target-view interface identifies the render-target 
	// subresources that can be accessed during rendering.
	ID3D11RenderTargetView* m_rtv = nullptr;

	friend class DeviceContext;
};

