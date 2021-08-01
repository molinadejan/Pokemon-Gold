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
		void Reset();

	private:

		unordered_map<string, Map> mapDatas;
		unordered_map<string, Image*> mapImages;
		Image* player_game;
	};

private:

	static DataLoad dataLoad;

public:

	static void Reset();

	static Map* GetMapData(string ID);
	static Image* GetMapImage(string ID);
	static Image* GetPlayer_game();
};

#endif // !__DATALOADMANAGER_H__
