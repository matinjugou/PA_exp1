#include "CharString.h"
#include <windows.h>
#include <iostream>

CharString::CharString()
{
	data = NULL;
	length = 0;
}

CharString::CharString(wchar_t* sourceString)
{
	int l = wcslen(sourceString);
	wchar_t* buff = new wchar_t[l + 1];
	memset(buff, '\0', sizeof(wchar_t) * (l + 1));
	swprintf_s(buff, l + 1, L"%s", sourceString);
	
	wchar_t *p = data;
	data = buff;
	delete[] p;
	length = l;
}

CharString::CharString(const CharString& sourceString)
{
	length = wcslen(sourceString.getData());
	wchar_t *p = data;
	data = new wchar_t[length + 1];
	if (!p)
	{
		delete[] p;
	}
	memset(data, L'\0', sizeof(wchar_t) * (length + 1));
	swprintf_s(data, length + 1, L"%s", sourceString.getData());
}

CharString::~CharString()
{
	delete[] data;
}

wchar_t* CharString::getData() const
{
	return data;
}

int CharString::indexOf(const wchar_t * stringToFind, int pos)
{
	//TODO KMP
	int len = wcslen(stringToFind);
	int * next = new int[len + 1];
	next[0] = -1;
	for (int i = 1; i < len; i++)
	{
		int j = next[i - 1];
		while (j != -1 && stringToFind[i] != stringToFind[j + 1])
			j = next[j];
		if (stringToFind[i] == stringToFind[j + 1])
			next[i] = j + 1;
		else
			next[i] = -1;
	}
	int match = -1;
	for (int i = pos; i < length; i++)
	{
		while (match != -1 && data[i] != stringToFind[match + 1])
			match = next[match];
		if (data[i] == stringToFind[match + 1])
			match++;
		if (match == len - 1)
		{
			delete[] next;
			return i - match;
		}
	}
	delete[] next;
	return -1;
}

int CharString::indexOf(const CharString & stringToFind, int pos)
{
	//TODO KMP
	int * next = new int[stringToFind.getLength()];
	next[0] = -1;
	for (int i = 1; i < stringToFind.getLength(); i++)
	{
		int j = next[i - 1];
		while (j != -1 && stringToFind[i] != stringToFind[j + 1])
			j = next[j];
		if (stringToFind[i] == stringToFind[j + 1])
			next[i] = j + 1;
		else
			next[i] = -1;
	}
	int match = -1;
	for (int i = pos; i < length; i++)
	{
		while (match != -1 && data[i] != stringToFind[match + 1])
			match = next[match];
		if (data[i] == stringToFind[match + 1])
			match++;
		if (match == stringToFind.getLength() - 1)
		{
			delete[] next;
			return i - match;
		}
	}
	delete[] next;
	return -1;
}

int CharString::getLength() const
{
	return length;
}

wchar_t CharString::operator[](int index) const
{
	return data[index];
}

CharString CharString::substring(int pos, int end) const
{
	int len = end - pos + 2;
	wchar_t* buff = new wchar_t[len];
	memset(buff, L'\0', sizeof(wchar_t) * len);
	for (int i = pos; i <= end; i++)
	{
		buff[i - pos] = data[i];
	}
	CharString tmp;
	tmp = buff;
	return tmp;
}

void CharString::concat(const CharString & stringToConcat)
{
	int nLen = length + stringToConcat.getLength();
	wchar_t* buff = new wchar_t[nLen + 1];
	memset(buff, L'\0', sizeof(wchar_t) * (nLen + 1));
	swprintf_s(buff, nLen + 1, L"%s%s", data, stringToConcat.getData());
	wchar_t* p = data;
	data = buff;
	length = nLen;
	delete[] p;
}

CharString& CharString::operator=(wchar_t * sourceString)
{
	int l = wcslen(sourceString);
	wchar_t* buff = new wchar_t[l + 1];
	memset(buff, '\0', sizeof(wchar_t) * (l + 1));
	swprintf_s(buff, l + 1, L"%s", sourceString);
	wchar_t *p = data;
	data = buff;
	delete[] p;
	length = l;
	return *this;
}

CharString& CharString::operator=(const char * sourceString)
{
	int nLen = MultiByteToWideChar(CP_UTF8, 0, sourceString, -1, NULL, 0);
	wchar_t* pResult = new wchar_t[nLen + 1];
	memset(pResult, 0, nLen + 1);
	MultiByteToWideChar(CP_UTF8, 0, sourceString, -1, pResult, nLen);
	wchar_t *p = data;
	data = pResult;
	delete[] p;
	nLen = wcslen(pResult);
	length = nLen;
	return *this;
}

CharString& CharString::operator=(const CharString & sourceString)
{
	length = wcslen(sourceString.getData());
	wchar_t *p = data;
	data = new wchar_t[length + 1];
	if (!p)
	{
		delete[] p;
	}
	memset(data, L'\0', sizeof(wchar_t) * (length + 1));
	swprintf_s(data, length + 1, L"%s", sourceString.getData());
	return *this;
}

bool CharString::operator==(const CharString & sourceString)
{
	if (length == sourceString.getLength())
	{
		if (wcscmp(data, sourceString.getData()) == 0)
		{
			return true;
		}
	}
	return false;
}

bool CharString::operator==(const wchar_t * sourceString)
{
	if (wcscmp(data, sourceString) == 0)
	{
		return true;
	}
	return false;
}

CharString CharString::operator+(const CharString & stringToPlus)
{
	int nLen = length + stringToPlus.getLength();
	wchar_t* buff = new wchar_t[nLen + 1];
	memset(buff, L'\0', sizeof(wchar_t) * (nLen + 1));
	swprintf_s(buff, nLen + 1, L"%s%s", data, stringToPlus.getData());

	CharString tmpString;
	tmpString = buff;
	delete[] buff;
	return tmpString;
}

CharString CharString::operator+(wchar_t charToPlus)
{
	int nLen = length + 1;
	wchar_t* buff = new wchar_t[nLen + 1];
	memset(buff, L'\0', sizeof(wchar_t) * (nLen + 1));
	swprintf_s(buff, nLen + 1, L"%s%c", data, charToPlus);

	CharString tmpString;
	tmpString = buff;
	delete[] buff;
	return tmpString;
}


wostream & operator<<(wostream & outputStream, CharString & outputString)
{
	outputStream << outputString.getData();
	return outputStream;
	// TODO: 在此处插入 return 语句
}
