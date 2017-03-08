#pragma once

#include<iostream>

using namespace std;

class MyException {
	int code;
	string message;

public:
	MyException();
	MyException(int, string);

	void set_code(int);
	void set_message(string);

	int get_code();
	string get_message();

	friend ostream& operator <<(ostream&, const MyException&);
};