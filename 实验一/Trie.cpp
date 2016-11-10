#include "Trie.h"

dicTree::dicTree()
{
	root = new trieNode;
	root->leftNode = NULL;
	root->rightNode = NULL;
}

dicTree::~dicTree()
{
	delete root;
}

void dicTree::insertString(const CharString & stringToInsert)
{
	trieNode* curNode = root;
	int i = 0;
	while (i < stringToInsert.getLength())
	{
		if (curNode->leftNode == NULL)
		{
			trieNode* tmpNode = new trieNode;
			tmpNode->character = stringToInsert[i];
			tmpNode->isWordEnd = 1;
			curNode->leftNode = tmpNode;
			i++;
			curNode = tmpNode;
		}
		else
		{
			if (curNode->leftNode->character == stringToInsert[i])
			{
				i++;
				curNode = curNode->leftNode;
			}
			else
			{
				trieNode* p = curNode->leftNode->rightNode;
				while ((p != NULL) && (p->character != stringToInsert[i]))
					p = p->rightNode;
				if (p == NULL)
				{
					p = new trieNode;
					p->character = stringToInsert[i];
					p->rightNode = curNode->leftNode;
					p->isWordEnd = 1;
					curNode->leftNode = p;
					curNode = p;
					i++;
				}
				else
				{
					curNode = p;
					i++;
				}
			}
		}
		if (i == stringToInsert.getLength())
			curNode->isWordEnd = 2;
	}
}


int dicTree::findString(const CharString & stringToFind) const
{
	trieNode* curNode = root->leftNode;
	int i = 0;
	while (i < stringToFind.getLength())
	{
		while ((curNode != NULL) && (curNode->character != stringToFind[i]))
		{
			curNode = curNode->rightNode;
		}
		if (curNode == NULL)
		{
			return 0;
		}
		else
		{
			if (i == (stringToFind.getLength() - 1))
			{
				return curNode->isWordEnd;
			}
			else
			{
				curNode = curNode->leftNode;
				i++;
			}
		}
	}
}

trieNode * dicTree::getRoot() const
{
	return root;
}
