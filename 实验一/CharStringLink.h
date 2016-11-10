#ifndef CHARSTRINGLINK_H
#define CHARSTRINGLINK_H
#include "CharString.h"

struct CharStringNode
{
	CharString* data;
	CharStringNode* next;
	CharStringNode* last;
	CharString tagName;
	CharString className;
	int NodeType;		//0-正文，1-标签
	int TagType;		//0-开始标签，1-结束标签，2-自闭合标签
};

class CharStringLink
{
private:
	int length;
	CharStringNode* data;
public:
	CharStringLink();
	~CharStringLink();
public:
	CharStringNode* getData();
	void add(CharString* stringToAdd);
	void add(const CharString & stringToAdd);
	void remove(CharString* stringToRemove);
	CharString* search(CharString* stringToFind);
	void print();
	void print(wostream & outputStream);
};

#endif
