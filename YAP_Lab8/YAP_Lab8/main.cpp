#include <iostream>
#include "Stack.h"
#include<fstream>
#include <string>
#include <map>
using namespace std;
enum COMANDS
{
	ADD,
	DELETE,
	SHOW,
	CHANGE,
	FIND,
	OWNERS,
	SAVE,
	LOAD
};
int main()
{
	setlocale(0, "");
	map<string, COMANDS> getEnum = { {"ADD", ADD}, {"DELETE", DELETE}, {"SHOW", SHOW}, {"CHANGE", CHANGE}, {"FIND",FIND}, {"OWNERS", OWNERS}, {"SAVE", SAVE}, {"LOAD", LOAD} };
	cout << "Comands: ADD, DELETE, SHOW, CHANGE, FIND, OWNERS, LOAD, SAVE, EXIT" << endl;
	{
		Stack Spisok;
		while (true)
		{
			cout << "COMAND: ";
			string input;
			cin >> input;
			if (input == "EXIT")
				break;
			if (getEnum.find(input) == getEnum.end())
			{
				cout << "Incorrect comand" << endl;
				continue;
			}
			COMANDS input_enum = getEnum[input];
			int16_t  index;
			fstream file;
			string filename;
			switch (input_enum)
			{
			case ADD:
				Spisok.Add_Element(makeElement());
				Spisok.Show();
				break;
			case DELETE:
				try
				{
					cin >> index;
					Spisok.Delete_Element(index);
				}
				catch (string a)
				{
					cerr << a << endl;
				}
				Spisok.Show();
				break;
			case SHOW:
				Spisok.Show();
				break;
			case CHANGE:
				try
				{
					cin >> index;
					Spisok.Change_Element(index, makeElement());
				}
				catch (string a)
				{
					cerr << a << endl;
				}
				Spisok.Show();
				break;
			case FIND:
				cout << Spisok.Search_Element(makeElement()) << endl;
				break;
			case OWNERS:
				cin >> index;
				std::cout << "--------------" << std::endl;
				cout << Spisok.owners(index) << endl;
				std::cout << "--------------" << std::endl;
				break;
			case LOAD:
				cin >> filename;
				file.open(filename + ".txt", ios::in);//, ios::binary)
				if (file)
				{
					Spisok.Load(file);
					file.close();
					Spisok.Show();
				}
				break;
			case SAVE:
				cin >> filename;
				file.open(filename + ".txt", ios::out);
				if (file)
				{
					Spisok.Save(file);
					file.close();
					Spisok.Show();
				}
				break;
			default:
				break;
			}
		}
	}

	system("pause");
	return 0;
}