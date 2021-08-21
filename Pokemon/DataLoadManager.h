#pragma once

#ifndef __DATALOADMANAGER_H__
#define __DATALOADMANAGER_H__

#define DM DataLoadManager

#include <unordered_map>
#include "Datas.h"

using std::unordered_map;
using std::vector;

class DataLoadManager
{
private:
	class DataLoad
	{
		friend DataLoadManager;

	private:

		DataLoad() = default;
		~DataLoad() = default;

	private:

		void LoadMap();
		void LoadItemDesc();
		void LoadTransData();

		void LoadPokemonData();
		void LoadPokemonDesc();

		void LoadSkillData();
		void LoadSkillDesc();

		void LoadAnimRect();

		void LoadUIImage(); 

		void Init();
		void Reset();

		void AddItemToInventory(int code, int count);
		bool RemoveItemFromInventory(int code, int count);

		float GetTypeRevision(int skillType, int pokeType);
	private:

		const float typeTable[17][17] = 
		{
			//�븻  �Ҳ�  ��    ����  Ǯ    ����  ����  ��    ��    ����  �����۹���  ����  ��Ʈ�巡���    ��ö 
			{ 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.5f, 0.0f, 1.0f, 1.0f, 0.5f },
			{ 1.0f, 0.5f, 0.5f, 1.0f, 2.0f, 2.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 0.5f, 1.0f, 0.5f, 1.0f, 2.0f },
			{ 1.0f, 2.0f, 0.5f, 1.0f, 0.5f, 1.0f, 1.0f, 1.0f, 2.0f, 1.0f, 1.0f, 1.0f, 2.0f, 1.0f, 0.5f, 1.0f, 1.0f },
			{ 1.0f, 1.0f, 2.0f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 2.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.5f, 1.0f, 1.0f },
			{ 1.0f, 0.5f, 2.0f, 1.0f, 0.5f, 1.0f, 1.0f, 0.5f, 2.0f, 0.5f, 1.0f, 0.5f, 2.0f, 1.0f, 0.5f, 1.0f, 0.5f },
			{ 1.0f, 0.5f, 0.5f, 1.0f, 2.0f, 0.5f, 1.0f, 1.0f, 2.0f, 2.0f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 1.0f, 0.5f },
			{ 2.0f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 1.0f, 0.5f, 1.0f, 0.5f, 0.5f, 0.5f, 2.0f, 0.0f, 1.0f, 2.0f, 2.0f },
			{ 1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 1.0f, 1.0f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f },
			{ 1.0f, 2.0f, 1.0f, 2.0f, 0.5f, 1.0f, 1.0f, 2.0f, 1.0f, 0.0f, 1.0f, 0.5f, 2.0f, 1.0f, 1.0f, 1.0f, 2.0f },
			{ 1.0f, 1.0f, 1.0f, 0.5f, 2.0f, 1.0f, 2.0f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 0.5f, 1.0f, 1.0f, 1.0f, 0.5f },
			{ 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 2.0f, 1.0f, 1.0f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.5f },
			{ 1.0f, 0.5f, 1.0f, 1.0f, 2.0f, 1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 2.0f, 1.0f, 1.0f, 0.5f, 1.0f, 2.0f, 0.5f },
			{ 1.0f, 2.0f, 1.0f, 1.0f, 1.0f, 2.0f, 0.5f, 1.0f, 0.5f, 2.0f, 1.0f, 2.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.5f },
			{ 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 1.0f, 1.0f, 2.0f, 1.0f, 0.5f, 0.5f },
			{ 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 1.0f, 0.5f },
			{ 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.5f, 1.0f, 1.0f, 1.0f, 2.0f, 1.0f, 1.0f, 2.0f, 1.0f, 0.5f, 0.5f },
			{ 1.0f, 0.5f, 0.5f, 0.5f, 1.0f, 2.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 1.0f, 1.0f, 1.0f, 0.5f },
		};

	private:

		unordered_map<string, Image*> mapImages;
		unordered_map<string, Map*> mapDatas;

		unordered_map<int, ItemDesc*> itemDescs;

		unordered_map<int, PokemonData*> pokemonDatas;
		unordered_map<int, PokemonDesc*> pokemonDescs;

		unordered_map<int, SkillData*> skillDatas;
		unordered_map<int, SkillDesc*> skillDescs;

		unordered_map<string, vector<Rect>*> animRects;
		unordered_map<string, string> transDatas;

		unordered_map<string, Image*> uiImages;

		Image* playerInGame;
		PlayerData* playerData;
	};

private:

	static DataLoad dataLoad;

	DataLoadManager() = delete;
	~DataLoadManager() = delete;

public:

	static void Init() { dataLoad.Init(); }
	static void Reset() { dataLoad.Reset(); }

	static void SetPlayerData(PlayerData* data) { dataLoad.playerData = data; }

	static Map* GetMapData(string ID) { return dataLoad.mapDatas[ID]; }
	static Image* GetMapImage(string ID) { return dataLoad.mapImages[ID]; }

	static Image* GetPlayerInGameImage() { return dataLoad.playerInGame; }
	static Image* GetUIImage(string name) { return dataLoad.uiImages[name]; }

	static ItemDesc* GetItemDesc(int code) { return dataLoad.itemDescs[code]; }
	static PlayerData* GetPlayerData() { return dataLoad.playerData; }

	static PokemonData* GetPokemonData(int id) { return dataLoad.pokemonDatas[id]; }
	static PokemonDesc* GetPokemonDesc(int id) { return dataLoad.pokemonDescs[id]; }

	static SkillData* GetSkillData(int id) { return dataLoad.skillDatas[id]; }
	static SkillDesc* GetSkillDesc(int id) { return dataLoad.skillDescs[id]; }

	static vector<Rect>* GetAnimRect(string id) { return dataLoad.animRects[id]; }

	static Rect GetFrontPokemonImageRect(int id);
	static Rect GetBehindPokemonImageRect(int id);

	static void AddItemToInventory(int code, int count = 1) { dataLoad.AddItemToInventory(code, count); }
	static bool RemoveItemFromInventory(int code, int count = 1) { return dataLoad.RemoveItemFromInventory(code, count); }

	static float GetTypeRevision(int skillType, int pokeType) { return dataLoad.GetTypeRevision(skillType, pokeType); }
	static string GetStringData(string key) { return dataLoad.transDatas[key]; }
};

#endif // !__DATALOADMANAGER_H__
