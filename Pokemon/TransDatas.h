#pragma once

#ifndef __TRANSDATAS_H__
#define __TRANSDATAS_H__

#include <string>
#include <tchar.h>

using std::string;

struct TokenChange
{
	string token;
	string change;

	TokenChange(string _token, string _change);
};

void StringReplaceMent(string& str, const string& from, const string& to);

// UI나 기타 텍스트를 위한 메서드
string TransString(TCHAR* buffer, const string& key);

string TransString(TCHAR* buffer, const string& key, int count, const TokenChange...);

// 아이템 코드를 넣으면 이름 반환??

// 포켓몬 코드를 넣으면 이름 반환??

#endif // !__TRANSDATAS_H__
