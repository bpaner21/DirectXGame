#pragma once

#include <Windows.h>

class Window
{
public: 

	Window();

	// Initialize the window and assign it to m_hwnd
	bool init();

	// Is the program/ window still active and running
	bool isRunning();

	// Update the window and handle any new messages
	bool broadcast();

	// Release the window
	bool release();

	// EVENTS
	virtual void onCreate() = 0;
	virtual void onUpdate() = 0;
	virtual void onDestroy();

	// Return the client window rectangle from m_hwnd
	RECT getClientWindowRect();
	void setHWND(HWND hwnd);

protected:

	// Pointer release is handled in the release() function,
	// so there is no need for an explicit destructor
	virtual ~Window() = 0;

	// A handle to a Windows internal window data structure
	HWND m_hwnd = nullptr;
	bool m_is_running = true;

private:
};

