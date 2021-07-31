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

		void Reset();

	private:

		unordered_map<string, Map> mapDatas;
		unordered_map<string, Image*> mapImages;
	};

private:

	static DataLoad dataLoad;

public:

	static void Reset();

	static Map* GetMapData(string ID);
	static Image* GetMapImage(string ID);
};

#endif // !__DATALOADMANAGER_H__
