#include <iostream>
#include <string>
#include <vector>
#include<cmath>
#include<ctime>
#include<map>
#include<iomanip>
#include<sstream>
#include"IError.h"
#include "Date.h"

std::vector<IError*> err;

void DT::Date::plusYear(int32_t deltaTime)
{
	currupted = false;
	if (year + deltaTime > 9999) {
		year = 9999;
		month = DT::Months::December;
		day = 31;
		hour = 23;
		minute = 59;
		second = 59;
		currupted = true;
		err.push_back(new curruptedError("max"));
	}
	else
		if (year + deltaTime < 1) {
			year = 1;
			month = DT::Months::January;
			day = 1;
			hour = 0;
			minute = 0;
			second = 0;
			IError* pointer = new curruptedError("min");
			err.push_back(pointer);
			currupted = true;
		}
		else
			year += deltaTime;


	if (year % 4 == 0)
		vesocosn = true;
	if (year % 100 == 0)
		vesocosn = false;
	if (year % 400 == 0)
		vesocosn = true;

	if (vesocosn)
		daysInMonth[1] = 29;
	else
		daysInMonth[1] = 28;
}

void DT::Date::plusMonth(int32_t deltaMonth)
{
	currupted = false;
	int32_t localDelta = deltaMonth;
	while (static_cast<int32_t>(month) - 1 + localDelta > 11 || static_cast<int32_t>(month) - 1 + localDelta < 0) {//мы увеличиваем(уменьшаем) год при нужных услови€х, уменьша€ разность на 12, если услови€ всЄ ещЄ подход€щие повтор€ем
		plusYear(localDelta / abs(localDelta));
		localDelta -= 12 * localDelta / abs(localDelta);//¬ычитание из модул€ числа
		if (localDelta == 0)
			throw new zeroDivizionError("plusMonth()");
		if (localDelta != 0 && localDelta / abs(localDelta) != deltaMonth / abs(deltaMonth))//выполн€етс€ если от нужной дельты ничего не осталось пример: d = 2 -> d= -10 нужно завершить
			break;//deltaMonth !=0
	}
	if (!currupted)
		month = static_cast<DT::Months>((static_cast<int32_t>(month) + 11 + (deltaMonth % 12)) % 12 + 1);
}

void DT::Date::plusDay(int32_t deltaDay)
{
	currupted = false;
	while (day + deltaDay > daysInMonth[static_cast<int32_t>(month) - 1]) {//ѕо сути алгоритм такой же как и в addMonth но тут он разбит на два цикла так как дней не всегда 31
		deltaDay = deltaDay - daysInMonth[static_cast<int32_t>(month) - 1];
		plusMonth(1);
	}
	while (day + deltaDay < (-1 * daysInMonth[(static_cast<int32_t>(month) + 10) % 12])) {// (days - 2 + 12) %12
		deltaDay = deltaDay + daysInMonth[(static_cast<int32_t>(month) + 10) % 12];
		plusMonth(-1);
	}
	if (!currupted) {
		day += deltaDay;
		if (day <= 0) {
			plusMonth(-1);
			if (!currupted)
				day += daysInMonth[static_cast<int32_t>(month) - 1];
		}
	}
}

void DT::Date::plusHour(int32_t deltaHour)
{
	currupted = false;
	int32_t localDelta = deltaHour;
	while (hour + localDelta > 23 || hour + localDelta < 0) {
		plusDay(localDelta / abs(localDelta));
		localDelta -= 24 * localDelta / abs(localDelta);//¬ычитание из модул€ числа 
		if (localDelta == 0)
			throw new zeroDivizionError("plusHour()");
		if (localDelta != 0 && localDelta / abs(localDelta) != deltaHour / abs(deltaHour))//выполн€етс€ если от нужной дельты ничего не осталось пример: d = 2 -> d= -22 нужно завершить
			break;//deltaHour >0 или <0
	}
	if (!currupted)
		hour = (hour + 24 + (deltaHour % 24)) % 24;
}

void DT::Date::plusMinute(int32_t deltaMinutes)
{
	currupted = false;
	int32_t localDelta = deltaMinutes;
	while (minute + localDelta > 59 || minute + localDelta < 0) {
		plusHour(localDelta / abs(localDelta));
		localDelta -= 60 * localDelta / abs(localDelta);//¬ычитание из модул€ числа 
		if (localDelta == 0)
			throw new zeroDivizionError("plusMinute()");
		if (localDelta != 0 && localDelta / abs(localDelta) != deltaMinutes / abs(deltaMinutes))//выполн€етс€ если от нужной дельты ничего не осталось пример: d = 2 -> d= -22 нужно завершить
			break;//deltaHour >0 или <0
	}
	if (!currupted)
		minute = (minute + 60 + (deltaMinutes % 60)) % 60;
}

void DT::Date::plusSecond(int32_t deltaSeconds)
{
	currupted = false;
	int32_t localDelta = deltaSeconds;
	while (second + localDelta > 59 || second + localDelta < 0) {
		plusMinute(localDelta / abs(localDelta));
		localDelta -= 60 * localDelta / abs(localDelta);//¬ычитание из модул€ числа 
		if (localDelta == 0)
			throw new zeroDivizionError("plusSecond()");
		if (localDelta != 0 && localDelta / abs(localDelta) != deltaSeconds / abs(deltaSeconds))//выполн€етс€ если от нужной дельты ничего не осталось пример: d = 2 -> d= -22 нужно завершить
			break;//deltaHour >0 или <0
	}
	if (!currupted)
		second = (second + 60 + (deltaSeconds % 60)) % 60;
}

DT::Date::Date(int32_t a, Months b, int32_t c, int32_t d, int32_t e, int32_t f)
{
	plusSecond(f);
	plusMinute(e);
	plusHour(d);
	plusDay(c - 1);
	plusMonth(b - 1);
	plusYear(a - 1);
}

DT::Date::Date(int32_t a, Months b, int32_t c) 
{
	plusDay(c - 1);
	plusMonth(b - 1);
	plusYear(a - 1);
}

DT::Date::Date(int32_t a, int32_t b, int32_t c) 
{
	plusSecond(c);
	plusMinute(b);
	plusHour(a);
}

DT::Date::Date(const Date& a)
{
	vesocosn = a.vesocosn;
	currupted = a.currupted;
	year = a.year;
	month = a.month;
	day = a.day;
	hour = a.hour;
	minute = a.minute;
	second = a.second;
}

DT::Date::Date()
{
	time_t now = time(0);
	tm a;
	localtime_s(&a, &now);

	vesocosn = false;
	currupted = false;
	plusSecond(a.tm_sec);
	plusMinute(a.tm_min );
	plusHour(a.tm_hour);
	plusDay(a.tm_mday - 1);
	plusMonth(a.tm_mon);
	plusYear(a.tm_year + 1900 - 1);
}

uint32_t DT::Date::getYear()
{
	return year;
}

DT::Months DT::Date::getMonth()
{
	return month;
}

int32_t DT::Date::getDay()
{
	return day;
}

int32_t DT::Date::getHour()
{
	return hour;
}

int32_t DT::Date::getMinute()
{
	return minute;
}

int32_t DT::Date::getSecond()
{
	return second;
}

DT::Date DT::Date::addYear(int32_t deltaTime)
{
	Date localData(*this);
	localData.plusYear(deltaTime);
	return localData;
}

DT::Date DT::Date::addMonth(int32_t deltaMonth)
{
	Date localData(*this);
	localData.plusMonth(deltaMonth);
	return localData;
}

DT::Date DT::Date::addDay(int32_t deltaDay)
{
	Date localData(*this);
	localData.plusDay(deltaDay);
	return localData;
}

DT::Date DT::Date::addHour(int32_t deltaHour)
{
	Date localData(*this);
	localData.plusHour(deltaHour);
	return localData;
}

DT::Date DT::Date::addMinute(int32_t deltaMinutes)
{
	Date localData(*this);
	localData.plusMinute(deltaMinutes);
	return localData;
}

DT::Date DT::Date::addSecond(int32_t deltaSeconds)
{
	Date localData(*this);
	localData.plusSecond(deltaSeconds);
	return localData;
}

std::string DT::Date::toString()
{
	std::stringstream s;
	s << *this;
	std::string out;
	std::getline(s, out);
	return out;
}

DT::Date::~Date()
{
}

std::ostream& operator<<(std::ostream& stream, DT::Months month)
{
	std::map<DT::Months, std::string> dict = { {DT::January, "January" }, {DT::February, "February" }, {DT::March, "March" }, {DT::April, "April" }, {DT::May, "May" }, {DT::June, "June" }, {DT::July, "July" }, {DT::Augest, "Augest" }, {DT::September, "September" }, {DT::October, "October" }, {DT::November, "November" }, {DT::December, "December" } };
	return stream << dict[month];
}

std::ostream& operator<<(std::ostream& stream, DT::Date object)
{
	stream << object.getYear() << '-' << object.getMonth() << '-';
	stream << std::setw(2) << std::setfill('0') << object.getDay();
	stream << ' ' << std::setw(2) << std::setfill('0') << object.getHour() << ':' << std::setw(2) << std::setfill('0') << object.getMinute() << ':' << std::setw(2) << std::setfill('0') << object.getSecond();
	return stream;
}

