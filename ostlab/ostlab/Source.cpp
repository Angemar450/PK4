#include <iostream>
#include <regex>
#include <chrono>
#include <stdlib.h>


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


}
int main() {






	system("pause");

	return 0;
}