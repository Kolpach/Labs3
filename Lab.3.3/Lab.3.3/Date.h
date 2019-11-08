#pragma once
#include<iostream>
#include<cmath>
#include<ctime>
#include<map>
#include<iomanip>
#include<sstream>
namespace DT {
	enum Months { January = 1, February = 2, March, April, May, June, July, Augest, September, October, November, December };
	class Date
	{
	private:
		bool currupted = false;
		bool vesocosn = false;
		int32_t year = 1;
		Months month = January;
		int32_t day = 1;
		int32_t hour = 0;
		int32_t minute = 0;
		int32_t second = 0;
		int16_t daysInMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		void plusYear(int32_t deltaTime);
		void plusMonth(int32_t deltaMonth);
		void plusDay(int32_t deltaDay);
		void plusHour(int32_t deltaHour);
		void plusMinute(int32_t deltaMinute);
		void plusSecond(int32_t deltaSecond);
	public:
		Date(int32_t year, Months month, int32_t day, int32_t hour, int32_t minute, int32_t second );
		Date(int32_t year, Months month, int32_t day);
		Date(int32_t hour, int32_t minute, int32_t second);
		Date(const Date& a);
		Date();

		uint32_t getYear();
		Months getMonth();
		int32_t getDay();
		int32_t getHour();
		int32_t getMinute();
		int32_t getSecond();

		Date addYear(int32_t deltaTime);
		Date addMonth(int32_t deltaMonth);
		Date addDay(int32_t deltaDay);
		Date addHour(int32_t deltaHour);
		Date addMinute(int32_t deltaMinute);
		Date addSecond(int32_t deltaSecond);

		std::string toString();
	};
}
std::ostream& operator<<(std::ostream& stream, DT::Months month); 
std::ostream& operator<<(std::ostream& stream, DT::Date object);