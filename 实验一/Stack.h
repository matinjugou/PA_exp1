#ifndef STACK_H
#define STACK_H

template<class T>
class Stack
{
private:
	int stackTop;
	int size;
	T* data;
public:
	Stack();
	~Stack();
public:
	int push(const T &newNode);
	void pop();
	T top();
	void empty();
	bool isEmpty() const;
};

#endif