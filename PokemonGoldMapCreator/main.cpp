#include "framework.h"
#include "PokemonGoldMapCreator.h"
#include "MapCreator.h"
#include "TilesetManager.h"
#include "Datas.h"

#include <atlstr.h>

#define MAX_LOADSTRING 100

HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];

ULONG_PTR g_GdiToken;

HWND mainWnd;
HWND tileSetWnd;
HWND tileInfoDlg;
HWND mapInfoDlg;

MapCreator mc;
TilesetManager tm;

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    TilesetProc(HWND, UINT, WPARAM, LPARAM);

BOOL CALLBACK    CreateDlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK    SaveDlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK    OpenDlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK    TileInfoDlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK    MapInfoDlgProc(HWND, UINT, WPARAM, LPARAM);

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
      10, 10, 1000, 500, nullptr, nullptr, hInstance, nullptr);

   if (!mainWnd)
      return FALSE;

   ShowWindow(mainWnd, nCmdShow);
   UpdateWindow(mainWnd);

   return TRUE;
}

enum MODE 
{
	TileImage,
	Collider,
	Select,
	MP
};

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static RECT rectView;
	static bool isDrag;
	static MODE state;

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
				0, 0, 0, 0,
				hWnd, NULL, hInst, NULL);

			tileInfoDlg = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG_TILEINFO), hWnd, TileInfoDlgProc);
			ShowWindow(tileInfoDlg, SW_SHOW);

			mapInfoDlg = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG_MAPINFO), hWnd, MapInfoDlgProc);
			ShowWindow(mapInfoDlg, SW_SHOW);

			mc.SetSreenSize(hWnd);
			mc.SetTilesetManager(&tm);

			state = MODE::Select;

			SetTimer(hWnd, 1, 8, NULL);
		}
		break;

		case WM_SIZE:
		{
			mc.SetSreenSize(hWnd);
			GetClientRect(hWnd, &rectView);
		}
		break;

		case WM_KEYDOWN:
		{
			switch (wParam)
			{
				case 'T':
					state = MODE::TileImage;
					break;

				case 'C':
					state = MODE::Collider;
					break;

				case 'S':
					state = MODE::Select;
					break;

				case 'M':
					state = MODE::MP;
					break;
			}
		}
		break;

		case WM_LBUTTONDOWN:
		{
			Point mPos = { LOWORD(lParam), HIWORD(lParam) };

			if (GetAsyncKeyState(VK_LMENU) & 0x8001)
			{
				isDrag = true;
				mc.SetOldPos(mPos);
				return 0;
			}
			
			isDrag = false;

			switch (state)
			{
				case MODE::TileImage:
					mc.SetTile(mPos);
					break;

				case MODE::Collider:
					mc.SetCollider(mPos);
					break;

				case MODE::Select:
					mc.SelectTile(mPos);
					break;

				case MODE::MP:
					mc.SetMp(mPos);
					break;
			}

			PostMessage(tileInfoDlg, WM_SELECT_TILE, 0, 0);
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
			Point mPos = { LOWORD(lParam), HIWORD(lParam) };

			switch (state)
			{
				case MODE::TileImage:
					mc.EraseTile(mPos);
					break;

				case MODE::Collider:
					break;

				case MODE::Select:
					mc.SelectTile(mPos);
					break;
			}

			PostMessage(tileInfoDlg, WM_SELECT_TILE, 0, 0);
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

					PostMessage(mapInfoDlg, WM_SELECT_MAP, 0, 0);

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

					PostMessage(mapInfoDlg, WM_SELECT_MAP, 0, 0);

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

BOOL CALLBACK TileInfoDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static Tile* tile;
	static MovePoint* mp;

	switch (message)
	{
		case WM_INITDIALOG:
		{
			tile = NULL;
			mp = NULL;

			EnableWindow(GetDlgItem(hDlg, IDC_EDIT_TARGETID), FALSE);
			EnableWindow(GetDlgItem(hDlg, IDC_EDIT_TARGETPOSX), FALSE);
			EnableWindow(GetDlgItem(hDlg, IDC_EDIT_TARGETPOSY), FALSE);
			EnableWindow(GetDlgItem(hDlg, IDC_EDIT_MOVETYPE), FALSE);
		}
		break;

		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
				case IDSAVE:
				{
					if (tile != NULL)
					{
						tile->interactID = GetDlgItemInt(hDlg, IDC_EDIT_INID, NULL, TRUE);
						tile->isPokemon = GetDlgItemInt(hDlg, IDC_EDIT_ISPOKEMON, NULL, TRUE);
					}

					if (mp != NULL)
					{
						TCHAR targetId[64];
						GetDlgItemText(hDlg, IDC_EDIT_TARGETID, targetId, 64);

						std::wstring wTargetId(targetId);
						std::string sTargetId(wTargetId.begin(), wTargetId.end());

						mp->targetID = sTargetId;
						mp->targetPos.X = GetDlgItemInt(hDlg, IDC_EDIT_TARGETPOSX, NULL, TRUE);
						mp->targetPos.Y = GetDlgItemInt(hDlg, IDC_EDIT_TARGETPOSY, NULL, TRUE);
						mp->moveType = GetDlgItemInt(hDlg, IDC_EDIT_MOVETYPE, NULL, TRUE);
					}
				}
				break;
			}
		}
		break;

		case WM_SELECT_TILE:
		{
			tile = mc.GetSelectTile();

			if (tile == NULL)
			{
				SetDlgItemText(hDlg, IDC_EDIT_XPOS, _T(""));
				SetDlgItemText(hDlg, IDC_EDIT_YPOS, _T(""));
				SetDlgItemText(hDlg, IDC_EDIT_TXPOS, _T(""));
				SetDlgItemText(hDlg, IDC_EDIT_TYPOS, _T(""));
				SetDlgItemText(hDlg, IDC_EDIT_MOVEABLE, _T(""));
				SetDlgItemText(hDlg, IDC_EDIT_INID, _T(""));
				SetDlgItemText(hDlg, IDC_EDIT_ISPOKEMON, _T(""));
			}
			else
			{
				SetDlgItemInt(hDlg, IDC_EDIT_XPOS, tile->pos.X, FALSE);
				SetDlgItemInt(hDlg, IDC_EDIT_YPOS, tile->pos.Y, FALSE);
				SetDlgItemInt(hDlg, IDC_EDIT_TXPOS, tile->tilePos.X, TRUE);
				SetDlgItemInt(hDlg, IDC_EDIT_TYPOS, tile->tilePos.Y, TRUE);
				SetDlgItemInt(hDlg, IDC_EDIT_MOVEABLE, tile->moveable, FALSE);
				SetDlgItemInt(hDlg, IDC_EDIT_INID, tile->interactID, TRUE);
				SetDlgItemInt(hDlg, IDC_EDIT_ISPOKEMON, tile->isPokemon, TRUE);
			}

			mp = mc.GetMP();

			if (mp == NULL)
			{
				EnableWindow(GetDlgItem(hDlg, IDC_EDIT_TARGETID), FALSE);
				EnableWindow(GetDlgItem(hDlg, IDC_EDIT_TARGETPOSX), FALSE);
				EnableWindow(GetDlgItem(hDlg, IDC_EDIT_TARGETPOSY), FALSE);
				EnableWindow(GetDlgItem(hDlg, IDC_EDIT_MOVETYPE), FALSE);

				SetDlgItemText(hDlg, IDC_EDIT_TARGETID, _T(""));
				SetDlgItemText(hDlg, IDC_EDIT_TARGETPOSX, _T(""));
				SetDlgItemText(hDlg, IDC_EDIT_TARGETPOSY, _T(""));
				SetDlgItemText(hDlg, IDC_EDIT_MOVETYPE, _T(""));
			}
			else
			{
				EnableWindow(GetDlgItem(hDlg, IDC_EDIT_TARGETID), TRUE);
				EnableWindow(GetDlgItem(hDlg, IDC_EDIT_TARGETPOSX), TRUE);
				EnableWindow(GetDlgItem(hDlg, IDC_EDIT_TARGETPOSY), TRUE);
				EnableWindow(GetDlgItem(hDlg, IDC_EDIT_MOVETYPE), TRUE);

				TCHAR targetId[64];
				_tcscpy_s(targetId, CA2T(mp->targetID.c_str()));

				SetDlgItemText(hDlg, IDC_EDIT_TARGETID, targetId);
				SetDlgItemInt(hDlg, IDC_EDIT_TARGETPOSX, mp->targetPos.X, TRUE);
				SetDlgItemInt(hDlg, IDC_EDIT_TARGETPOSY, mp->targetPos.Y, TRUE);
				SetDlgItemInt(hDlg, IDC_EDIT_MOVETYPE, mp->moveType, TRUE);
			}
		}
		break;
	}

	return 0;
}

BOOL CALLBACK MapInfoDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static Map* map;

	switch (message)
	{
		case WM_INITDIALOG:
		{

		}
		break;

		case WM_SELECT_MAP:
		{
			map = mc.GetMap();

			TCHAR id[64];

			_tcscpy_s(id, CA2T(map->ID.c_str()));
			SetDlgItemText(hDlg, IDC_EDIT_SAVE_NAME, id);

			SetDlgItemText(hDlg, IDC_EDIT_ID, id);
			SetDlgItemInt(hDlg, IDC_EDIT_POSX, map->worldPos.X, FALSE);
			SetDlgItemInt(hDlg, IDC_EDIT_POSY, map->worldPos.Y, FALSE);
			SetDlgItemInt(hDlg, IDC_EDIT_MAPSIZEX, map->mapSize.X, FALSE);
			SetDlgItemInt(hDlg, IDC_EDIT_MAPSIZEY, map->mapSize.Y, FALSE);
		}
		break;

		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
				case IDSAVE:
				{
					if (map != NULL)
					{
						map->worldPos.X = GetDlgItemInt(hDlg, IDC_EDIT_POSX, NULL, FALSE);
						map->worldPos.Y = GetDlgItemInt(hDlg, IDC_EDIT_POSY, NULL, FALSE);
					}
				}
				break;
			}
		}
		break;
	}

	return 0;
}