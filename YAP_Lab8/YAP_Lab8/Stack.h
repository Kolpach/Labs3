#pragma once
#include <iostream>
#include <fstream>
#include <string>
//#include <sstream>//используется для преобразования int -> string в save
#include <map>
enum formVariants { coin, banknote };
struct Element
{
	formVariants form; //m | k монеты или купюры
	uint32_t value;//Номинал
	std::string contry;//Страна
	uint16_t year;//Год
	std::string defects;//Дефекты
	std::string owner;//Владелец
	Element* previous;
	Element(formVariants, uint32_t, std::string, uint16_t, std::string, std::string);
};
class Stack
{
private:
	Element* p_back = nullptr;
	int16_t count;
	void show_one_element( Element* a, std::ostream& stream);
public:
	Stack();
	void Add_Element(Element local);
	void Delete_Element(int16_t index);
	int16_t Search_Element(Element index);
	void Show(std::ostream& stream = std::cout);
	void Change_Element(int16_t index, Element element);
	std::string owners(uint16_t year);

	void Load(std::fstream&);
	void Save(std::fstream&);
	~Stack();
};

Element makeElement(std::istream& stream = std::cin, bool showHints = true);
std::ostream& operator<<(std::ostream &out, const Element& equation);
std::ostream& operator << (std::ostream& out, const formVariants& t);