#include"Dzielenie.h"
#include"CustomException.h"
#include"MyException.h"

double Dzielenie::dziel_ce(int a, int b) {
	if (b == 0) {
		CustomException wystapil_blad;
		throw wystapil_blad;
	}
	else
		return a / b;
}

double Dzielenie::dziel_ei(int a, int b) {
	if (b == 0) {
		int blad = 1;
		throw blad;
	}
	else
		return a / b;
}

double Dzielenie::dziel_me(int a, int b) {
	if (b == 0) {
		string tresc_bledu("Nie mozna dzielic przez 0!");
		MyException wystapil_blad(1, tresc_bledu);

		throw wystapil_blad;
	}
	else
		return a / b;
}