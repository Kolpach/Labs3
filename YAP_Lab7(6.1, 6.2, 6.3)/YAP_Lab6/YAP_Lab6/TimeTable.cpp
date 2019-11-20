#pragma once
#include <iostream>
#include <string>
#include "TimeTable.h"

std::vector<int> month = { 31,28,31,30,31,30,31,31,30,31,30,31 };
int current_Month = 0;
int year = 2019;
void nextYear()
{
	year++;
	if (year % 4 == 0)
		month[1] = 29;
	else
		month[1] = 28;
}
std::vector<int> nextMonth(std::map<int, std::vector<std::string>> &timetable)
{
	std::vector<int> have_to_be_deleted;
	current_Month = current_Month == 11 ? -1 : current_Month;
	if (current_Month == 11)
	{
		current_Month = -1;
		nextYear();
	}

	int current_count_of_days = month[++current_Month];

	for (std::pair<int, std::vector<std::string>> a : timetable)
	{
		if (current_count_of_days < a.first)//Если в текущем месяце нет таких дней
		{
			for (std::string stroke : a.second)//Склеиваем два вектора
			{
				timetable[current_count_of_days - 1].push_back(stroke);
			}
			have_to_be_deleted.push_back(a.first);
		}
	}
	return have_to_be_deleted;
}
void addLesson(std::map<int, std::vector<std::string>> &timetable, int day, std::string title)
{
	if (day > 0 && day <= month[current_Month])
	{
		bool flag = 1;
		for (std::string lesson : timetable[day])
		{
			if (lesson == title)
				flag = 0;
		}
		if (flag)
		{
			timetable[day].push_back(title);
		}
	}
	else
		std::cerr << "Нет такого числа в этом месяце. Доступны числа от 1 до " << month[current_Month]<<std::endl;
}
void outPut(std::map<int, std::vector<std::string>> &timetable, int day)
{
	if (day > 0 && day <= month[current_Month])
	{
		if (timetable[day].size() != 0)
		{
			std::cout << "In " << day << " day " << timetable[day].size() << " classes  in university : ";
			for (std::string a : timetable[day])
				std::cout << a << ' ';
			std::cout << std::endl;
		}
		else
			std::cout << "In " << day << " day We are free!" << std::endl;
	}
	else
		std::cerr << "Нет такого числа в этом месяце. Доступны числа от 1 до " << month[current_Month] << std::endl;
}
void show_all(std::map<int, std::vector<std::string>> &timetable)
{
	for (std::pair<int, std::vector<std::string>> a : timetable)
	{
		std::cout << "In " << a.first << " day " << timetable[a.first].size() << " classes  in university : ";
		for (std::string b : a.second)
			std::cout << b;
		std::cout << std::endl;
	}
}