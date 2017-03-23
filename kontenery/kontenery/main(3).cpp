#include<iostream>
#include<string>
#include<list>
#include<vector>
#include<map>
#include<deque>
#include<set>
#include<array>
#include<chrono>

using namespace std;
using namespace chrono;

enum TYP_KONTENERA {
	ARRAY,
	VECTOR_PUSH,
	VECTOR_INSERT,
	DEQUE,
	LIST,
	SET
};

int main() {
	const int ile = 5;

	// =========================================

	list<string> lista_slow;
	string kolejne_slowo;

	cout << "Lista slow" << endl;
	cout << "Podaj kolejne slowa do wpisania do listy:" << endl;

	for (int i = 0; i < ile; ++i) {
		cout << i + 1 << ": ";
		cin >> kolejne_slowo;
		lista_slow.push_back(kolejne_slowo);
	}

	cout << "\nOto Twoje slowa:" << endl;

	list<string>::iterator iter_slowa;

	for (iter_slowa = lista_slow.begin(); iter_slowa != lista_slow.end(); ++iter_slowa)
		cout << *iter_slowa << endl;

	lista_slow.clear();

	// =========================================

	vector<double> lista_liczb;
	double kolejna_liczba;

	cout << "\nWektor liczb" << endl;
	cout << "Podaj kolejne liczby do wpisania do wektora:" << endl;

	for (int i = 0; i < ile; ++i) {
		cout << i + 1 << ": ";
		cin >> kolejna_liczba;
		lista_liczb.push_back(kolejna_liczba);
	}

	cout << "\nOto Twoje liczby:" << endl;

	for each (double var in lista_liczb)
		cout << var << endl;

	cout << "\nDrugi element tablicy:" << endl;
	const int pozycja_elementu = 1;

	try {
		cout << lista_liczb.at(pozycja_elementu) << endl;
	}
	catch (const out_of_range& exc) {
		cout << "\nPodana pozycja wykracza poza zakres liczby elementow." << endl;		// tak, wiem, ze to bez sensu przy 2-giej pozycji, ale potencjalne wyjatki sie obsluguje, a nie ignoruje ;P
	}

	vector<double>::iterator iter_liczby;
	iter_liczby = lista_liczb.begin() + pozycja_elementu;

	lista_liczb.erase(iter_liczby);
	
	cout << "\nWektor po usunieciu drugiej pozycji:" << endl;

	for each (double var in lista_liczb)
		cout << var << endl;

	lista_liczb.clear();

	// =========================================

	map<int, string> tab_asocj_stringow;
	int podaj_klucz;

	tab_asocj_stringow[1] = "jeden";
	tab_asocj_stringow[2] = "dwa";
	tab_asocj_stringow[3] = "trzy";
	tab_asocj_stringow[4] = "cztery";
	tab_asocj_stringow[5] = "piec";

	cout << "\nMapa poszukiwan" << endl;

	for (int i = 0; i < ile; ++i) {
		cout << "Podaj klucz elementu do wyswietlenia (z zakresu 1 - 5): ";
		cin >> podaj_klucz;

		try {
			cout << "Element o kluczu " << podaj_klucz << ": " << tab_asocj_stringow.at(podaj_klucz) << endl;
		}
		catch (const out_of_range& exc) {
			cout << "Klops, nie ma takiego elementu :(\nNa pocieszenie wyswietlimy element o kluczu i - tym (" << i << "): ";	// komentarz do tego absurdu jak wyzej :D

			try {
				cout << tab_asocj_stringow.at(i) << endl;
			}
			catch (const out_of_range& exc) {
				cout << "\nHehe, takiego tez nie ma ;P No to masz problem ;P" << endl;
			}
		}
	}

	tab_asocj_stringow.clear();

	// =========================================

	cout << "\nCzasy wypelniania poszczegolnych kontenerow (prosze czekac, troche to potrwa...)" << endl;

	const int horrendalna_wrecz_ilosc = 125000;
	const int zakres = 101;

	int randomowa_tablica[horrendalna_wrecz_ilosc];

	srand(static_cast<unsigned int>(time(NULL)));

	for (int i = 0; i < horrendalna_wrecz_ilosc; ++i)
		randomowa_tablica[i] = rand() % zakres;

	//~~~~~~~~~~~~~~~~~~~~~~~

	map<TYP_KONTENERA, duration<double, milli>> czasy_calkowite;

	int ile_sposobow = 0;

	//-----------------------

	vector<int> wektor_met_insert;

	auto start = steady_clock::now();

	for (int i = 0; i < horrendalna_wrecz_ilosc; ++i)
		wektor_met_insert.insert(wektor_met_insert.begin() + i, randomowa_tablica[i]);

	auto stop = steady_clock::now();

	czasy_calkowite.insert_or_assign(VECTOR_INSERT, duration<double, milli>(stop - start));

	++ile_sposobow;
	wektor_met_insert.clear();
	
	//-----------------------

	vector<int> wektor_met_push;

	start = steady_clock::now();

	for (int i = 0; i < horrendalna_wrecz_ilosc; ++i)
		wektor_met_push.push_back(randomowa_tablica[i]);

	stop = steady_clock::now();

	czasy_calkowite.insert_or_assign(VECTOR_PUSH, duration<double, milli>(stop - start));

	++ile_sposobow;
	wektor_met_push.clear();

	//-----------------------

	deque<int> tab_dynamiczna_2kier;

	start = steady_clock::now();

	for (int i = 0; i < horrendalna_wrecz_ilosc; ++i)
		tab_dynamiczna_2kier.push_back(randomowa_tablica[i]);

	stop = steady_clock::now();

	czasy_calkowite.insert_or_assign(DEQUE, duration<double, milli>(stop - start));

	++ile_sposobow;
	tab_dynamiczna_2kier.clear();

	//-----------------------

	list<int> lista;

	start = steady_clock::now();

	for (int i = 0; i < horrendalna_wrecz_ilosc; ++i)
		lista.push_back(randomowa_tablica[i]);

	stop = steady_clock::now();

	czasy_calkowite.insert_or_assign(LIST, duration<double, milli>(stop - start));

	++ile_sposobow;
	lista.clear();

	//-----------------------

	set<int> zbior;

	start = steady_clock::now();

	for (int i = 0; i < horrendalna_wrecz_ilosc; ++i)
		zbior.insert(randomowa_tablica[i]);

	stop = steady_clock::now();

	czasy_calkowite.insert_or_assign(SET, duration<double, milli>(stop - start));

	++ile_sposobow;
	zbior.clear();

	//-----------------------

	array<int, horrendalna_wrecz_ilosc> tab_staly_rozmiar;

	start = steady_clock::now();

	for (int i = 0; i < horrendalna_wrecz_ilosc; ++i)
		tab_staly_rozmiar[i] = randomowa_tablica[i];

	stop = steady_clock::now();

	czasy_calkowite.insert_or_assign(ARRAY, duration<double, milli>(stop - start));

	++ile_sposobow;

	//-----------------------

	for (int i = 0; i < ile_sposobow; ++i) {
		try {
			switch (i)
			{
			case ARRAY:
				cout << "Czas wypelniania array-a: " << czasy_calkowite.at(ARRAY).count() << " ms" << endl;
				break;
			case VECTOR_PUSH:
				cout << "Czas wypelniania wectora (metoda push()): " << czasy_calkowite.at(VECTOR_PUSH).count() << " ms" << endl;
				break;
			case VECTOR_INSERT:
				cout << "Czas wypelniania vectora (metoda insert()): " << czasy_calkowite.at(VECTOR_INSERT).count() << " ms" << endl;
				break;
			case DEQUE:
				cout << "Czas wypelniania deque-a: " << czasy_calkowite.at(DEQUE).count() << " ms" << endl;
				break;
			case LIST:
				cout << "Czas wypelniania list-a: " << czasy_calkowite.at(LIST).count() << " ms" << endl;
				break;
			case SET:
				cout << "Czas wypelniania set-a: " << czasy_calkowite.at(SET).count() << " ms" << endl;
				break;
			default:
				cout << "Nieznana struktura!" << endl;
				break;
			}
		}
		catch (const out_of_range& except) {
			cout << "Nieprzewidziane wyjscie poza zakres wektora czasow!" << endl;
		}
	}

	czasy_calkowite.clear();
	
	system("pause");
	return 0;
}