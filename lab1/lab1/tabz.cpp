#include<iostream>
#include"pies.h"
#include"kot.h"
#include"chomik.h"
#include"tabz.h"

using namespace std;

void tabz::wypelnij() {
	int wybierz_typ;
	tablica = new zwierz*[ile];
	for (int i = 0; i < ile; ++i) {
		cout << "Wprowadz liczbe z zakresu od 1 do 4:";
		cin >> wybierz_typ;

		switch (wybierz_typ)
		{
		case ZWIERZE:
			tablica[i] = new zwierz;
			break;

		case PIES:
			tablica[i] = new pies;
			break;

		case KOT:
			tablica[i] = new kot;
			break;

		case CHOMIK:
			tablica[i] = new chomik;
			break;

		default:
			tablica[i] = new zwierz;
			break;
		}
	}
}

void tabz::wypisz_typy() {
	for (int i = 0; i < ile; ++i)
		cout << "Typ elementu nr " << i << ": " << typeid(*tablica[i]).name() << endl;
}

void tabz::glosy_typeid() {
	cout << "Glosy psow:" << endl;

	for (int i = 0; i < ile; ++i)
		if (typeid(*tablica[i]) == typeid(pies)) {
			cout << "Szczeka pies spod indeksu " << i << ": ";
			tablica[i]->daj_glos();
		}

	cout << "Glosy kotow:" << endl;

	for (int i = 0; i < ile; ++i)
		if (typeid(*tablica[i]) == typeid(kot)) {
			cout << "Miauczy kot spod indeksu " << i << ": ";
			tablica[i]->daj_glos();
		}

	cout << "Glosy chomikow:" << endl;

	for (int i = 0; i < ile; ++i)
		if (typeid(*tablica[i]) == typeid(chomik)) {
			cout << "Cos robi chomik spod indeksu " << i << ": ";
			tablica[i]->daj_glos();
		}

	cout << "Glosy nie-wiadomo-czego:" << endl;

	for (int i = 0; i < ile; ++i)
		if (typeid(*tablica[i]) == typeid(zwierz)) {
			cout << "Daje glos zwierze spod indeksu " << i << ": ";
			tablica[i]->daj_glos();
		}
}

void tabz::glosy_dynamic() {
	cout << "Glosy psow:" << endl;

	for (int i = 0; i < ile; ++i)
		if (dynamic_cast<pies*>(tablica[i])) {
			cout << "Szczeka pies spod indeksu " << i << ": ";
			tablica[i]->daj_glos();
		}

	cout << "Glosy kotow:" << endl;

	for (int i = 0; i < ile; ++i)
		if (dynamic_cast<kot*>(tablica[i])) {
			cout << "Miauczy kot spod indeksu " << i << ": ";
			tablica[i]->daj_glos();
		}

	cout << "Glosy chomikow:" << endl;

	for (int i = 0; i < ile; ++i)
		if (dynamic_cast<chomik*>(tablica[i])) {
			cout << "Cos robi chomik spod indeksu " << i << ": ";
			tablica[i]->daj_glos();
		}
}

tabz::~tabz() {
	for (int i = 0; i < ile; ++i)
		delete tablica[i];

	delete tablica;
}