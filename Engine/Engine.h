#pragma once
#include "Windows/WindowContainer.h"
class Engine : WindowContainer
{
public:
	bool Initialize(HINSTANCE hInst, std::string windowTitle, std::string windowClass, int wid, int height);
	bool ProcessMessages();
	void Update();
	void Render();
	void releaseData();
};