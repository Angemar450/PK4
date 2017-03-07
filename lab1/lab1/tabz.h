#pragma once
#include"zwierz.h"


class tabz {
	const int ile = 8;
	zwierz **tablica;

public:
	void wypelnij();
	void wypisz_typy();

	void glosy_typeid();
	void glosy_dynamic();

	~tabz();
};

enum typ {
	ZWIERZE = 1,
	PIES,
	KOT,
	CHOMIK
};