#pragma once
#include "commonUsings.h"
#include "IError.h"

class wrongSymbolError :
	virtual public IError
{
public:
	wrongSymbolError(string msg) {
		error_msg = "wrong symbol: " + msg;
	}
	virtual void print(){
		cout << error_msg << endl;
	}
};