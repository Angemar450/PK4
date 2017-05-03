#include <iostream>
#include <regex>
#include <chrono>
#include <stdlib.h>
#include <fstream>



using namespace std;

bool phone_valid(string phone) {
	regex regex("^((\\+|00)48)? ?(\\d{2}|\\(\\d{2}\\)) ?(\\d[ -]?){6}\\d$");
	return regex_match(phone, regex);
}

void zadanie1() {
	string phone;
	cout << "Podaj numer telefonu; ";
	getline(cin, phone);

	bool valid = phone_valid(phone);
	cout << "Numer \"" << phone << " \" jest ";
	cout << (valid ? "poprawnym" : "niepoprawnym");
	cout << " numerem telefonu." << endl;
}

bool email_valid_regex(string email) {
	regex regex(".*@.*\\..*");
	return regex_match(email, regex);
}

bool email_valid_strchr(string email) { 
	char* char_at = strchr (email.c_str, '@');
	char* char_dot = strchr(email.c_str, '.');
	size_t email_len = strlen(email.c_str());

	return (
		char_at != nullptr && char_dot != nullptr &&
		char_at < char_dot - 1 &&
		char_at != email.c_str() &&
		char_dot != email.c_str + email_len - 1
		);
}

void zadanie2() {
	string email;
	cout << "Podaj adres email: ";
	cin >> email;

	auto regex_start = chrono::steady_clock::now();
	email_valid_regex(email);
	auto regex_end = chrono::steady_clock::now();
	cout << "regex: \t" << chrono::duration<double, milli>(regex_end - regex_start).count() << " ms" << endl;
	
	auto strchr_start = chrono::steady_clock::now();
	email_valid_strchr(email);
	auto strchr_end = chrono::steady_clock::now();
	cout << "strchr:\t" << chrono::duration<double, milli>(strchr_end - strchr_start).count() << " ms" << endl;

}


int main() {

	ifstream file;
	file.open("emails.txt");
	string line;
	int i = 0; //ilosc wierszy
	int w = 0; //ilosc regexow
	//0-email 1-nick 2-domain 3-end

	regex pieces_regex("^([a-z0-9-._]*)@([a-z]*).([a-z.-]*)");
	smatch pieces_match;

	if (file.is_open()) {
		string line;

		while (getline(file, line)) {
			line = line.substr(0, line.length() - 1);
			if (regex_match(line, pieces_match, pieces_regex)) {
				string email = pieces_match[0];
				string nick = pieces_match[1];
				string domain = pieces_match[2];
				string end = pieces_match[3];
				cout << "email: " << email << endl;
				cout << "\tnick: " << nick << endl;
				cout << "\tdomain: " << domain << endl;
				cout << "\tend: " << end << endl;

				w++;
			}
			else {
				cout << "brak wynikow dla: " << line << endl;
			}
			cout << endl << "--------------\n";
			i++;
		}
		cout << endl;
		cout << "Ilosc elementow w pliku: " <<i << endl;
		cout << "Ilosc elementow poprawnie przeanalizowanych: " << w << endl;

	}



	system("pause");

	return 0;
}