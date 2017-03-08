#include<iostream>
#include"Dzielenie.h"
#include"CustomException.h"
#include"MyException.h"

using namespace std;

int main() {
	Dzielenie obiekt_dzielacy;

	try {
		obiekt_dzielacy.dziel_ce(2, 0);
	}
	catch (exception &blad) {
		cout << blad.what() << endl;;
	}

	// ------------------

	try {
		obiekt_dzielacy.dziel_me(2, 0);
	}
	catch (MyException obsluz_wiadomosc) {
		cout << obsluz_wiadomosc << endl;
	}
	catch (int obsluz_kod) {
		cout << "Wystapil blad o kodzie: " << obsluz_kod << "!" << endl;
	}

	// ------------------

	try {
		obiekt_dzielacy.dziel_ei(2, 0);
	}
	catch (MyException obsluz_my_exc) {
		cout << obsluz_my_exc << endl;
	}
	catch (int blad_intowy) {
		cout << "Wystapil blad o kodzie: " << blad_intowy << endl;
	}

	// ------------------

	try {
		obiekt_dzielacy.dziel_me(2, 0);
	}
	catch (MyException obsluz_my_exception) {
		switch (obsluz_my_exception.get_code())
		{
		case 1:
			cout << "Nie dziel przez 0!" << endl;
			break;

		default:
			cout << "Inny kod bledu, ale i tak przez 0 nie wolno dzielic" << endl;
			break;
		}
	}
	catch (int blad_int) {
		cout << "Wystapil blad o kodzie: " << blad_int << "." << endl;
	}

	// ------------------

	try {
		try {
			obiekt_dzielacy.dziel_me(2, 0);
		}
		catch (int blad_typu_int) {
			cout << "Wystapil blad o kodzie: " << blad_typu_int << "." << endl;
		}
		catch (...) {
			throw;
		}
	}
	catch (MyException chwyc_to) {
		cout << chwyc_to << endl;
	}

	system("pause");
	return 0;
}