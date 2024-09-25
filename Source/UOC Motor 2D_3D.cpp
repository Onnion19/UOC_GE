#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include "ApplicationDX.h"


#define WIDTH_APPLICATION 1280
#define HEIGHT_APPLICATION 720

#define APPLICATION_NAME				L"UOC Motors 2D i 3D"
#define APPLICATION_CLASS_NAME			L"UOCMotors2Di3DClass"

#include <stdlib.h>
#include <crtdbg.h>

CApplicationDX *g_ApplicationDX = NULL;

HINSTANCE hInst;                                // instancia actual

LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	//-----------Para detectar Memory Leaks-------------------------
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetBreakAlloc(-1);
	//--------------------------------------------------------------

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = NULL;
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = APPLICATION_CLASS_NAME;
	wcex.hIconSm = NULL;

	RegisterClassExW(&wcex);

	// Realizar la inicialización de la aplicación:
	HWND hWnd = CreateWindowW(APPLICATION_CLASS_NAME, APPLICATION_NAME, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, WIDTH_APPLICATION, HEIGHT_APPLICATION, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, SW_SHOWDEFAULT);

	g_ApplicationDX = new CApplicationDX;

	g_ApplicationDX->Init(hWnd, WIDTH_APPLICATION, HEIGHT_APPLICATION);

	UpdateWindow(hWnd);


	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			g_ApplicationDX->Update();
			g_ApplicationDX->Render();
		}
	}

	CHECKED_DELETE(g_ApplicationDX);

	UnregisterClass(APPLICATION_NAME, hInst);

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return g_ApplicationDX->MsgProc(hWnd, message, wParam, lParam);
}
