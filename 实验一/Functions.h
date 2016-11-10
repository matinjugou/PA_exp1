#pragma once
#include "Stack.h"
#include "CharString.h"
#include "CharStringLink.h"
#include "Trie.h"
#include <Windows.h>
#include <string>
#include <fstream>

using namespace std;

struct FileInfo
{
	CharString title;
	CharString author;
	CharString question;
	CharString text;
};

struct DirInfo
{
	char** fileNames;
	int filesNum;
};

void work();

void getFiles(DirInfo& dir);

FileInfo extractInfo(const char* fileName);

dicTree* initDictionary(char* fileName);

CharStringLink* divideWords(const CharString& fileText, const dicTree* Dic);