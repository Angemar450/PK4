// Algorytmy.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include<iostream>
#include<algorithm>
#include<vector>
#include<Windows.h>
#include<time.h>
#include<chrono>

using namespace std;

void sortowanie_babelkowe(vector<int> &tab, int n)
{
	for (int i = 1; i<n; i++)
	{
		for (int j = n - 1; j >= 1; j--)
		{
			if (tab[j]<tab[j - 1])
			{
				swap(tab[j - 1], tab[j]);
			}
		}
	}
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

int main()
{
	const int stala = 10000;

	int tablica1[stala];
	for (int i = 0; i<stala; i++)
	{
		tablica1[i] = rand() % 100 + 1;
	}

	vector<int> tablica(stala);
	vector<int> tablica2(stala);
	vector<int> tablica3(stala);

	for (int i = 0; i < stala; i++) {
		tablica[i] = tablica1[i];
		tablica2[i] = tablica1[i];
		tablica2[i] = tablica1[i];
	}
	
	cout << "Sortuje teraz babelkowo. Prosze czekac!" << endl;
	auto start = chrono::steady_clock::now();
	sortowanie_babelkowe(tablica, tablica.size());
	auto stop = chrono::steady_clock::now();
	auto time = stop - start;
	cout << "Czas sortowania babelkowego: "<<chrono::duration <double, milli>(time).count() << " ms" << endl;
	
	tablica.clear();

	cout << endl << "Sortuje teraz algorytmem quicksort. Prosze czekac!" << endl;
	start = chrono::steady_clock::now();
	quicksort(tablica2, 0, tablica2.size()-1);
	stop = chrono::steady_clock::now();
	time = stop - start;;
	cout << "Czas sortowania quicksort: " << chrono::duration <double, milli>(time).count() << " ms" << endl;
	
	tablica2.clear();

	cout << endl << "Sortuje teraz funkcja sort(). Prosze czekac!" << endl;
	start = chrono::steady_clock::now();
	sort(tablica3.begin(), tablica3.end());
	stop = chrono::steady_clock::now();
	time = stop - start;;
	cout <<  "Czas sortowania funkcji sort(): " << chrono::duration <double, milli>(time).count() << " ms" << endl;
	
	tablica3.clear();

	system("pause");
    return 0;
}

