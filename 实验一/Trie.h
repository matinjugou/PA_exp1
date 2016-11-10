#ifndef TRIE_H
#define TRIE_H

#include "CharString.h"
#include <iostream>

class trieNode
{
public:
	wchar_t character;
	int isWordEnd;	//1-ÊÇÇ°×º£¬2-ÊÇ´ÊÓï
	trieNode* leftNode;
	trieNode* rightNode;
public:
	trieNode()
	{
		isWordEnd = false;
		leftNode = NULL;
		rightNode = NULL;
	}
	~trieNode()
	{
	}
};

class dicTree
{
private:
	trieNode* root;
public:
	dicTree();
	~dicTree();
public:
	void insertString(const CharString& stringToInsert);
	int findString(const CharString& stringToFind) const;
	trieNode* getRoot() const;
};

#endif