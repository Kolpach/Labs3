#include <iostream>
#include <string>
#include <vector>
#include"IError.h"
#include "Date.h"

extern std::vector<IError*> err;

void print_error_list(std::vector<IError*> err) {
	for (IError* a : err) {
		a->print();
	}
}
int main()
{
	DT::Date a(1, static_cast<DT::Months>(1), 1, -45, 30, 30);
	DT::Date c;
	DT::Date c2;
	std::cout << a << std::endl;
	int32_t x = 120;
	try {
		std::cout << a.addSecond(x) << std::endl;
	}
	catch (zeroDivizionError* error) {
		err.push_back(error);
		DT::Date local = a.addSecond(x + 1);
		std::cout << local.addSecond(-1) << std::endl;
	}
	std::cout << c << std::endl;
	c2 = c.addYear(5);
	c2 = c2.addMonth(10);
	c2 = c2.addDay(-15);
	std::cout << c2.toString() << std::endl;

	print_error_list(err);
	/*vector<IError*> err;
	err.push_back(new notFoundError("5"));
	err.push_back(new wrongSymbolError("\'"));
	err.push_back(new notFoundError("-1"));
	err.push_back(new wrongSymbolError("\""));
	print_error_list(err);*/
	for (IError* a : err) {
		delete a;
	}
	return 0;
}