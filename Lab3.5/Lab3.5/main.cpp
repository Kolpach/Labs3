#include <iostream>
#include <string>
#include <vector>
#include "commonUsings.h"
#include "notFoundError.h"
#include "wrongSymbolError.h"
void print_error_list(vector<IError*> err) {
	for (IError* a : err) {
		a->print();
	}
}
int main()
{
	vector<IError*> err;
	err.push_back(new notFoundError("5"));
	err.push_back(new wrongSymbolError("\'"));
	err.push_back(new notFoundError("-1"));
	err.push_back(new wrongSymbolError("\""));
	print_error_list(err);
	return 0;
}