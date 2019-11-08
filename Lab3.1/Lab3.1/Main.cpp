#include <iostream>
#include <vector>
#include <string>
#include <map>
using std::cout;
using std::vector;
using std::cin;
using std::string;
enum formVariants { coin, banknote };
struct Element
{
	formVariants form; //m | k монеты или купюры
	uint32_t value;//Номинал
	std::string contry;//Страна
	uint16_t year;//Год
	std::string defects;//Дефекты
	std::string owner;//Владелец
};

std::ostream& operator << (std::ostream& out, const formVariants& t)
{
	switch (t) {
	case formVariants::coin: return (out << "coin");
	case formVariants::banknote: return (out << "banknote");
	}
	return (out);
}

std::ostream& operator<<(std::ostream& out, const Element& equation)
{
	out << equation.form << ' ' << equation.value << ' ' << equation.contry << ' ' << equation.year << ' ' << equation.defects << ' ' << equation.owner << std::endl;
	return out;
}

std::istream& operator >> (std::istream& stream, Element& equation)
{
	std::map<std::string, formVariants> getForm = { {"coin", formVariants::coin}, {"banknote", formVariants::banknote} };
	std::string form;
	uint32_t value;
	std::string contry;
	uint16_t year;
	std::string defects;
	std::string owner;

	stream >> form;
	if (getForm.find(form) == getForm.end())
		throw 1;
	equation.form = getForm[form];
	
	stream >> equation.value;
	stream >> equation.contry;
	stream >> equation.year;
	stream >> equation.defects;
	stream >> equation.owner;

	return stream;
}

std::istream& operator >> (std::istream& stream, vector<Element>& list)
{
	Element newOne;
	while (1)
	{
		std::cout << "Введите в коректной форме:\nФорму выпуска (coin|banknote).\nНоминал, Страну, год. \nДефекты, владелец.\n";
		try
		{
			stream >> newOne;
			break;
		}
		catch (...)
		{
			stream.ignore(256, '\n');
		}
	}
	list.push_back(newOne);
	return stream;
}
std::ostream& operator << (std::ostream& out, vector<Element>& list)
{
	std::cout << "--------------" << std::endl;
	for (Element a : list)
	{
		out << a;
	}
	std::cout << "--------------" << std::endl;
	return out;
}

enum COMANDS
{
	ADD,
	SHOW
};

int main()
{
	setlocale(0, "");
	string a;
	std::map<string, COMANDS> getEnum = { {"ADD", ADD}, {"SHOW", SHOW} };
	vector<Element> list;
	
	while (1)
	{
		cout << "Comands: ADD, SHOW, EXIT" << std::endl;;
		cin >> a;
		if (a == "EXIT")
			break;
		switch (getEnum[a])
		{
		case ADD:
			cin >> list;
			break;
		case SHOW:

			cout << list;
			break;
		default:
			break;
		}
	}
	return 0;
}