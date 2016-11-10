#include "Stack.h"
#include <iostream>

template<class T>
Stack<T>::Stack()
{
	size = 16;
	stackTop = 0;
	data = new T[size];
}

template<class T>
Stack<T>::~Stack()
{
	delete[] data;
}

template<class T>
int Stack<T>::push(const T &newNode)
{
	if (stackTop == size)
	{
		T* tmp = new T[size * 2];
		for (int i = 0; i < stackTop; i++)
		{
			tmp[i] = data[i];
		}
		size = size * 2;
		T* p = data;
		data = tmp;
		delete[] p;
	}
	data[stackTop] = newNode;
	stackTop++;
	return 0;
}

template<class T>
void Stack<T>::pop()
{
	stackTop--;
}

template<class T>
T Stack<T>::top()
{
	return data[stackTop - 1];
}

template<class T>
void Stack<T>::empty()
{
	stackTop = 0;
}

template<class T>
bool Stack<T>::isEmpty() const
{
	if (stackTop == 0)
		return true;
	else
		return false;
}

