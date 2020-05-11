#include "WindowContainer.h"

bool RenderWindow::Initialize(WindowContainer* pwindowContainer, HINSTANCE hInst, std::string windowTitle, std::string windowClass, int width, int height)
{
	this->hInst = hInst;
	this->width = width;
	this->height = height;
	this->windowTitle = windowTitle;
	this->windowtitleW = StringConverter::StringtoWideString(this->windowTitle);
	this->windowClass = windowClass;
	this->windowclassW = StringConverter::StringtoWideString(this->windowClass);

	this->RegisterWindowClass();

	this->handle = CreateWindowEx(0,// extended window style, we are using the default
		this->windowclassW.c_str(), // window class name
		this->windowtitleW.c_str(), // window title
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, // windows style
		0, // window X position
		0, // window Y position
		this->width, // window width
		this->height, // window height
		NULL, // handle to the parent of this window
		NULL, // handle to menu or child window identifier. Can be set to NULL and menu in WindowClassEx
		this->hInst, // handle to the instance of module to be used with this window
		pwindowContainer); // param to create window

	if (this->handle == NULL)
	{
		ErrorLogger::Log(GetLastError(), "CreateWindowEX failed for window: " + this->windowTitle);
		return false;
	}

	// bring the window up on the screen and set it as main focus
	ShowWindow(this->handle, SW_SHOW);
	SetForegroundWindow(this->handle);
	SetFocus(this->handle);

	return true;
}

bool RenderWindow::ProcessMessages()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	while (PeekMessage(&msg, // where to store the message (if one exists)
		this->handle, // handle to window we are checking messages for
		0, // minimum filter msg value
		0, // maximum filter msg value
		PM_REMOVE)) // remove message after capturing it via PeekMessage
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// check if window was closed
	if (msg.message == WM_NULL)
	{
		if (!IsWindow(this->handle))
		{
			this->handle = NULL; // message processing loop takes care of destroying the window
			UnregisterClass(this->windowclassW.c_str(), this->hInst);
			return false;
		}
	}
	return true;
}

HWND RenderWindow::getHWND() const
{
	return this->handle;
}

LRESULT CALLBACK HandleMessageRedirect(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CLOSE:
	{
		DestroyWindow(hwnd);
		return 0;
	}
	default:
	{
		WindowContainer* const pwindow = reinterpret_cast<WindowContainer*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
		return pwindow->WindowProc(hwnd, uMsg, wParam, lParam);
	}
	}
}

LRESULT CALLBACK HandleMessageSetup(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_NCCREATE:
	{
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		WindowContainer* pwindow = reinterpret_cast<WindowContainer*>(pCreate->lpCreateParams);
		if (pwindow == nullptr)
		{
			ErrorLogger::Log("Critical Error: Pointer to window container is null during WM_NCCREATE.");
			exit(-1);
		}
		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pwindow));
		SetWindowLongPtr(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(HandleMessageRedirect));
		return pwindow->WindowProc(hwnd, uMsg, wParam, lParam);
	}
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}

RenderWindow::~RenderWindow()
{
	if (this->handle != NULL)
	{
		UnregisterClass(this->windowclassW.c_str(), this->hInst);
		DestroyWindow(handle);
	}
}

void RenderWindow::RegisterWindowClass()
{
	WNDCLASSEX wc; // our window class (this needs to be filled before our window can be created)
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC; // flags [Redraw on width/height change from resize/movement]
	wc.lpfnWndProc = HandleMessageSetup; // Pointer to Window Proc function for handling messages from this window
	wc.cbClsExtra = 0; // # of extra bytes to allocate following the window-class structure.
	wc.cbWndExtra = 0; // # of extra bytes to allocate following the window instance.
	wc.hInstance = this->hInst; // handle to the instance that contains the window procedure
	wc.hIcon = NULL; // handle to the class icon. Must be a handle to an icon resource
	wc.hIconSm = NULL; // handle to the small icon for this class
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); // default cursor - if we leave this null, we have to explicitly set the cursor
	wc.hbrBackground = NULL; // handle to the class background brush for the window's background color
	wc.lpszMenuName = NULL; // pointer to a null terminated character string for the menu
	wc.lpszClassName = this->windowclassW.c_str(); // pointer to null terminated string of our class name
	wc.cbSize = sizeof(WNDCLASSEX); // need to fill int he size for our struct for cbsize
	RegisterClassEx(&wc); // register the class so that it is usable
}
