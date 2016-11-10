#include "CharStringLink.h"

CharStringLink::CharStringLink()
{
	length = 0;
	data = new CharStringNode;
	data->data = NULL;
	data->next = data;
	data->last = data;
}

CharStringLink::~CharStringLink()
{
	CharStringNode *p = data, *q = data;
	for (int i = 0; i <= length; i++)
	{
		p = p->next;
		delete q;
		q = p;
	}
}

CharStringNode * CharStringLink::getData()
{
	return data;
}

void CharStringLink::add(CharString * stringToAdd)
{
	CharStringNode* tmpNode = new CharStringNode;
	tmpNode->data = stringToAdd;
	tmpNode->next = data;
	tmpNode->last = data->last;
	tmpNode->tagName = L"";
	tmpNode->className = L"";
	if (stringToAdd->indexOf(L"<", 0) == 0)
	{
		tmpNode->NodeType = 1;
		if (stringToAdd->indexOf(L"</", 0) != -1)
		{
			tmpNode->TagType = 1;
			tmpNode->tagName = stringToAdd->substring(2, stringToAdd->getLength() - 2);
		}
		else
		{
			tmpNode->TagType = 0;
			int spacePos = stringToAdd->indexOf(L" ", 0);
			if (spacePos != -1)
			{
				tmpNode->tagName = stringToAdd->substring(1, spacePos - 1);
			}
			else
			{
				tmpNode->tagName = stringToAdd->substring(1, stringToAdd->getLength() - 2);
			}
		}
		int classPos = stringToAdd->indexOf(L"class", 0);
		if (classPos != -1)
		{
			int classNameStart = stringToAdd->indexOf(L"\"", classPos) + 1;
			int classNameEnd = stringToAdd->indexOf(L"\"", classNameStart) - 1;
			tmpNode->className = stringToAdd->substring(classNameStart, classNameEnd);
		}
	}
	else
	{
		tmpNode->NodeType = 0;
	}
	data->last->next = tmpNode;
	data->last = tmpNode;
	length++;
}

void CharStringLink::add(const CharString & stringToAdd)
{
	CharString* tmpNode = new CharString;
	*tmpNode = stringToAdd;
	add(tmpNode);
}

void CharStringLink::remove(CharString * stringToRemove)
{
	CharStringNode *p = data->next;
	while ((p != data) && (p->data != stringToRemove))
	{
		p = p->next;
	}
	if (p == data)
		return;
	p->last->next = p->next;
	p->next->last = p->last;
	delete p;
	return;
}

CharString * CharStringLink::search(CharString * stringToFind)
{
	CharStringNode *p = data->next;
	while (p != data)
	{
		if ((p->data == stringToFind) || (*p->data == *stringToFind))
			return p->data;
	}
	return nullptr;
}

void CharStringLink::print()
{
	CharStringNode *p;
	p = data->next;
	wcout.imbue(locale(locale(), "", LC_CTYPE));
	while (p != data)
	{
		wcout << *p->data << endl;
		p = p->next;
	}
}

void CharStringLink::print(wostream & outputStream)
{
	CharStringNode *p;
	p = data->next;
	outputStream.imbue(locale(locale(), "", LC_CTYPE));
	while (p != data)
	{
		outputStream << *p->data << endl;
		p = p->next;
	}
}
