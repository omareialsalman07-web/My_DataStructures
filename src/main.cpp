#include <iostream>
#include "DS/Array.h"

int main()
{
	Array<int, 5> arr;

	arr[0] = 1;
	arr[1] = 2;
	arr[2] = 3;
	arr[3] = 4;
	arr[4] = 5;


	for (int i = 0; i < arr.size(); i++)
	{
		std::cout << arr[i] << std::endl;
	}

	return 0;
}