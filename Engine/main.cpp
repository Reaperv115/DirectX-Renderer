#include "Engine.h"


int APIENTRY wWinMain(_In_ HINSTANCE hInst,
	_In_opt_ HINSTANCE hprevInst,
	_In_ LPWSTR cmdLine,
	_In_ int cmdShow)
{
	Engine engine;
	if (engine.Initialize(hInst, "Engine", "Engine", 1280, 800))
	{
		while (engine.ProcessMessages())
		{
			engine.Update();
			engine.Render();
		}
	}

	return 0;
}