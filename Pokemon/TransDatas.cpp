#include "TransDatas.h"
#include "framework.h"
#include "DataLoadManager.h"

#include <cstdarg>

TokenChange::TokenChange(string _token, string _change)
	: token(_token), change(_change) { }

void StringReplaceMent(string & str, const string & from, const string & to)
{
	size_t startPos = 0;

	string _from = "{" + from + "}";

	while ((startPos = str.find(_from, startPos)) != string::npos)
	{
		str.replace(startPos, _from.length(), to);
		startPos += to.length();
	}
}

string TransString(TCHAR* buffer, const string& key)
{
	string ret = DataLoadManager::GetStringData(key);

	if(buffer != NULL)
		_tcscpy_s(buffer, ret.length() + 1, CA2T(ret.c_str()));

	return ret;
}

string TransString(TCHAR* buffer, const string & key, int count, const TokenChange ...)
{
	string ret = DataLoadManager::GetStringData(key);

	va_list ap;

	va_start(ap, count);

	for (int i = 0; i < count; ++i)
	{
		TokenChange tc = va_arg(ap, TokenChange);
		StringReplaceMent(ret, tc.token, tc.change);
	}

	va_end(ap);

	if(buffer != NULL)
		_tcscpy_s(buffer, ret.length() + 1, CA2T(ret.c_str()));

	return ret;
}
