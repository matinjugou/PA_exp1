#ifndef CHARSTRING_H
#define CHARSTRING_H
#include <string>
#include <iostream>

using namespace std;

class CharString
{
private:
	int length;
	wchar_t* data;
public:
	CharString();
	CharString(wchar_t* sourceString);
	CharString(const CharString& sourceString);
	~CharString();
public:
	int indexOf(const wchar_t * stringToFind, int pos);
	int indexOf(const CharString &stringToFind, int pos);
	int getLength() const;
	wchar_t* getData() const;
	wchar_t operator[](int index) const;
	CharString substring(int pos, int end) const;
	void concat(const CharString & stringToConcat);
	CharString& operator=(const char * sourceString);
	CharString& operator=(wchar_t* sourceString);
	CharString& operator=(const CharString & sourceString);
	bool operator==(const CharString& sourceString);
	bool operator==(const wchar_t * sourceString);
	CharString operator+(const CharString & stringToPlus);
	CharString operator+(wchar_t charToPlus);
	friend wostream& operator << (wostream& outputStream, CharString& outputString);
};

#endif