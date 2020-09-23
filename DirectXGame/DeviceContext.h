#pragma once
#include <d3d11.h>

class SwapChain;

class DeviceContext
{
public:

	DeviceContext(ID3D11DeviceContext* device_context);
	~DeviceContext();

	bool clearRenderTargetColor(SwapChain* swap_chain, float red, float green, float blue, float alpha);
	bool release();

protected:

private:

	// The ID3D11DeviceContext interface represents a device context which generates rendering commands.
	ID3D11DeviceContext* m_device_context = nullptr;
};

