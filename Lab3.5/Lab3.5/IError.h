#pragma once
#include "commonUsings.h"
class IError
{
protected:
	string error_msg;
public:
	virtual void print() = 0;
};
void IError::print() {
	cout << error_msg;
}