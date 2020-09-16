#pragma once

#include <d3d11.h>

class SwapChain
{
public:
	SwapChain();
	~SwapChain();

	// Initialize a SwapChain for a window
	bool init(HWND hwnd, UINT width, UINT height);

	// Release the SwapChain
	bool release();

protected:

private:
	IDXGISwapChain* m_swap_chain;
};

