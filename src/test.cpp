#include <stdio.h>
#include "BList.h"

bool cb(int *v)
{
	printf("%d\n", *v);
	return false;
}

int main()
{
	BList<int, int> *list = BList<int, int>::create(8, 16);
	list->set(3, 3);
	list->set(1, 1);
	list->set(2, 2);
	list->set(5, 5);
	list->set(4, 4);
	list->foreach(cb);

	getchar();
}