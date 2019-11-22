#pragma once
class IError
{
protected:
	std::string error_msg;
public:
	virtual void print() = 0;
	
};

class curruptedError :
	public IError
{
public:
	curruptedError(std::string msg) {
		error_msg = "Min or Max reached: " + msg;
	}
	virtual void print() {
		std::cout << error_msg << std::endl;
	}
};

class zeroDivizionError :
	public IError
{
public:
	zeroDivizionError(std::string msg) {
		error_msg = "zero division in " + msg;
	}
	virtual void print() {
		std::cout << error_msg << std::endl;
	}
};