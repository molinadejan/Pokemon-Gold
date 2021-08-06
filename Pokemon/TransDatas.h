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

// UI�� ��Ÿ �ؽ�Ʈ�� ���� �޼���
string TransString(TCHAR* buffer, const string& key);

string TransString(TCHAR* buffer, const string& key, int count, const TokenChange...);

// ������ �ڵ带 ������ �̸� ��ȯ??

// ���ϸ� �ڵ带 ������ �̸� ��ȯ??

#endif // !__TRANSDATAS_H__
