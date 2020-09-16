#pragma once

#include <Windows.h>

class Window
{
public: 
	Window();

	// Initialize the window
	bool init();

	bool isRun();

	bool broadcast();

	// Release the window
	bool release();

	// EVENTS
	virtual void onCreate() = 0;
	virtual void onUpdate() = 0;
	virtual void onDestroy();

	RECT getClientWindowRect();
	void setHWND(HWND hwnd);

protected:
	virtual ~Window() = 0;
	HWND m_hwnd = nullptr;
	bool m_is_run = true;
};

