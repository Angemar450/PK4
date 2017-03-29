#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
#include<chrono>

using namespace std;
using namespace chrono;

enum SORTY {
	PIWO_JESZCZE_Z_GAZEM,
	SZYBKIE,
	ZWYKLY_SORT
};

void sortowanie_babelkowe(vector<int> &tab, int n)
{
	for (int i = 1; i<n; i++)
		for (int j = n - 1; j >= 1; j--)
			if (tab[j]<tab[j - 1])
				swap(tab[j], tab[j - 1]);
}

void quicksort(vector<int> &tablica, int lewy, int prawy)
{
	int v = tablica[(lewy + prawy) / 2];
	int i, j, x;
	i = lewy;
	j = prawy;
	do {
		while (tablica[i]<v) i++;
			while (tablica[j]>v) j--;
				if (i <= j) {
					swap(tablica[i], tablica[j]);
					i++; j--;
				}
	} while (i <= j);
	if (j>lewy) quicksort(tablica, lewy, j);
	if (i<prawy) quicksort(tablica, i, prawy);
}

int main() {
	const int ile = 10000;
	int tab_statyczna[ile];

	const int zakres = 101;

	srand(static_cast<unsigned int>(time(NULL)));

	for (int i = 0; i < ile; ++i)
		tab_statyczna[i] = rand() % zakres;

	vector<int> wektor_intow_1;
	vector<int> wektor_intow_2;
	vector<int> wektor_intow_3;

	map<SORTY, duration<double, milli>> czasy_calowite;
	int ile_sortowan = 0;

	cout << "Czasy sortowan wg roznych algorytmow.\nRadze uzbroic sie w cierpliwosc, tam jest bubble sort,\nktory dla takiej tablicy jak ta (10000 elemento trwa 5 min z czubem)" << endl;

	for (int i = 0; i < ile; ++i)
		wektor_intow_1.push_back(tab_statyczna[i]);

	auto start = steady_clock::now();

	sortowanie_babelkowe(wektor_intow_1, ile);

	auto stop = steady_clock::now();

	czasy_calowite.insert_or_assign(PIWO_JESZCZE_Z_GAZEM, static_cast<duration<double, milli>>(stop - start));

	++ile_sortowan;
	wektor_intow_1.clear();

	//===================================

	for (int i = 0; i < ile; ++i)
		wektor_intow_2.push_back(tab_statyczna[i]);

	int poczatek = 0;
	int koniec = ile - 1;

	start = steady_clock::now();

	quicksort(wektor_intow_2, poczatek, koniec);

	stop = steady_clock::now();

	czasy_calowite.insert_or_assign(SZYBKIE, static_cast<duration<double, milli>>(stop - start));

	++ile_sortowan;
	wektor_intow_2.clear();

	//===================================

	for (int i = 0; i < ile; ++i)
		wektor_intow_3.push_back(tab_statyczna[i]);

	start = steady_clock::now();

	std::sort(wektor_intow_3.begin(), wektor_intow_3.end());

	stop = steady_clock::now();

	czasy_calowite.insert_or_assign(ZWYKLY_SORT, static_cast<duration<double, milli>>(stop - start));

	++ile_sortowan;
	wektor_intow_3.clear();

	//===================================

	for (int i = 0; i < ile_sortowan; ++i) {
		try {
			switch (i) {
			case PIWO_JESZCZE_Z_GAZEM:
				cout << "Czas sortowania babelkowego: " << czasy_calowite.at(PIWO_JESZCZE_Z_GAZEM).count() << " ms" << endl;
				break;
				
			case SZYBKIE:
				cout << "Czas sortownaia szybkiego: " << czasy_calowite.at(SZYBKIE).count() << " ms" << endl;
				break;

			case ZWYKLY_SORT:
				cout << "Czas sortowania algorytmem z biblioteki: " << czasy_calowite.at(ZWYKLY_SORT).count() << " ms" << endl;
				break;

			default:
				cout << "Nieznany sposob sortowania!" << endl;
				break;
			}
		}
		catch (const out_of_range& exc) {
			cout << "Nieprzewidziane wyjscie poza zakres!" << endl;
		}
	}

	czasy_calowite.clear();

	std::system("pause");
	return 0;
}