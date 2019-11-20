#include <iostream>
#include <string>
#include <map>
#include "Spisok.h"
using namespace std;
enum COMANDS
{
	ADD,
	DELETE,
	SHOW,
	MAX
};
int main()
{
	map<string, COMANDS> getEnum = { {"ADD", ADD}, {"DELETE", DELETE}, {"SHOW", SHOW}, {"MAX", MAX} };
	cout << "Comands: ADD, DELETE, SHOW, MAX, EXIT" << endl;
	{
		Spisok Spisok;
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
			int16_t number;
			switch (input_enum)
			{
			case ADD:
				cin >> number;
				Spisok.push_back(number);
				Spisok.show();
				break;
			case DELETE:
				try
				{
					cin >> number;
					Spisok.delete_element(number);
				}
				catch (string a)
				{
					cerr << a << endl;
				}
				catch (...)
				{
					cerr << "Something went wrong" << endl;
				}
				Spisok.show();
				break;
			case SHOW:
				Spisok.show();
				break;
			case MAX:
				cout << "Max element is: " << Spisok.findMax() << endl;
				std::cout << "---------------" << std::endl;
				Spisok.show();
				break;
			default:
				break;
			}
		}
	}
	
	system("pause");
	return 0;
}