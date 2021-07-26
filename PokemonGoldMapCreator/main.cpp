#include "framework.h"
#include "PokemonGoldMapCreator.h"
#include "MapCreator.h"

#define MAX_LOADSTRING 100

HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];

ULONG_PTR g_GdiToken;

HWND tileSetWnd;

MapCreator mc;

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    TileSetProc(HWND, UINT, WPARAM, LPARAM);

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
	Timer::Reset();

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
			Timer::Update();
			mc.Update();
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
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDR_MENU1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    RegisterClassExW(&wcex);

	wcex.lpfnWndProc = TileSetProc;
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = _T("TileSet Window");

	RegisterClassExW(&wcex);

	return NULL;
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance;

   HWND hWnd = CreateWindowW(szWindowClass, szTitle,  WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
      CW_USEDEFAULT, 0, 1000, 500, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
      return FALSE;

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static RECT rectView;
	static int tileSetWndW;
	static HCURSOR hCursor;
	static int boundary;

    switch (message)
    {
		case WM_CREATE:
		{
			GetClientRect(hWnd, &rectView);

			tileSetWndW = rectView.right / 3;
			boundary = rectView.right - tileSetWndW;

			hCursor = LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZEWE));

			tileSetWnd = CreateWindowEx(0, _T("TileSet Window"), szWindowClass,
				WS_CHILD | WS_VISIBLE | WS_BORDER,
				rectView.right  - tileSetWndW, 0, tileSetWndW, rectView.bottom,
				hWnd, NULL, hInst, NULL);

			Gdiplus::GdiplusStartupInput gpsi;
			Gdiplus::GdiplusStartup(&g_GdiToken, &gpsi, NULL);

			mc.SetSreenSize(hWnd);

			SetTimer(hWnd, 1, 8, NULL);
		}
		break;

		case WM_SIZE:
		{
			mc.SetSreenSize(hWnd);
			GetClientRect(hWnd, &rectView);

			boundary = rectView.right - tileSetWndW;
			MoveWindow(tileSetWnd, rectView.right - tileSetWndW - 1, 0, tileSetWndW, rectView.bottom, TRUE);
		}
		break;

		case WM_MOUSEMOVE:
		{
			int mx = LOWORD(lParam);

			if (boundary - 10 <= mx && boundary + 10 >= mx)
			{
				SetCursor(hCursor);

				if (wParam == MK_LBUTTON)
				{
					GetClientRect(hWnd, &rectView);

					if (mx > 0 && mx < rectView.right)
					{
						boundary = mx;
						tileSetWndW = rectView.right - boundary;
					}

					MoveWindow(tileSetWnd, rectView.right - tileSetWndW - 1, 0, tileSetWndW, rectView.bottom, TRUE);
				}
			}
		}
		break;

		case WM_LBUTTONDOWN:
		{
			SetCursor(hCursor);
			SetCapture(hWnd);
		}
		break;

		case WM_LBUTTONUP:
		{
			ReleaseCapture();
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

LRESULT CALLBACK TileSetProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_CREATE:
		{

		}
		break;

		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);

			Graphics graphic(hdc);

			Image image(_T("Resource/tileset_day.png"));

			graphic.DrawImage(&image, 0, 0, image.GetWidth(), image.GetHeight());

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