#include "framework.h"
#include "PokemonGoldMapCreator.h"
#include "MapCreator.h"
#include "TilesetManager.h"

#include <atlstr.h>

#define MAX_LOADSTRING 100

HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];

ULONG_PTR g_GdiToken;

HWND mainWnd;
HWND tileSetWnd;

MapCreator mc;
TilesetManager tm;

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    TilesetProc(HWND, UINT, WPARAM, LPARAM);

BOOL CALLBACK    CreateDlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK    SaveDlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK    OpenDlgProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_POKEMONGOLDMAPCREATOR, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance (hInstance, nCmdShow))
        return FALSE;

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_POKEMONGOLDMAPCREATOR));

    MSG msg;

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			//mc.Update(mainWnd);
			//tm.Update(tileSetWnd);
		}
	}

    return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_POKEMONGOLDMAPCREATOR));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDR_MAIN_MENU);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    RegisterClassExW(&wcex);

	wcex.lpfnWndProc = TilesetProc;
	wcex.lpszMenuName = 0;
	wcex.lpszClassName = _T("TileSet Window");

	RegisterClassExW(&wcex);

	return NULL;
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance;

   mainWnd = CreateWindowW(szWindowClass, szTitle,  WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
      CW_USEDEFAULT, 0, 1000, 500, nullptr, nullptr, hInstance, nullptr);

   if (!mainWnd)
      return FALSE;

   ShowWindow(mainWnd, nCmdShow);
   UpdateWindow(mainWnd);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static RECT rectView;
	static bool isDrag;

    switch (message)
    {
		case WM_CREATE:
		{
			isDrag = false;

			Gdiplus::GdiplusStartupInput gpsi;
			Gdiplus::GdiplusStartup(&g_GdiToken, &gpsi, NULL);

			GetClientRect(hWnd, &rectView);

			tileSetWnd = CreateWindowEx(0, _T("TileSet Window"), szWindowClass,
				WS_VISIBLE | WS_OVERLAPPED | WS_BORDER,
				0, 0, 200, 200,
				hWnd, NULL, hInst, NULL);

			mc.SetSreenSize(hWnd);
			mc.SetTilesetManager(&tm);

			SetTimer(hWnd, 1, 8, NULL);
		}
		break;

		case WM_SIZE:
		{
			mc.SetSreenSize(hWnd);
			GetClientRect(hWnd, &rectView);
		}
		break;

		case WM_LBUTTONDOWN:
		{
			POINT mPos = { LOWORD(lParam), HIWORD(lParam) };

			if (GetAsyncKeyState(VK_LMENU) & 0x8001)
			{
				isDrag = true;
				mc.SetOldPos(mPos);
				return 0;
			}
			
			isDrag = false;
			mc.SelectTile(mPos);
		}
		break;

		case WM_MOUSEMOVE:
		{
			if (isDrag && (GetAsyncKeyState(VK_LMENU) & 0x8001))
			{
				mc.SetNewPos({ LOWORD(lParam), HIWORD(lParam) });
				mc.ViewDrag(hWnd);
			}
		}
		break;

		case WM_LBUTTONUP:
		{
			isDrag = false;
		}
		break;

		case WM_RBUTTONDOWN:
		{
			mc.SelectCollider({ LOWORD(lParam), HIWORD(lParam) });
		}
		break;

		case WM_COMMAND:
		{
			int wmId = LOWORD(wParam);

			switch (wmId)
			{
				case IDM_EXIT:
				{
					DestroyWindow(hWnd);
				}
				break;

				case ID_CREATE:
				{
					DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG_CREATE), hWnd, CreateDlgProc);
				}
				break;

				case ID_SAVE:
				{
					DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG_SAVE), hWnd, SaveDlgProc);
				}
				break;

				case ID_OPEN:
				{
					DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG_OPEN), hWnd, OpenDlgProc);
				}
				break;

				default:
				{
					return DefWindowProc(hWnd, message, wParam, lParam);
				}
				break;
			}
		}
		break;

		case WM_TIMER:
		{
			InvalidateRect(hWnd, NULL, false);
		}
		break;

		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);

			mc.Draw(hdc);

			EndPaint(hWnd, &ps);
		}
		break;

		case WM_DESTROY:
		{
			Gdiplus::GdiplusShutdown(g_GdiToken);
			PostQuitMessage(0);
		}
		break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);

	}
    return 0;
}

LRESULT CALLBACK TilesetProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static RECT rectView;

	switch (message)
	{
		case WM_CREATE:
		{
			tm.LoadTileset(hWnd);
			tm.SetSreenSize(hWnd);

			SetTimer(hWnd, 2, 128, NULL);
		}
		break;

		case WM_TIMER:
		{
			InvalidateRect(hWnd, NULL, false);
		}
		break;

		case WM_LBUTTONDOWN:
		{
			tm.SelectTile(hWnd);
		}
		break;

		case WM_KEYDOWN:
		{
			switch (wParam)
			{
				case VK_ESCAPE:
				{
					tm.SetIsSelect(false);
				}
			}
		}
		break;

		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);

			tm.Draw(hWnd, hdc);

			EndPaint(hWnd, &ps);
		}
		break;

		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
		break;

		default:
		{
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	}

	return 0;
}

BOOL CALLBACK CreateDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
		{

		}
		break;

		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
				case IDOK:
				{
					UINT x = GetDlgItemInt(hDlg, IDC_EDIT_X, NULL, FALSE);
					UINT y = GetDlgItemInt(hDlg, IDC_EDIT_Y, NULL, FALSE);

					TCHAR id[64];
					GetDlgItemText(hDlg, IDC_EDIT_ID, id, 64);

					mc.MapCreate(id, x, y);

					EndDialog(hDlg, 0);
				}
				break;

				case IDCANCEL:
				{
					EndDialog(hDlg, 0);
				}
				break;
			}
		}
		break;
	}

	return 0;
}

BOOL CALLBACK SaveDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{
		TCHAR id[64];

		_tcscpy_s(id, CA2T(mc.GetMapID().c_str()));
		SetDlgItemText(hDlg, IDC_EDIT_SAVE_NAME, id);
	}
	break;

	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			TCHAR filename[128];

			GetDlgItemText(hDlg, IDC_EDIT_SAVE_NAME, filename, 128);

			mc.FileSave(filename);
			EndDialog(hDlg, 0);
		}
		break;

		case IDCANCEL:
		{
			EndDialog(hDlg, 0);
		}
		break;
		}
	}
	break;
	}

	return 0;
}

BOOL CALLBACK OpenDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{

	}
	break;

	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			TCHAR filename[128];
			GetDlgItemText(hDlg, IDC_EDIT_LOAD_NAME, filename, 128);

			mc.FileOpen(filename);
			EndDialog(hDlg, 0);
		}
		break;

		case IDCANCEL:
		{
			EndDialog(hDlg, 0);
		}
		break;
		}
	}
	break;
	}

	return 0;
}