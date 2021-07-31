#include "MapCreator.h"
#include <ctime>
#include <json/json.h>
#include <fstream>
#include <string>
#include <cstdio>

#include "Converter.h"

MapCreator::MapCreator()
	: cameraPos{ 0, 0 }, curSelectPos{0, 0}, mapImage(NULL), coliImage(NULL), mpImage(NULL), isSelect(false)
{ }

bool MapCreator::PosInGrid(Point pos)
{
	if (pos.X < rect.left || pos.X > rect.right || pos.Y < rect.top || pos.Y > rect.bottom || pos.X / 16 >= mapData.mapSize.X || pos.Y / 16 >= mapData.mapSize.Y)
		return false;

	return true;
}

void MapCreator::DrawToCollider(int moveable, int x, int y)
{
	Graphics g(coliImage);
	g.SetCompositingMode(CompositingMode::CompositingModeSourceCopy);

	if (moveable == 0)
	{
		SolidBrush brush(Color(0, 255, 255, 255));
		g.FillRectangle(&brush, x, y, 16, 16);
	}
	else
	{
		SolidBrush brush(Color(100, 255, 0, 0));
		g.FillRectangle(&brush, x, y, 16, 16);

		g.SetCompositingMode(CompositingMode::CompositingModeSourceOver);

		TCHAR cnt[4];
		_stprintf_s(cnt, _T("%d"), moveable);

		Font font(&FontFamily(L"Arial"), 12, FontStyleRegular, UnitPoint);
		SolidBrush strBrush(Color(255, 0, 0, 0));
		RectF rectF(x, y, x + 16, y + 16);
		g.DrawString(cnt, -1, &font, rectF, NULL, &strBrush);
	}
}

void MapCreator::DrawToMap(Image *img, int x, int y, int srcx, int srcy)
{
	Graphics g(mapImage);
	g.DrawImage(img, x, y, srcx, srcy, 16, 16, Unit::UnitPixel);
}

void MapCreator::EraseToMap(int x, int y)
{
	Graphics g(mapImage);
	g.SetCompositingMode(CompositingMode::CompositingModeSourceCopy);

	SolidBrush brush(Color(255, 200, 200, 200));
	g.FillRectangle(&brush, x, y, 16, 16);
}

void MapCreator::DrawToMp(int isPoint, int x, int y)
{
	Graphics g(mpImage);
	g.SetCompositingMode(CompositingMode::CompositingModeSourceCopy);

	if (isPoint == 1)
	{
		Pen pen(Color(255, 0, 0, 255));
		g.DrawEllipse(&pen, x, y, 15, 15);
	}
	else
	{
		SolidBrush brush(Color(0, 255, 255, 255));
		g.FillRectangle(&brush, x, y, 16, 16);
	}
}

void MapCreator::SelectTile(Point mPos)
{
	mPos = mPos + cameraPos;

	if (PosInGrid(mPos))
	{
		isSelect = true;

		curSelectPos.X = mPos.X - mPos.X % 16;
		curSelectPos.Y = mPos.Y - mPos.Y % 16;
	}
	else isSelect = false;
}

void MapCreator::SetTile(Point mPos)
{
	mPos = mPos + cameraPos;

	if(PosInGrid(mPos))
	{
		isSelect = true;

		curSelectPos.X = mPos.X - mPos.X % 16;
		curSelectPos.Y = mPos.Y - mPos.Y % 16;

		int idxX = curSelectPos.X / 16;
		int idxY = curSelectPos.Y / 16;

		if (tm->GetIsSelect())
		{
			Point src = mapData.tiles[idxY][idxX].tilePos = tm->GetCurSelectPos();
			DrawToMap(tm->GetTileset(), curSelectPos.X, curSelectPos.Y, src.X, src.Y);
		}
	}
	else isSelect = false;
}

void MapCreator::EraseTile(Point mPos)
{
	mPos = mPos + cameraPos;

	if (PosInGrid(mPos))
	{
		isSelect = true;

		curSelectPos.X = mPos.X - mPos.X % 16;
		curSelectPos.Y = mPos.Y - mPos.Y % 16;

		int idxX = curSelectPos.X / 16;
		int idxY = curSelectPos.Y / 16;

		mapData.tiles[idxY][idxX].tilePos = { -1, -1 };
		EraseToMap(curSelectPos.X, curSelectPos.Y);
	}
	else isSelect = false;
}

void MapCreator::SetCollider(Point mPos)
{
	mPos = mPos + cameraPos;

	if (PosInGrid(mPos))
	{
		isSelect = true;

		curSelectPos.X = mPos.X - mPos.X % 16;
		curSelectPos.Y = mPos.Y - mPos.Y % 16;

		int idxX = curSelectPos.X / 16;
		int idxY = curSelectPos.Y / 16;

		Tile &curTile = mapData.tiles[idxY][idxX];

		++curTile.moveable;
		curTile.moveable %= 5;
		DrawToCollider(curTile.moveable, curSelectPos.X, curSelectPos.Y);
	}
	else isSelect = false;
}

void MapCreator::SetMp(Point mPos)
{
	mPos = mPos + cameraPos;

	if (PosInGrid(mPos))
	{
		isSelect = true;

		curSelectPos.X = mPos.X - mPos.X % 16;
		curSelectPos.Y = mPos.Y - mPos.Y % 16;

		int idxX = curSelectPos.X / 16;
		int idxY = curSelectPos.Y / 16;

		for(int i = 0; i < (int)mapData.movePoints.size(); ++i)
		{
			MovePoint mp = mapData.movePoints[i];

			if (mp.pos.X == idxX && mp.pos.Y == idxY)
			{
				DrawToMp(0, curSelectPos.X, curSelectPos.Y);
				mapData.movePoints.erase(mapData.movePoints.begin() + i);
				return;
			}
		}

		DrawToMp(1, curSelectPos.X, curSelectPos.Y);
		mapData.movePoints.push_back({ "", {idxX, idxY}, {-1, -1} });
	}
	else isSelect = false;
}

Tile* MapCreator::GetSelectTile()
{
	if (!isSelect) return NULL;

	int idxX = curSelectPos.X / 16;
	int idxY = curSelectPos.Y / 16;

	return &(mapData.tiles[idxY][idxX]);
}

MovePoint* MapCreator::GetMP()
{
	if (!isSelect) return NULL;

	int idxX = curSelectPos.X / 16;
	int idxY = curSelectPos.Y / 16;

	for (auto& e : mapData.movePoints)
		if (e.pos.X == idxX && e.pos.Y == idxY)
			return &e;

	return NULL;
}

void MapCreator::ViewDrag(HWND hWnd)
{
	cameraPos = cameraPos - (newPos - oldPos);

	if (cameraPos.X < 0) cameraPos.X = 0;
	if (cameraPos.Y < 0) cameraPos.Y = 0;

	oldPos = newPos;
}

void MapCreator::SetSreenSize(HWND hWnd)
{
	GetClientRect(hWnd, &rect);
}

void MapCreator::DrawGrid(Graphics *graphic)
{
	Pen pen(Color(100, 100, 100, 100));

	int startX, startY;

	if (cameraPos.X % 16 == 0) startX = 0;
	else startX = 16 - cameraPos.X % 16;

	if (cameraPos.Y % 16 == 0) startY = 0;
	else startY = 16 - cameraPos.Y % 16;

	// 세로선
	for (int i = startX; i <= rect.right && cameraPos.X + i <= mapData.mapSize.X * 16; i += 16)
		graphic->DrawLine(&pen, i, 0, i, mapData.mapSize.Y * 16 - cameraPos.Y);

	// 가로선
	for (int i = startY; i <= rect.bottom && cameraPos.Y + i <= mapData.mapSize.Y * 16; i += 16)
		graphic->DrawLine(&pen, 0, i, mapData.mapSize.X * 16 - cameraPos.X, i);
}

void MapCreator::DrawBack(Graphics* graphic)
{
	SolidBrush brush(Color(255, 255, 255));
	graphic->FillRectangle(&brush, 0, 0, rect.right, rect.bottom);
}

void MapCreator::DrawMap(Graphics* graphic)
{
	if(mapImage != NULL)
		graphic->DrawImage(mapImage, 0, 0, cameraPos.X, cameraPos.Y, mapImage->GetWidth() - cameraPos.X, mapImage->GetHeight() - cameraPos.Y, Unit::UnitPixel);
}

void MapCreator::DrawCollider(Graphics* graphic)
{
	if (coliImage != NULL)
		graphic->DrawImage(coliImage, 0, 0, cameraPos.X, cameraPos.Y, coliImage->GetWidth() - cameraPos.X, coliImage->GetHeight() - cameraPos.Y, Unit::UnitPixel);
}

void MapCreator::DrawMp(Graphics * graphic)
{
	if (mpImage != NULL)
		graphic->DrawImage(mpImage, 0, 0, cameraPos.X, cameraPos.Y, mpImage->GetWidth() - cameraPos.X, mpImage->GetHeight() - cameraPos.Y, Unit::UnitPixel);
}

void MapCreator::DrawCurSelect(Graphics * graphic)
{
	if (!isSelect) return;

	Pen pen(Color(255, 0, 0));
	graphic->DrawRectangle(&pen, curSelectPos.X - cameraPos.X, curSelectPos.Y - cameraPos.Y, 15, 15);
}

void MapCreator::InitMap(int x, int y)
{
	if (mapImage != NULL)
		delete mapImage;

	mapImage = new Bitmap(x, y, PixelFormat32bppARGB);

	Graphics g(mapImage);
	g.Clear(Color(255, 200, 200, 200));
}

void MapCreator::InitMap(TCHAR * filepath)
{
	if (mapImage != NULL)
		delete mapImage;

	mapImage = new Bitmap(filepath);
}

void MapCreator::InitCollider(int x, int y)
{
	if (coliImage != NULL)
		delete coliImage;

	coliImage = new Bitmap(x, y , PixelFormat32bppARGB);

	Graphics g(coliImage);
	g.Clear(Color(0, 255, 255, 255));
}

void MapCreator::InitMp(int x, int y)
{
	if (mpImage != NULL)
		delete mpImage;

	mpImage = new Bitmap(x, y, PixelFormat32bppARGB);

	Graphics g(mpImage);
	g.Clear(Color(0, 255, 255, 255));
}

void MapCreator::Draw(HDC hdc)
{
	HDC memDC;
	HBITMAP oldBit, newBit;

	memDC = CreateCompatibleDC(hdc);

	newBit = CreateCompatibleBitmap(hdc, rect.right, rect.bottom);
	oldBit = (HBITMAP)SelectObject(memDC, newBit);

	Graphics *graphic = new Graphics(memDC);
	
	DrawBack(graphic);
	DrawMap(graphic);
	DrawCollider(graphic);
	DrawMp(graphic);
	DrawGrid(graphic);
	DrawCurSelect(graphic);

	delete graphic;

	BitBlt(hdc, 0, 0, rect.right, rect.bottom, memDC, 0, 0, SRCCOPY);
	SelectObject(memDC, oldBit);
	DeleteObject(newBit);

	DeleteDC(memDC);
}

void MapCreator::MapCreate(TCHAR *id, int x, int y)
{
	std::wstring wID(id);
	std::string sID(wID.begin(), wID.end());

	mapData = Map(sID, x, y);

	InitMap(x * 16, y * 16);
	InitCollider(x * 16, y * 16);
	InitMp(x * 16, y * 16);
}

void MapCreator::FileOpen(TCHAR *filename)
{
	TCHAR imgName[256];
	_stprintf_s(imgName, _T("Files\\%s.png"), filename);

	TCHAR dataName[256];
	_stprintf_s(dataName, _T("Files\\%s.mapData"), filename);

	Json::Value root;
	std::ifstream readFile(dataName);

	if (readFile.is_open())
	{
		readFile >> root;
		readFile.close();

		JsonToMap(mapData, root);

		InitMap(imgName);
		InitCollider(mapData.mapSize.X * 16, mapData.mapSize.Y * 16);
		InitMp(mapData.mapSize.X * 16, mapData.mapSize.Y * 16);

		cameraPos = curSelectPos = oldPos = newPos = { 0, 0 };

		for (int i = 0; i < mapData.mapSize.Y; ++i)
			for (int j = 0; j < mapData.mapSize.X; ++j)
				DrawToCollider(mapData.tiles[i][j].moveable, j * 16, i * 16);

		for (const auto& e : mapData.movePoints)
			DrawToMp(1, e.pos.X * 16, e.pos.Y * 16);
	}
}

void MapCreator::FileSave(TCHAR* filename)
{
	if (mapImage == NULL)
		return;

	TCHAR imgName[256];
	_stprintf_s(imgName, _T("Files\\%s.png"), filename);

	TCHAR dataName[256];
	_stprintf_s(dataName, _T("Files\\%s.mapData"), filename);

	std::wstring wID(filename);
	std::string ID(wID.begin(), wID.end());
	mapData.ID = ID;

	Json::Value root;
	MapToJson(mapData, root);

	std::ofstream writeFile(dataName);

	if (writeFile.is_open())
	{
		Json::StreamWriterBuilder writer;
		string str = Json::writeString(writer, root);

		writeFile << str;
		writeFile.close();

		CLSID png_sid;
		GetEncoderClsid(L"image/png", &png_sid);
		mapImage->Save(imgName, &png_sid, NULL);
	}
}
