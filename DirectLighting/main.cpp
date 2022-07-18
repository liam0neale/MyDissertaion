#include <Windows.h>

#include "DXDefines.h"
#include "Scene.h"
#include "WindowsApp.h"

int WINAPI WinMain(HINSTANCE hInstance,    //Main windows function
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nShowCmd)

{
	Scene* scene = new Scene(1280, 720, "Liams");
	return WindowsApp::Run(scene, hInstance, nShowCmd);
}