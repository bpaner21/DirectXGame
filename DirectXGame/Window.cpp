#include "Window.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

Window::Window() {}

Window::~Window() {}

bool Window::init() {

	// Create an object contiaining all the window class information for RegisterClassEX()
	WNDCLASSEX wc;

	// The number of extra bytes to allocate following the window-class structure. 
	// The system initializes the bytes to zero by default.
	// int
	wc.cbClsExtra = 0;

	// The size, in bytes, of this structure.
	// Set this member to sizeof(WNDCLASSEX).
	// Be sure to set this member before calling the GetClassInfoEx function.
	//
	// UINT - 32-bit unisgned integer
	wc.cbSize = sizeof(WNDCLASSEX);

	// The number of extra bytes to allocate following the window instance. 
	// The system initializes the bytes to zero. 
	// If an application uses WNDCLASSEX to register a dialog box created by using the CLASS directive in the resource file, 
	// it must set this member to DLGWINDOWEXTRA.
	//
	// int
	wc.cbWndExtra = 0;

	// A handle to the class background brush.
	// Can be a handle to a brush used for painting the background or a color value.
	// HBRUSH - A handle to a brush
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;

	// A handle to the class cursor.
	// This member must be a handle to a cursor resource.
	// If this member is NULL, an application must explicitly set the cursor shape whenever the mouse moves into the application's window.
	//
	// HCURSOR - A handle to a cursor
	wc.hCursor = LoadCursorW(0, IDC_ARROW);

	// A handle to the class icon.
	// This member must be a handle to an icon resource.
	// If this member is NULL, the system provides a default icon.
	//
	// HICON - A handle to an icon
	wc.hIcon = LoadIconW(0, IDI_APPLICATION);

	// A handle to a small icon that is associated with the window class.
	// If this member is NULL, the system searches the icon resource specified 
	// by the hIcon member for an icon of the appropriate size to use as the small icon.
	//
	// HICON
	wc.hIconSm = LoadIconW(0, IDI_APPLICATION);

	// A handle to the instance that contains the window procedure for the class.
	// HINSTANCE - A handle to an instance. The base address of the memory
	wc.hInstance = 0;

	// A pointer to a null-terminated string or is an atom. 
	// If lpszClassName is a string, it specifies the window class name.
	// The class name can be any name registered with RegisterClass or RegisterClassEx, or any of the predefined control - class names.
	// The maximum length for lpszClassName is 256. If lpszClassName is greater than the maximum length, the RegisterClassEx function will fail.
	//
	// LPCWSTR - A 32-bit pointer to a constant string of 16-bit UNICODE characters, which MAY be null-terminated
	// The 'L' prefix casts the string into 16-bit wchar_t wide characters
	wc.lpszClassName = L"MyWindowClass";

	// Pointer to a null-terminated character string that specifies the resource 
	// name of the class menu, as the name appears in the resource file.
	// If you use an integer to identify the menu, use the MAKEINTRESOURCE macro. 
	// If this member is NULL, windows belonging to this class have no default menu.
	//
	// LPCWSTR
	wc.lpszMenuName = L"";

	// The class style(s). 
	// This member can be any combination of the Class Styles.
	// UINT
	wc.style = 0;

	// A pointer to the window procedure. 
	// You must use the CallWindowProc function to call the window procedure.
	// WNDPROC
	wc.lpfnWndProc = &WndProc;

	// Register the wc window class object for use in CreateWindowEX()
	// If the registration of the class fails, return false
	if (!::RegisterClassExW(&wc)) { return false; }

	// Creation of the window
	m_hwnd = ::CreateWindowExW(WS_EX_OVERLAPPEDWINDOW, L"MyWindowClass", L"My DirectX Application", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768, 0, 0, 0, this);

	// If the window creation fails, return false
	if (m_hwnd == 0) { return false; }

	// Show and update the window
	::ShowWindow(m_hwnd, SW_SHOW);
	::UpdateWindow(m_hwnd);

	// Set this flag to true to indicate that the window is initialized and running
	m_is_running = true;

	return true;
}

bool Window::isRunning()
{
	return m_is_running;
}

bool Window::broadcast()
{
	MSG msg;

	this->onUpdate();

	// Dispatches incoming sent messages, checks the thread message queue for a posted message, and retrieves the message(if any exist).
	while (::PeekMessageW(&msg, 0, 0, 0, PM_REMOVE) > 0) {

		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}

	// Create a brief pause in the update loop to reduce the load on CPU
	Sleep(0);

	return true;
}

bool Window::release() {

	// Destroy the window
	if (!::DestroyWindow(m_hwnd)) { return false; }

	return true;
}

void Window::onDestroy()
{
	m_is_running = false;
}

RECT Window::getClientWindowRect()
{
	RECT rc;
	::GetClientRect(this->m_hwnd, &rc);

	return rc;
}

void Window::setHWND(HWND hwnd)
{
	this->m_hwnd = hwnd;
}


// An application-defined function that process messages sent to a window
// WNDPROC type defines a pointer to this callback function.

// The application defines the name of the function as well,
// in this case WndProc

// HWND hwnd - a handle to the window.

// UINT msg - the message.

// WPARAM wparam - additional message info,
// The contents of which are defined based on the value of the UINT parameter

// LPRAMA lparam - also additional message info,
// and also defined based on the value of the UINT parameter

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {

	switch (msg) {
		
		case WM_CREATE:
		{
			// Event fired when the window will be created

			// Get the 'this' pointer passed in CreateWindowEx()
			Window* window = (Window*)((LPCREATESTRUCT)lparam)->lpCreateParams;

			// Save the 'this' pointer in a special data structure identified by hwnd
			SetWindowLongW(hwnd, GWLP_USERDATA, (LONG_PTR)window);

			window->setHWND(hwnd);

			window->onCreate();
			break;
		}

		case WM_DESTROY:
		{
			// Event fired when the window will be destroyed

			// Recover 'this' pointer from hwnd data structure created in case WM_CREATE
			Window* window = (Window*)GetWindowLongW(hwnd, GWLP_USERDATA);

			window->onDestroy();
			::PostQuitMessage(0);
			break;
		}
		default:
		{
			return ::DefWindowProcW(hwnd, msg, wparam, lparam);
		}
	}

	return NULL;
}