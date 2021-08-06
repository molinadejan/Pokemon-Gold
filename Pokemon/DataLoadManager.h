#pragma once

#ifndef __DATALOADMANAGER_H__
#define __DATALOADMANAGER_H__

#define DM DataLoadManager

#include <unordered_map>
#include "Datas.h"

using std::unordered_map;

class DataLoadManager
{
private:
	class DataLoad
	{
		friend DataLoadManager;

	private:

		DataLoad();
		~DataLoad();

	private:

		void LoadMap();
		void LoadFont();
		void LoadItemData();
		void LoadTransData();
		void Reset();

		void AddItemToInventory(int code, int count);
		void RemoveItemFromInventory(int code, int count);

	private:

		unordered_map<string, Map> mapDatas;
		unordered_map<string, Image*> mapImages;
		unordered_map<int, ItemDesc*> itemDescs;

		unordered_map<string, string> transDatas;

		Image* player_game;
		Image* UI_Dialog_Base;
		Image* UI_Bag;

		PrivateFontCollection *collection;
		FontFamily* fm;

		Font* fontS;
		Font* fontM;
		Font* fontB;

		PlayerData* playerData;
	};

private:

	static DataLoad dataLoad;

public:

	static void Reset();

	static Map* GetMapData(string ID);
	static Image* GetMapImage(string ID);

	static Image* GetPlayer_game();
	static Image* GetUI_Bag() { return dataLoad.UI_Bag; }
	static Image* GetUI_Dialog_Base() { return dataLoad.UI_Dialog_Base; }

	static Font* GetFontS() { return dataLoad.fontS; };
	static Font* GetFontM() { return dataLoad.fontM; };
	static Font* GetFontB() { return dataLoad.fontB; };

	static ItemDesc* GetItemDesc(int code) { return dataLoad.itemDescs[code]; }
	static PlayerData* GetPlayerData() { return dataLoad.playerData; }

	static void AddItemToInventory(int code, int count = 1) { dataLoad.AddItemToInventory(code, count); }
	static void RemoveItemFromInventory(int code, int count = 1) { dataLoad.RemoveItemFromInventory(code, count); }

	static string GetStringData(string key) { return dataLoad.transDatas[key]; }
};

#endif // !__DATALOADMANAGER_H__
