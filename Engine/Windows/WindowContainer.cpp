#include "WindowContainer.h"

WindowContainer::WindowContainer()
{
	static bool rawinputInitialized = false;
	if (rawinputInitialized == false)
	{
		RAWINPUTDEVICE rawinputDevice;

		rawinputDevice.usUsagePage = 0x01;
		rawinputDevice.usUsage = 0x02;
		rawinputDevice.dwFlags = 0;
		rawinputDevice.hwndTarget = NULL;

		if (RegisterRawInputDevices(&rawinputDevice, 1, sizeof(rawinputDevice)) == FALSE)
		{
			ErrorLogger::Log(GetLastError(), "Failed to register raw input devices");
			exit(-1);
		}
		rawinputInitialized = true;
	}
}

LRESULT WindowContainer::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_KEYUP:
	{
		unsigned char keycode = static_cast<unsigned char>(wParam);
		keyboard.onkeyReleased(keycode);
		
		return 0;
	}
	case WM_KEYDOWN:
	{
		unsigned char keycode = static_cast<unsigned char>(wParam);
		if (keyboard.iskeyautoRepeat())
		{
			keyboard.onkeyPressed(keycode);
		}
		else
		{
			const bool wasPressed = lParam & 0x40000000;
			if (!wasPressed)
			{
				keyboard.onkeyPressed(keycode);
			}
		}
		return 0;
	}
	case WM_CHAR:
	{
		unsigned char ch = static_cast<unsigned char>(wParam);
		if (keyboard.ischarsautoRepeat())
		{
			keyboard.onChar(ch);
		}
		else
		{
			const bool wasPressed = lParam & 0x40000000;
			if (!wasPressed)
			{
				keyboard.onChar(ch);
			}
		}
		return 0;
	} //NOTE: use GET_X_LPARAM/GET_Y_LPARAM when using multiple monitors
	  //else use LOWORD/HIWORD
	case WM_MOUSEMOVE:
	{
		int x = GET_X_LPARAM(lParam);
		int y = GET_Y_LPARAM(lParam);
		mouse.mouseMove(x, y);
		return 0;
	}
	case WM_LBUTTONDOWN:
	{
		int x = GET_X_LPARAM(lParam);
		int y = GET_Y_LPARAM(lParam);
		mouse.leftPressed(x, y);
		return 0;
	}
	case WM_RBUTTONDOWN:
	{
		int x = GET_X_LPARAM(lParam);
		int y = GET_Y_LPARAM(lParam);
		mouse.rightPressed(x, y);
		return 0;
	}
	case WM_MBUTTONDOWN:
	{
		int x =  GET_X_LPARAM(lParam);
		int y = GET_Y_LPARAM(lParam);
		mouse.middlePressed(x, y);
		return 0;
	}
	case WM_MBUTTONUP:
	{
		int x = GET_X_LPARAM(lParam);
		int y = GET_Y_LPARAM(lParam);
		mouse.middleReleased(x, y);
		return 0;
	}
	case WM_LBUTTONUP:
	{
		int x = GET_X_LPARAM(lParam);
		int y = GET_Y_LPARAM(lParam);
		mouse.leftreleased(x, y);
		return 0;
	}
	case WM_RBUTTONUP:
	{
		int x = GET_X_LPARAM(lParam);
		int y = GET_Y_LPARAM(lParam);
		mouse.rightReleased(x, y);
		return 0;
	}
	case WM_MOUSEWHEEL:
	{
		int x = GET_X_LPARAM(lParam);
		int y = GET_Y_LPARAM(lParam);
		if (GET_WHEEL_DELTA_WPARAM(wParam) > 0)
		{
			mouse.wheelUp(x, y);
		}
		else if (GET_WHEEL_DELTA_WPARAM(wParam) < 0)
		{
			mouse.wheelDown(x, y);
		}
		break;
	}
	case WM_INPUT:
	{
		UINT dataSize;
		GetRawInputData(reinterpret_cast<HRAWINPUT>(lParam), RID_INPUT, NULL, &dataSize, sizeof(RAWINPUTHEADER));

		if (dataSize > 0)
		{
			std::unique_ptr<BYTE[]> rawData = std::make_unique<BYTE[]>(dataSize);
			if (GetRawInputData(reinterpret_cast<HRAWINPUT>(lParam), RID_INPUT, rawData.get(), &dataSize, sizeof(RAWINPUTHEADER)) == dataSize);
			{
				RAWINPUT* raw = reinterpret_cast<RAWINPUT*>(rawData.get());
				if (raw->header.dwType == RIM_TYPEMOUSE)
				{
					mouse.mousemoveRaw(raw->data.mouse.lLastX, raw->data.mouse.lLastY);
				}
			}
		}

		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}
