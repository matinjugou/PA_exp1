#include "Functions.h"
#include "Stack.cpp"
#include <io.h>

using namespace std;

FileInfo extractInfo(const char* fileName)
{
	FileInfo fileInformation;
	fileInformation.author = L"";
	fileInformation.question = L"";
	fileInformation.text = L"";
	fileInformation.title = L"";
	string textLine = "";
	CharString FileText = L"";
	char tmpFileName[100];
	sprintf_s(tmpFileName, 100, "input\\%s", fileName);
	ifstream inputFile(tmpFileName);
	while (getline(inputFile, textLine))
	{
		CharString tmpString;
		tmpString = textLine.c_str();
		FileText = FileText + tmpString;
	}
	inputFile.close();
	inputFile.clear();

	CharStringLink textLink;
	int i = 0;
	while (i < FileText.getLength())
	{
		CharString *tmpString = new CharString;
		CharString tmpString2;
		if (FileText[i] == L'<')
		{
			int pos = FileText.indexOf(L">", i);
			*tmpString = FileText.substring(i, pos);
			i = pos + 1;
			textLink.add(tmpString);
		}
		else
		{
			int pos = FileText.indexOf(L"<", i);
			*tmpString = FileText.substring(i, pos - 1);
			i = pos;
			textLink.add(tmpString);
		}
	}
	Stack<CharStringNode*> FileStack;
	CharStringNode *p = textLink.getData()->last;
	while (p != textLink.getData())
	{
		FileStack.push(p);
		if ((FileStack.top()->NodeType == 1) && (FileStack.top()->TagType == 0))
		{
			if (FileStack.top()->className.getLength() > 0)
			{
				if ((FileStack.top()->className == L"author") || (FileStack.top()->className == L"headline-title")
					|| (FileStack.top()->className == L"question-title") || (FileStack.top()->className == L"content"))
				{
					CharString tmpTagName = FileStack.top()->tagName;
					CharString tmpClassName = FileStack.top()->className;
					CharString tmpText = L"";
					int stackLevel = 1;
					FileStack.pop();
					while (stackLevel > 0)
					{
						if (FileStack.top()->NodeType == 0)
						{
							tmpText.concat(*FileStack.top()->data);
							FileStack.pop();
						}
						else
						{
							if (FileStack.top()->tagName == tmpTagName)
							{
								if (FileStack.top()->TagType == 0)
								{
									stackLevel++;
								}
								else if (FileStack.top()->TagType == 1)
								{
									stackLevel--;
								}
							}
							else if (((FileStack.top()->tagName == L"p") || (FileStack.top()->tagName == L"li")) && (FileStack.top()->TagType == 1))
							{
								tmpText = tmpText + L'\n';
							}
							FileStack.pop();
						}
					}
					if (tmpClassName == L"author")
					{
						while (tmpText.getData()[tmpText.getLength() - 1] < 19968 || tmpText.getData()[tmpText.getLength() - 1] > 40869)
							tmpText = tmpText.substring(0, tmpText.getLength() - 2);
						fileInformation.author = tmpText;
					}
					else if (tmpClassName == L"headline-title")
					{
						fileInformation.title = tmpText;
					}
					else if (tmpClassName == L"question-title")
					{
						fileInformation.question = tmpText;
					}
					else if (tmpClassName == L"content")
					{
						CharString tmpString = L"客官，这篇文章有意思吗";
						if (tmpText.indexOf(tmpString, 0) == -1)
						{
							fileInformation.text = tmpText + fileInformation.text;
						}
					}
				}
			}
		}
		p = p->last;
	}
	return fileInformation;
}

dicTree* initDictionary(char * fileName)
{
	string words;
	ifstream inputDic(fileName);
	dicTree* newDicTree = new dicTree;
	while (getline(inputDic, words))
	{
		CharString tmpString;
		tmpString = words.c_str();
		if (tmpString[0] == wchar_t(65279))
		{
			tmpString = tmpString.substring(1, tmpString.getLength() - 1);
		}
		newDicTree->insertString(tmpString);
	}
	inputDic.close();
	return newDicTree;
}

CharStringLink * divideWords(const CharString & fileText, const dicTree* Dic)
{
	if (fileText.getLength() == 0)
		return NULL;
	CharString textPart1 = L"";
	dicTree foundWords;
	int strBegin = 0;
	int strEnd = 0;
	int tmpEnd = 0;
	textPart1 = fileText.substring(strBegin, strEnd);

	int findResult;
	while (true)
	{
		findResult = Dic->findString(textPart1);
		if (findResult != 0)
		{
			if (findResult == 2)
			{
				strEnd = tmpEnd;
			}
			tmpEnd++;
			textPart1 = fileText.substring(strBegin, tmpEnd);
			while ((tmpEnd < fileText.getLength()) && ((findResult = Dic->findString(textPart1)) != 0))
			{
				if (findResult == 2)
					strEnd = tmpEnd;
				tmpEnd++;
				if (tmpEnd >= (fileText.getLength()))
					break;
				textPart1 = fileText.substring(strBegin, tmpEnd);
			}
			textPart1 = fileText.substring(strBegin, strEnd);
			foundWords.insertString(textPart1);
		}
		strBegin = strEnd + 1;
		strEnd = strBegin;
		tmpEnd = strBegin;
		if (strBegin > (fileText.getLength() - 1))
			break;
		textPart1 = fileText.substring(strBegin, strEnd);
	}
	CharStringLink* ansLink = new CharStringLink;
	struct recordNode
	{
		trieNode* curNode;
		CharString curString;
	};

	Stack<recordNode> ansStack;

	recordNode startNode;
	startNode.curNode = foundWords.getRoot()->leftNode;
	startNode.curString = L"";
	ansStack.push(startNode);
	while (!ansStack.isEmpty())
	{
		recordNode topNode = ansStack.top();
		ansStack.pop();
		if (topNode.curNode->leftNode == NULL)
		{
			CharString tmpString;
			tmpString = topNode.curString + topNode.curNode->character;
			if (tmpString.getLength() > 1)
				ansLink->add(tmpString);
		}
		else
		{
			recordNode tmpNode;
			tmpNode.curNode = topNode.curNode->leftNode;
			tmpNode.curString = topNode.curString + topNode.curNode->character;
			ansStack.push(tmpNode);
		}
		if (topNode.curNode->rightNode != NULL)
		{
			recordNode tmpNode;
			tmpNode.curNode = topNode.curNode->rightNode;
			tmpNode.curString = topNode.curString;
			ansStack.push(tmpNode);
		}
	}
	return ansLink;
}

void getFiles(DirInfo& dir)
{
	intptr_t hFile = 0;
	struct _finddata_t fileInfo;
	const char *toSearch = "input\\*.html";
	hFile = _findfirst(toSearch, &fileInfo);
	if (hFile != -1)
	{
		dir.fileNames[dir.filesNum] = new char[128];
		strcpy_s(dir.fileNames[dir.filesNum], 128, fileInfo.name);
		dir.filesNum++;
		while (!_findnext(hFile, &fileInfo))
		{
			dir.fileNames[dir.filesNum] = new char[128];
			strcpy_s(dir.fileNames[dir.filesNum], 128, fileInfo.name);
			dir.filesNum++;
		}
		_findclose(hFile);
	}
}

void work()
{
	DirInfo dir;
	wofstream outputFile;
	outputFile.imbue(locale(locale(), "", LC_CTYPE));
	dir.fileNames = new char*[100];
	dir.filesNum = 0;
	getFiles(dir);
	dicTree* Dictionary;
	Dictionary = initDictionary("词库.dic");
	system("md output");
	for (int i = 0; i < dir.filesNum; i++)
	{
		FileInfo fileInformation;
		CharStringLink* divideResult;
		fileInformation = extractInfo(dir.fileNames[i]);
		cout << dir.fileNames[i] << " is extracted." << endl;
		divideResult = divideWords(fileInformation.text, Dictionary);
		cout << dir.fileNames[i] << " is divided." << endl;
		char* outputFileInfo = new char[100];
		char* outputFileTxt = new char[100];
		char* outputFileName = new char[100];
		strncpy_s(outputFileName, 100, dir.fileNames[i], strlen(dir.fileNames[i]) - 5);
		sprintf_s(outputFileInfo, 100, "%s%s%s", "output\\", outputFileName, ".info");
		sprintf_s(outputFileTxt, 100, "%s%s%s", "output\\", outputFileName, ".txt");
		outputFile.open(outputFileInfo, ios::out|ios::trunc);
		outputFile << fileInformation.title << endl << fileInformation.question << endl << fileInformation.author << endl << fileInformation.text;
		outputFile.close();
		outputFile.open(outputFileTxt, ios::out|ios::trunc);
		if (divideResult != NULL)
			divideResult->print(outputFile);
		outputFile.close();
		delete[] outputFileInfo;
		delete[] outputFileTxt;
		delete[] outputFileName;
		delete divideResult;
	}
	Stack<trieNode*> dictionaryStack;
	dictionaryStack.push(Dictionary->getRoot());
	while (!dictionaryStack.isEmpty())
	{
		trieNode* tmpNode = dictionaryStack.top();
		dictionaryStack.pop();
		if (tmpNode->leftNode != NULL)
		{
			dictionaryStack.push(tmpNode->leftNode);
		}
		if (tmpNode->rightNode != NULL)
		{
			dictionaryStack.push(tmpNode->rightNode);
		}
		delete tmpNode;
	}
	for (int i = 0; i < dir.filesNum; i++)
	{
		delete[] dir.fileNames[i];
	}
	delete[] dir.fileNames;
	return;
}