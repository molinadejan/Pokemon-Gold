#pragma once

#ifndef __DATALOADMANAGER_H__
#define __DATALOADMANAGER_H__

#include <unordered_map>
#include <string>

#include "Datas.h"

using std::unordered_map;
using std::string;

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
		void Reset();

	private:

		unordered_map<string, Map> mapDatas;
		unordered_map<string, Image*> mapImages;
		Image* player_game;
		Image* UI_menu;
		//Image* UI_Dialog;
		Image* UI_Dialog_Base;
		Image* UI_Bag;

		PrivateFontCollection *collection;
		FontFamily* fm;

		Font* fontS;
		Font* fontM;
		Font* fontB;
	};

private:

	static DataLoad dataLoad;

public:

	static void Reset();

	static Map* GetMapData(string ID);
	static Image* GetMapImage(string ID);

	static Image* GetPlayer_game();
	static Image* GetUI_menu() { return dataLoad.UI_menu; }
	//static Image* GetUI_Dialog() { return dataLoad.UI_Dialog; }
	static Image* GetUI_Bag() { return dataLoad.UI_Bag; }
	static Image* GetUI_Dialog_Base() { return dataLoad.UI_Dialog_Base; }


	static Font* GetFontS() { return dataLoad.fontS; };
	static Font* GetFontM() { return dataLoad.fontM; };
	static Font* GetFontB() { return dataLoad.fontB; };
};

#endif // !__DATALOADMANAGER_H__
