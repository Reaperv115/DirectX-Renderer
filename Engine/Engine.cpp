#include "Engine.h"
bool Engine::Initialize(HINSTANCE hInst, std::string windowTitle, std::string windowClass, int width, int height)
{
	if (!this->renderWindow.Initialize(this, hInst, windowTitle, windowClass, width, height))
		return false;

	if (!gfx.Initialize(this->renderWindow.getHWND(), width, height))
		return false;

	return true;
}

bool Engine::ProcessMessages()
{
	return this->renderWindow.ProcessMessages();
}

void Engine::Update()
{
	while (!keyboard.charbufferisEmpty())
	{
		unsigned char ch = keyboard.readChar();
	}

	while (!keyboard.keybufferisEmpty())
	{
		keyboardEvent e = keyboard.readKey();
		unsigned char keycode = e.GetkeyCode();
	}

	while (!mouse.eventbufferisEmpty())
	{
		MouseEvent me = mouse.readEvent();
		if (me.getType() == MouseEvent::EventType::RAW_MOVE)
		{
			std::string msg = "X: ";
			msg += std::to_string(me.GetPosX());
			msg += ", ";
			msg += "Y: ";
			msg += std::to_string(me.GetPosY());
			msg += "\n";
			OutputDebugStringA(msg.c_str());
		}
	}
}

void Engine::Render()
{
	gfx.Render();
}
