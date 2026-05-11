#include <iostream>
#include "DS/Array.h"
#include "DS/Queue.h"
#include "DS/DynamicArray.h"

void Print(const DynamicArray<int>& arr)
{
	for (const int& x : arr)
	{
		std::cout << x << std::endl;
	}
}

int main()
{
	DynamicArray<int> dArr(5);

	dArr[0] = 1;
	dArr[1] = 2;
	dArr[2] = 3;
	dArr[3] = 4;
	dArr[4] = 5;


	std::cout << "Before inserting" << std::endl;
	Print(dArr);

	std::cout << "After inserting" << std::endl;
	dArr.InsertLast(55);
	std::cout << "new Size = " << dArr.size() << std::endl;
	Print(dArr);

	return 0;
}