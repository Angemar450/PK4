#include<thread>
#include<iostream>
#include<windows.h>
#include<atomic>
#include<chrono>

using namespace std;
using namespace chrono;

CRITICAL_SECTION sekcja_krytyczna;

void print_thread_id(int nr) {
	cout << "Numer " << nr << " nalezy do tego watku" << endl;
}

void print_thread_id_mutex(int nr) {
	EnterCriticalSection(&sekcja_krytyczna);

	cout << "Numer " << nr << " nalezy do tego watku" << endl;

	LeaveCriticalSection(&sekcja_krytyczna);
}

void tablica_watkow() {
	int ile_watkow = thread::hardware_concurrency();

	thread* watki_tab = new thread[ile_watkow];

	cout << "Bez sekcji krytycznej:" << endl;

	for (int i = 0; i < ile_watkow; ++i) {
		try {
			watki_tab[i] = thread(print_thread_id, i);
		}
		catch (system_error& exc) {
			cout << "Nie mozna zaczac nowego watku" << endl;
		}
	}

	for (int i = 0; i < ile_watkow; ++i)
		if (watki_tab[i].joinable()) {
			try {
				watki_tab[i].join();
			}
			catch (system_error& exc) {
				cout << "Cos poszlo paskudnie nie tak" << endl;
			}
		}

	cout << "Z sekcja krytyczna:" << endl;

	for (int i = 0; i < ile_watkow; ++i) {
		try {
			watki_tab[i] = thread(print_thread_id_mutex, i);
		}
		catch (system_error& exc) {
			cout << "Nie mozna zaczac nowego watku" << endl;
		}
	}

	for (int i = 0; i < ile_watkow; ++i)
		if (watki_tab[i].joinable()) {
			try {
				watki_tab[i].join();
			}
			catch (system_error& exc) {
				cout << "Cos poszlo paskudnie nie tak" << endl;
			}
		}

	delete[] watki_tab;
}

void inc(unsigned long& argument1, int argument2) {
	for (int i = 0; i < argument2; ++i)
		++argument1;
}

void inc_ato(atomic<unsigned long>& argument1, int argument2) {
	for (int i = 0; i < argument2; ++i)
		++argument1;
}

void typy_atomowe() {
	int partial = 2000000;
	unsigned long zmienna_zwykla = 0;
	atomic<unsigned long> zmienna_atomowa(0);

	int ile_watkow = thread::hardware_concurrency();

	thread* watki_tab = new thread[ile_watkow];

	for (int i = 0; i < ile_watkow; ++i) {
		try {
			watki_tab[i] = thread(inc, ref(zmienna_zwykla), partial);
		}
		catch (system_error& exc) {
			cout << "Nie mozna zaczac nowego watku" << endl;
		}
	}

	for (int i = 0; i < ile_watkow; ++i)
		if (watki_tab[i].joinable()) {
			try {
				watki_tab[i].join();
			}
			catch (system_error& exc) {
				cout << "Cos poszlo paskudnie nie tak" << endl;
			}
		}

	for (int i = 0; i < ile_watkow; ++i) {
		try {
			watki_tab[i] = thread(inc_ato, ref(zmienna_atomowa), partial);
		}
		catch (system_error& exc) {
			cout << "Nie mozna zaczac nowego watku" << endl;
		}
	}

	for (int i = 0; i < ile_watkow; ++i)
		if (watki_tab[i].joinable()) {
			try {
				watki_tab[i].join();
			}
			catch (system_error& exc) {
				cout << "Cos poszlo paskudnie nie tak" << endl;
			}
		}

	delete[] watki_tab;

	cout << "Wartosc zmiennej zmienna_zwykla: " << zmienna_zwykla << endl;
	cout << "Wartosc zmiennej zmienna_atomowa: " << zmienna_atomowa << endl;
}

void wypelnij(char* co, char czym, int odkad, int dokad) {
	for (int i = odkad; i < dokad; ++i)
		co[i] = czym;
}

void znowu_pomiar_czasu_ile_mozna() {
	int ile_watkow = thread::hardware_concurrency();
	int mnoznik = 2000000;

	int rozmiar = ile_watkow * mnoznik;
	char czym_wypelniamy1 = 'M';
	char czym_wypleniamy2 = 'K';

	char* zmienne_1bajtowe = new char[rozmiar];

	thread* watki_tab = new thread[ile_watkow];

	// =============================

	auto start = steady_clock::now();

	for (int i = 0; i < ile_watkow; ++i) {
		try {
			watki_tab[i] = thread(wypelnij, zmienne_1bajtowe, czym_wypelniamy1, i * mnoznik, (i + 1) * mnoznik);
		}
		catch (system_error& exc) {
			cout << "Nie mozna zaczac nowego watku" << endl;
		}
	}

	auto stop = steady_clock::now();

	cout << "Czas wypelniania na wielu watkach: " << duration<double, milli>(stop - start).count() << " ms" << endl;

	for (int i = 0; i < ile_watkow; ++i)
		if (watki_tab[i].joinable()) {
			try {
				watki_tab[i].join();
			}
			catch (system_error& exc) {
				cout << "Cos poszlo paskudnie nie tak" << endl;
			}
		}

	// =============================

	start = steady_clock::now();

	for (int i = 0; i < ile_watkow * mnoznik; ++i)
		zmienne_1bajtowe[i] = czym_wypleniamy2;

	stop = steady_clock::now();

	cout << "Czas wypelniania na jednym watku: " << duration<double, milli>(stop - start).count() << " ms" << endl;

	delete[] zmienne_1bajtowe;
	delete[] watki_tab;
}

int main() {
	InitializeCriticalSection(&sekcja_krytyczna);

	// zad. 1.
	tablica_watkow();

	// zad. 2.
	typy_atomowe();

	// zad. 3
	znowu_pomiar_czasu_ile_mozna();

	system("pause");
	return 0;
}