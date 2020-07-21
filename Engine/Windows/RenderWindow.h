#pragma once
#include "../Utilities/ErrorLogger.h"
#include <memory>
#include "../Graphics/Graphics.h"

class WindowContainer;

class RenderWindow
{
public:
	bool Initialize(WindowContainer * pwindowContainer, HINSTANCE hInst, std::string windowTitle, std::string windowClass, int width, int height);
	bool ProcessMessages();
	HWND getHWND() const;
	~RenderWindow();
private:
	void RegisterWindowClass();
	HWND handle = NULL; //handle to this window
	HINSTANCE hInst = NULL; // handle to application instance
	std::string windowTitle = ""; 
	std::wstring windowtitleW = L""; // wide string rep of window title
	std::string windowClass = "";
	std::wstring windowclassW = L""; // wide string rep of window class name
	int width = 0;
	int height = 0;
};

