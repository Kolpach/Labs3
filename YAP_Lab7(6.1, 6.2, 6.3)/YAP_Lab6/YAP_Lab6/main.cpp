#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "TimeTable.h"
using namespace std;
enum timetable{CLASS, NEXT, VIEW, ALL};
int main()
{
	setlocale(0, "");
	cout << "Введите количество команд: ";
	int number;
	cin >> number;
	map<string, timetable> getEnum = { {"CLASS", CLASS}, {"NEXT", NEXT}, {"VIEW", VIEW}, {"ALL", ALL} };
	string comandString;
	timetable comand;

	std::map<int, std::vector<std::string>> timetable;

	for (int i = 0; i < number; ++i)
	{
		std::cin >> comandString;
		comand = getEnum[comandString];
		int day;
		string title;
		std::vector<int> must_be_deleted;
		switch (comand)
		{
		case timetable::CLASS:
			cin >> day;
			cin >> title;
			addLesson(timetable, day, title);
			break;
		case timetable::NEXT:
			must_be_deleted = nextMonth(timetable);
			if (!must_be_deleted.empty())
			{
				for (int local : must_be_deleted)
				{
					timetable.erase(local);
				}
			}
			break;
		case timetable::VIEW:
			cin >> day;
			outPut(timetable, day);
			break;
		case timetable::ALL:
			show_all(timetable);
			break;
		default:
			std::cerr << "Error!" << std::endl;
		}
	}
	system("pause");
	return 0;
}