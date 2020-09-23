#include "SwapChain.h"

#include "GraphicsEngine.h"

SwapChain::SwapChain() {}

SwapChain::~SwapChain() {}

bool SwapChain::init(HWND hwnd, UINT width, UINT height)
{
	// Retrieve the DirectX 11 device created in GraphicsEngine
	ID3D11Device* device = GraphicsEngine::get()->m_d3d_device;

	// A struct to describe the swap chain
	DXGI_SWAP_CHAIN_DESC desc;

	// Fill the memory block assigned to desc with zeroes
	// to prevent any rendering errors
	ZeroMemory(&desc, sizeof(desc));

	// A value that describes the number of buffers in the swap chain. 
	// When you call IDXGIFactory::CreateSwapChain to create a full-screen swap chain, 
	// you typically include the front buffer in this value.
	// 
	// UINT
	desc.BufferCount = 1;

	// UINT
	desc.BufferDesc.Width = width;
	desc.BufferDesc.Height = height;

	// DXGI_FORMAT_R8G8B8A8_UNORM 	
	// A four - component, 
	// 32 - bit unsigned - normalized - integer 
	// format that supports 8 bits per channel including alpha.
	// 
	// enum DXGI_FORMAT 
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	// UINT
	desc.BufferDesc.RefreshRate.Numerator = 60;
	desc.BufferDesc.RefreshRate.Denominator = 1;

	// A member of the DXGI_USAGE enumerated type 
	// that describes the surface usage and CPU access options for the back buffer. 
	// The back buffer can be used for shader input or render-target output.
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	// An HWND handle to the output window.
	// This member must not be NULL.
	//
	// HWND
	desc.OutputWindow = hwnd;

	// SampleDesc is a DXGI_SAMPLE_DESC structure
	// that describes multi-sampling parameters for a resource.

	// The number of multisamples per pixel.
	// UINT
	desc.SampleDesc.Count = 1;

	// The image quality level. 
	// The higher the quality, the lower the performance. 
	// The valid range is between zero and one less 
	// than the level returned by ID3D11Device::CheckMultisampleQualityLevels for Direct3D 11.
	//
	// UINT
	desc.SampleDesc.Quality = 0;

	// A Boolean value that specifies whether the output is in windowed mode. 
	// TRUE if the output is in windowed mode; otherwise, FALSE.
	desc.Windowed = true;

	HRESULT res = GraphicsEngine::get()->m_dxgi_factory->CreateSwapChain(device, &desc, &m_swap_chain);

	if (FAILED(res)) { return false;  }

	ID3D11Texture2D* buffer = nullptr;
	res = m_swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&buffer);

	if (FAILED(res)) { return false; }

	res = device->CreateRenderTargetView(buffer, nullptr, &m_rtv);
	buffer->Release();

	if (FAILED(res)) { return false; }

	return true;
}

bool SwapChain::present(bool vsync)
{
	m_swap_chain->Present(vsync, 0);

	return true;
}

bool SwapChain::release()
{
	m_swap_chain->Release();
	delete this;

	return true;
}
