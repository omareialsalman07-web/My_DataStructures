#include <iostream>
#include "DS/Array.h"
#include "DS/Queue.h"
#include "DS/DynamicArray.h"

int main()
{
	DynamicArray<int> dArr(5);

	dArr[0] = 1;
	dArr[1] = 2;
	dArr[2] = 3;
	dArr[3] = 4;
	dArr[4] = 5;

	dArr.DeleteItem(3);

	for (const int& x : dArr)
	{
		std::cout << x << std::endl;
	}

	return 0;
}