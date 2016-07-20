#include <stdio.h>
#include "BList.h"
#include <string>

bool cb(int *v)
{
	printf("%d\n", *v);
	return true;
}

bool cb2(std::string *v)
{
	printf("%s\n", (*v).c_str());
	return false;
}

int main()
{
	BList<int, int> *list = BList<int, int>::create(8, 8);
	list->set(3, 3);
	list->set(1, 1);
	list->set(2, 2);
	list->set(5, 5);
	list->set(4, 4);
	list->set(7, 7);
	list->set(8, 8);
	list->set(0, 0);
	list->set(9, 9);
	list->set(6, 6);

	list->foreach(cb);
	list->foreach(cb);

	BList<std::string, std::string> *list2 = BList<std::string, std::string>::create(8, 8);
	
	list2->set("ddd", "ddd");
	list2->set("bbb", "bbb");
	list2->set("ccc", "ccc");
	list2->set("eee", "eee");
	list2->set("aaa", "aaa");
	list2->foreach(cb2);
	getchar();
}