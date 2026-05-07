#include <iostream>
#include "DS/Array.h"
#include "DS/LinkedList.h"

void PrintList(const LinkedList<int>& list)
{
	for (int i = 0; i < list.size(); i++)
	{
		std::cout << list[i] << std::endl;
	}
}

int main()
{
	LinkedList<int> list;

	list.InsertAtEnd(1);
	list.InsertAtEnd(2);
	list.InsertAtEnd(3);
	list.InsertAtEnd(4);
	list.InsertAtEnd(5);

	return 0;
}