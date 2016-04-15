#include <windows.h>
#include "resource.h"
#include <stdlib.h>
#include <time.h>

#define ID_FILE_EXIT 9001
#define ID_FILE_DIALOG 9003
#define ID_STUFF_GO 9002

const char g_szClassName[] = "myWindowClass";

BOOL CALLBACK AboutDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	//HBRUSH g_hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
	switch (Message)
	{
	/*case WM_CTLCOLORDLG:
		return (LONG)g_hbrBackground;
	case WM_CTLCOLORSTATIC:
	{
		HDC hdcStatic = (HDC)wParam;
		SetTextColor(hdcStatic, RGB(255, 255, 255));
		SetBkMode(hdcStatic, TRANSPARENT);
		return (LONG)g_hbrBackground;
	}
	break;*/
	case WM_INITDIALOG:
	{
		int nr = rand() % 100;
		SetDlgItemInt(hwnd, IDC_SHOWCOUNT, nr, FALSE);
		SetDlgItemInt(hwnd, IDC_SHIFT, nr>>1, FALSE);
		break;
	}
	case WM_COMMAND: switch (LOWORD(wParam))
	{
	case IDOK:{ EndDialog(hwnd, IDOK); break; }
	case IDCANCEL: {EndDialog(hwnd, IDCANCEL); break; }
	}
	break;
	default: return FALSE;
	}
	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE: DestroyWindow(hwnd); break;
	case WM_DESTROY: PostQuitMessage(0); break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_FILE_EXIT: DestroyWindow(hwnd); break;
		case ID_STUFF_GO: MessageBox(hwnd, "Bravo!!", "mesaj", MB_OK); break;
		case ID_FILE_DIALOG:
		{
			int ret = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG1), hwnd, AboutDlgProc);
			/*if (ret == IDOK)
			{
				MessageBox(hwnd, "Dialog exited with IDOK.", "Notice", MB_OK | MB_ICONINFORMATION);
		    }
			else if (ret == IDCANCEL)
			{
				MessageBox(hwnd, "Dialog exited with IDCANCEL.", "Notice", MB_OK | MB_ICONINFORMATION);
			}
			else*/ if (ret == -1)
			{
				MessageBox(hwnd, "Dialog failed!", "Error", MB_OK | MB_ICONINFORMATION);
			}
		}
		break;
		}
	break;
	case WM_CREATE:
	{
		HMENU hMenu, hSubMenu;
		HICON hIcon, hIconSm;
		hMenu = CreateMenu();
		hSubMenu = CreatePopupMenu();
		AppendMenu(hSubMenu, MF_STRING, ID_FILE_DIALOG, "&Dialog");
		AppendMenu(hSubMenu, MF_STRING, ID_FILE_EXIT, "E&xit");//submeniul exit atasat meniului File
		AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&File");
		hSubMenu = CreatePopupMenu();
		AppendMenu(hSubMenu, MF_STRING, ID_STUFF_GO, "&Go");
		AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&Stuff");
		SetMenu(hwnd, hMenu);
		hIcon = (HICON)LoadImage(NULL, "menu_two.ico", IMAGE_ICON, 32, 32, LR_LOADFROMFILE);
		if (hIcon) SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
		else MessageBox(hwnd, "Could not load large icon!", "Error", MB_OK | MB_ICONERROR);
		hIconSm = (HICON)LoadImage(NULL, "menu_two.ico", IMAGE_ICON, 16, 16, LR_LOADFROMFILE);
		if (hIconSm) SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIconSm);
		else MessageBox(hwnd, "Could not load small icon!", "Error", MB_OK | MB_ICONERROR);
	}
	break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	srand((unsigned int)time(NULL));
	//int nr = rand() % 100;///


	WNDCLASSEX wc;
	HWND hwnd;
	MSG Msg;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_HAND);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = g_szClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}
	hwnd = CreateWindowEx( WS_EX_CLIENTEDGE, g_szClassName, "Fereastra", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 250, 250, NULL, NULL, hInstance, NULL);
	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	while (GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}