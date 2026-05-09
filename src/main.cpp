#include <iostream>
#include "DS/Array.h"
#include "DS/Queue.h"

int main()
{
	Queue<int> q;

	q.push(10);
	q.push(20);
	q.push(30);
	q.push(40);
	q.push(50);

	std::cout << "Queue : \n";
	q.Print();

	std::cout << "Size : " << q.size() << std::endl;
	std::cout << "front : " << q.front() << std::endl;
	std::cout << "back : " << q.back() << std::endl;

	q.pop();

	std::cout << "After pop : \n\n";
	q.Print();


	return 0;
}