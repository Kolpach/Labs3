#pragma once
#include <iostream>
//¬ программе существует класс Elements, который хранит значение одного элемента, а так же указатели на другие
// ласс Spisok представл€ет собой упрощЄнную версию Elements, котора€ не хранит значени€, а просто динамически выдел€ет и освобождает пам€ть дл€ других
//ѕочему так: »з списка можно удалить любой элемент, а если удалить все, то добавление новых станет невозможно(–ешено классом Spisok)
//  элементам списка мы получаем доступ через указатели p_begin и p_back, так же помогает переменна€ count
 class Elements
{
private:
	 int32_t one_element_of_list;
	 Elements *p_next = nullptr, *p_previous = nullptr;
	 static Elements *p_begin, *p_back;
	 static size_t count;
	 
	 Elements(int32_t);

	 void add_link(Elements* next, Elements* previous);
	 Elements* find_element(int16_t index);
public:
	Elements();//ѕо идее не нужен, но его требует Spisok
	void push_back(int32_t elem);
	void delete_element(int16_t index);
	int32_t findMax();
	void show();
	~Elements();
protected:
	void delete_all();
};
class Spisok : public Elements
{
public:
	Spisok();//ѕо идее ничего не должен создавать, но перегрузка конструктора не работает, он создаЄт Element, который ничего не хранит
	~Spisok();
};