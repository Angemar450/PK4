#include"MyException.h"

MyException::MyException(): code(0), message("Niespodziewany blad") {}
MyException::MyException(int code_to_set, string msg_to_set): code(code_to_set), message(msg_to_set) {}

void MyException::set_code(int code_to_set) {
	code = code_to_set;
}
void MyException::set_message(string msg_to_set) {
	message = msg_to_set;
}

int MyException::get_code() {
	return code;
}
string MyException::get_message() {
	return message;
}

ostream& operator <<(ostream& stream, const MyException& exc) {
	stream << exc.message.c_str();
	return stream;
}