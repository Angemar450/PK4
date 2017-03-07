#include<iostream>
#include"tabz.h"

using namespace std;

int main() {
	tabz tablica_stworow;

	tablica_stworow.wypelnij();
	tablica_stworow.wypisz_typy();

	tablica_stworow.glosy_typeid();
	tablica_stworow.glosy_dynamic();

	system("pause");
	return 0;
}