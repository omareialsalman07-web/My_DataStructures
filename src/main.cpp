#include <iostream>

#include "DS/LinkedList.h"


int main()
{
	LinkedList<int> list;

	list.push_back(-12);
	list.push_back(13);
	list.push_back(14);

	for (auto x : list)
	{
		std::cout << x << std::endl;
	}
	
	return 0;
}