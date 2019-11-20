#include "Stack.h"

Stack::Stack()
{
}

void Stack::Add_Element(Element local)
{
	Element* dynamic = new Element(local);
	++count;
	dynamic->previous = p_back;
	p_back = dynamic;
	dynamic = nullptr;
}
void Stack::Delete_Element(int16_t index)
{
	if (index < count && index >= 0)
	{
		//--index;//Если список индексируется с 1
		Element *Previous = nullptr;
		Element *Current = p_back;
		Element *Next = nullptr;
		for (int i = 0; i < count - index - 1; ++i)//Ищем индекс с конца
		{
			Next = Current;
			Current = Current->previous;
		}
		if (Next != nullptr)
		{
			if (Current->previous != nullptr)
				Previous = Current->previous;
			Next->previous = Previous;//Связываем два элемента рядом с заданным
		}
		if (p_back == Current)
			p_back = Current->previous;
		Current->previous = nullptr;
		delete Current;
		--count;
	}
	else
		throw static_cast<std::string>("Index out of range");
}
int16_t Stack::Search_Element(Element equation)
{
	int16_t index = count-1;
	for (Element *local_el = p_back; local_el != nullptr; local_el = local_el->previous, --index)
	{
		if (equation.contry == local_el->contry && equation.defects == local_el->defects && equation.form == local_el->form && equation.owner == local_el->owner && equation.value == local_el->value && equation.year == local_el->year)
		{
			return index;
		}
	}
	return -1;
}
void Stack::Show(std::ostream& stream)
{
	std::cout << "--------------";
	show_one_element(p_back, stream);
	std::cout << std::endl << "--------------" << std::endl;
}
void Stack::show_one_element(Element* a, std::ostream& stream)//Рекурсивно показывает все элементы стека. Нужно, так как пользователь видит элементы в порядке их погружения, а стек в обратном этому.
{
	if (a != nullptr)
	{
		show_one_element(a->previous, stream);
		stream << std::endl;
		stream << *a;
	}
}
void Stack::Change_Element(int16_t index, Element element)
{
	if (index < count && index >= 0)
	{
		Element *Current = p_back;
		for (int i = 0; i < count - index - 1; ++i)//Ищем индекс с конца
			Current = Current->previous;
		Current->contry = element.contry;
		Current->defects = element.defects;
		Current->form = element.form;
		Current->owner = element.owner;
		Current->value = element.value;
		Current->year = element.year;
	}
	else
		throw static_cast<std::string>("Index out of range");
}
std::string Stack::owners(uint16_t year)
{
	//идём по стеку с конца, и возвращаем имена владельцев денег, выпущенных до определённого года
	//int16_t index = count - 1;
	std::string finalString = "";
	for (Element *local_el = p_back; local_el != nullptr; local_el = local_el->previous)//, --index)
	{
		if ( local_el->year < year)
		{
			finalString += local_el->owner + '\n';
		}
	}
	finalString[finalString.size() - 1] = ' ';//Удаляем последний \n
	return finalString;
}

void Stack::Load(std::fstream& inputStream)
{
	// Мы дублируем ниже код для деструктора ~stack() потомучто мы хотим очистить список от Element-ов, а для Element не предусмотрен деструктор.
	Element *Current = p_back; //очищаем весь список
	Element *Next = nullptr;
	for (int i = 0; i < count; ++i)//Ищем индекс с конца
	{
		Next = Current;
		Current = Current->previous;
		delete Next;
	}

	count = 0;
	p_back = nullptr;
	
	//Добавляем элементы со значениями из списка
	while (!inputStream.eof())
	{
		Add_Element(makeElement(inputStream, false));
	}
}
void Stack::Save(std::fstream& outputStream)
{
	show_one_element(p_back, outputStream);
}


Stack::~Stack()
{
	Element *Current = p_back;
	Element *Next = nullptr;
	for (int i = 0; i < count; ++i)//Ищем индекс с конца
	{
		Next = Current;
		Current = Current->previous;
		delete Next;
	}
}

Element::Element(formVariants a, uint32_t b, std::string c, uint16_t d, std::string e, std::string f)
{
	form = a;
	value = b;
	contry = c;
	year = d;
	defects = e;
	owner = f;
}

std::ostream& operator<<(std::ostream &out, const Element& equation)
{
	out << equation.form << ' ' << equation.value << ' ' << equation.contry << ' ' << equation.year << ' ' << equation.defects << ' ' << equation.owner;
	return out;
}

std::ostream& operator << (std::ostream& out, const formVariants& t)
{
	switch (t) {
	case formVariants::coin: return (out << "coin");
	case formVariants::banknote: return (out << "banknote");
	}
	return (out);
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

	stream >> value;
	if (value < 0)
		throw 1;

	stream >> contry;
	stream >> year;
	if (year < 0)
		throw 1;
	stream >> defects;
	stream >> owner;

	equation.form = getForm[form];
	equation.value = value;
	equation.contry = contry;
	equation.year = year;
	equation.defects = defects;
	equation.owner = owner;

	return stream;
}

Element makeElement(std::istream& stream, bool showHints)
{
	Element newOne(formVariants::banknote, 0, " ", 0, " ", " ");//Так как доп задание - перегрузить оператор ввода
	while (1)
	{
		if(showHints)
			std::cout << "Введите в коректной форме:\nФорму выпуска (coin|banknote).\nНоминал, Страну, год. \nДефекты, владелец.\n";
		try
		{
			stream >> newOne;
			break;
		}
		catch(...)
		{
			stream.ignore(256, '\n');
		}
	}
	return newOne;
}