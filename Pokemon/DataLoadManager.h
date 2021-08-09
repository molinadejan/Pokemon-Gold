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
		void LoadItemDesc();
		void LoadTransData();

		void LoadPokemonData();
		void LoadPokemonDesc();

		void LoadSkillData();
		void LoadSkillDesc();

		void Init();

		void AddItemToInventory(int code, int count);
		void RemoveItemFromInventory(int code, int count);

	private:

		unordered_map<string, Image*> mapImages;

		unordered_map<string, Map> mapDatas;
		unordered_map<int, ItemDesc*> itemDescs;

		unordered_map<int, PokemonData*> pokemonDatas;
		unordered_map<int, PokemonDesc*> pokemonDescs;

		unordered_map<int, SkillData*> skillDatas;
		unordered_map<int, SkillDesc*> skillDescs;

		unordered_map<string, string> transDatas;

		Image* playerInGame;
		Image* dialogBase;
		Image* bagUI;
		Image* battleUI;
		Image* pokemonPicture;

		PlayerData* playerData;
	};

private:

	static DataLoad dataLoad;

public:

	static void Reset();

	static Map* GetMapData(string ID);
	static Image* GetMapImage(string ID);

	static Image* GetPlayerInGame() { return dataLoad.playerInGame; }
	static Image* GetBagUI() { return dataLoad.bagUI; }
	static Image* GetDialogBase() { return dataLoad.dialogBase; }
	static Image* GetBattleUI() { return dataLoad.battleUI; }
	static Image* GetPokemonPicture() { return dataLoad.pokemonPicture; }

	static ItemDesc* GetItemDesc(int code) { return dataLoad.itemDescs[code]; }
	static PlayerData* GetPlayerData() { return dataLoad.playerData; }

	static PokemonData* GetPokemonData(int id) { return dataLoad.pokemonDatas[id]; }
	static PokemonDesc* GetPokemonDesc(int id) { return dataLoad.pokemonDescs[id]; }

	static SkillData* GetSkillData(int id) { return dataLoad.skillDatas[id]; }
	static SkillDesc* GetSkillDesc(int id) { return dataLoad.skillDescs[id]; }

	static void AddItemToInventory(int code, int count = 1) { dataLoad.AddItemToInventory(code, count); }
	static void RemoveItemFromInventory(int code, int count = 1) { dataLoad.RemoveItemFromInventory(code, count); }

	static string GetStringData(string key) { return dataLoad.transDatas[key]; }
};

#endif // !__DATALOADMANAGER_H__
