#include"CustomException.h"

const char* CustomException::what() const throw () {
	return "Moj customowy wyjatek!";
}