#pragma once
#include<iostream>
#include<map>
#include<tuple>

enum SecurityCheckList { ISNEW, DEVELOPING, APPROBATION, ISDONE };
using SecurityList = std::map<SecurityCheckList, int>;

class SecurityDepartment
{
private:
	std::map<std::string, SecurityList> specialists;
public:
	const SecurityList& GetSpecialist(const std::string& specialist);
	void CreateNew(const std::string& person);
	std::tuple<SecurityList, SecurityList> Execute(const std::string& specialist, int count);//Нахуй нам count
};

