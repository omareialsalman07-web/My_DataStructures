#include <iostream>
#include "DS/Array.h"
#include "DS/LinkedList.h"

int main()
{
	Array<int, 5> arr;

	arr[0] = 1;
	arr[1] = 2;
	arr[2] = 3;
	arr[3] = 4;
	arr[4] = 5;

	std::cout << "Array >>> \n\n";
	for (const auto& x : arr)
	{
		std::cout << "\t";
		std::cout << x << std::endl;
	}

	LinkedList<int> list;

	list.InsertAtEnd(1);
	list.InsertAtEnd(2);
	list.InsertAtEnd(3);
	list.InsertAtEnd(4);
	list.InsertAtEnd(5);

	std::cout << "\nList >>> \n\n";
	std::cout << list[3];

	return 0;
}