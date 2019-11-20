#pragma once
#include <vector>
#include <map>
void nextYear();
std::vector<int> nextMonth(std::map<int, std::vector<std::string>> &timetable);
void addLesson(std::map<int, std::vector<std::string>> &timetable, int day, std::string title);
void outPut(std::map<int, std::vector<std::string>> &timetable, int day);
void show_all(std::map<int, std::vector<std::string>> &timetable);