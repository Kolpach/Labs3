#include <iostream>
#include "IError.h"
void IError::print() {
	std::cout << error_msg;
}
