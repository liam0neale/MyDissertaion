#pragma once
#include <windows.h>

#include "D12Core.h"
#include "LWindow.h"
#include "Status.h"

class WindowsApp
{

public:
	WindowsApp() = default;
	static int Run(D12Core* pCore, HINSTANCE hInstance, int nCmdShow);
	static HWND GetHwnd() { return m_pWindow->getWindow(); }

private:
	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static int messageloop(D12Core* pCore);
	static LWindow* m_pWindow;
};

