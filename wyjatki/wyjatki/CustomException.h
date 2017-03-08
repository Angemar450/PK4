#pragma once

#include<iostream>

using namespace std;

class CustomException : public exception {
	const char* what() const throw (string);

};