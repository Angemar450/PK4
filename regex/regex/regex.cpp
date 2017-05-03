#include<iostream>
#include<regex>
#include<chrono>
#include<fstream>

using namespace std;
using namespace chrono;

void nr_tel() {
	string nr_do_sprawdzenia;

	cout << "Prosze podac nr telefonu: ";
	getline(cin, nr_do_sprawdzenia);

	regex wzor("^((\\+|00)48)? ?(\\d{2}|\\(\\d{2}\\)) ?(\\d[ -]?){6}\\d$");

	bool czy_pasuje = regex_match(nr_do_sprawdzenia, wzor);

	if (czy_pasuje)
		cout << "Podany nr telefonu jest poprawny" << endl;
	else
		cout << "Podany nr telefonu nie jest poprawny" << endl;
}

bool sprawdzanie_regex(string email_do_sprawdzenia) {
	regex wzor(".+@.+\..+");
	return regex_match(email_do_sprawdzenia, wzor);
}

bool sprawdzanie_c(const char* email_do_sprawdzenia) {
	const char* malpa = strchr(email_do_sprawdzenia, '@');
	const char* kropka = strchr(email_do_sprawdzenia, '.');

	if (!malpa || !kropka)
		return false;

	if (malpa < kropka && kropka != malpa + 1 && email_do_sprawdzenia != malpa && email_do_sprawdzenia + strlen(email_do_sprawdzenia) - 1 != kropka)
		return true;
	else
		return false;
}

void sprawdzanie_emaila() {
	string email;

	cout << "Prosze podac email: ";
	getline(cin, email);

	bool czy_ok;

	auto start = steady_clock::now();
	czy_ok = sprawdzanie_regex(email);
	auto stop = steady_clock::now();

	duration<double, milli> czas_regex(stop - start);

	const char* email_c = email.c_str();

	start = steady_clock::now();
	czy_ok = sprawdzanie_c(email_c);
	stop = steady_clock::now();

	duration<double, milli> czas_c(stop - start);

	if (czy_ok)
		cout << "Podany email jest poprawny" << endl;
	else
		cout << "Podany email nie jest poprawny" << endl;

	cout << "Czas sprawdzania regexami: " << czas_regex.count() << " ms\nCzas sprawdzania funkcjami z C: " << czas_c.count() << " ms" << endl;
}

void analizuj_regex() {
	fstream plik;
	string nazwa("emails.txt");

	plik.open(nazwa, ios::in);

	regex wzor("([a-zA-Z0-9-._]+)@([a-zA-Z0-9]+[-.]?[a-zA-Z]+)\\.([a-zA-Z0-9]+[-]?[a-zA-Z]+)(\\.[a-zA-Z0-9]+[-]?[a-zA-Z]+)*");
	string kolejny_email;;
	smatch czesc_emaila;

	int wiersze = 0;
	int adresy_ok = 0;

	while (plik >> kolejny_email) {
		++wiersze;

		if (regex_match(kolejny_email, czesc_emaila, wzor)) {
			cout << "Caly email: " << czesc_emaila[0] << endl;
			cout << "Login: " << czesc_emaila[1] << endl;
			cout << "Domena: " << czesc_emaila[2] << endl;
			cout << "Koncowka: " << czesc_emaila[3] << czesc_emaila[4] << endl;

			++adresy_ok;
		}
		else
			cout << "Emaila " << kolejny_email << " nie da sie rozdzielic" << endl;
	}

	cout << "Wierszy: " << wiersze << endl;
	cout << "Adresow rozdzielonych poprawnie: " << adresy_ok << endl;
	
	plik.close();
}

void analizuj_string() {
	fstream plik;
	string nazwa("emails.txt");

	plik.open(nazwa, ios::in);

	string kolejny_email;;

	int wiersze = 0;
	int adresy_ok = 0;

	while (plik >> kolejny_email) {
		++wiersze;

		size_t malpa = kolejny_email.find('@', 0);
		
		if (malpa != string::npos) {
			size_t kropka = kolejny_email.find('.', malpa);
			if (kropka != string::npos)
				if(isalpha(kolejny_email[kolejny_email.length() - 1])) {
					++adresy_ok;

					cout << "Caly email: " << kolejny_email << endl;
					cout << "Login: " << kolejny_email.substr(0, malpa) << endl;
					cout << "Domena: " << kolejny_email.substr(malpa + 1, kropka - malpa) << endl;
					cout << "Koncowka: " << kolejny_email.substr(kropka + 1, kolejny_email.length() - kropka) << endl;
			}
			else
				cout << "Emaila " << kolejny_email << " nie da sie rozdzielic" << endl;
		}
		else
			cout << "Emaila " << kolejny_email << " nie da sie rozdzielic" << endl;
	}

	cout << "Wierszy: " << wiersze << endl;
	cout << "Adresow rozdzielonych poprawnie: " << adresy_ok << endl;

	plik.close();
}

int main() {
	nr_tel();
	sprawdzanie_emaila();
	analizuj_regex();
	analizuj_string();

	system("pause");
	return 0;
}