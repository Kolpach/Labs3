#pragma once
#include "commonUsings.h"
#include "IError.h"

class notFoundError :
	public IError
{
public:
	notFoundError(string msg) {
		error_msg = "Could not found element: " + msg;
	};
	virtual void print() {
		cout << error_msg << endl;
	}
};