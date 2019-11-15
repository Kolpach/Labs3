#include "SecurityDepartment.h"

const SecurityList& SecurityDepartment::GetSpecialist(const std::string& specialist)
{
	return specialists[specialist];
}

void SecurityDepartment::CreateNew(const std::string& person)
{
	if (specialists.find(person) == specialists.end()) {
		SecurityList newOne{ {SecurityCheckList::ISNEW, 0 }, {SecurityCheckList::DEVELOPING, 0}, {SecurityCheckList::APPROBATION, 0}, {SecurityCheckList::ISDONE, 0} };
		specialists.insert(std::pair<std::string, SecurityList>(person, newOne));
	}
	else {
		++specialists[person][SecurityCheckList::ISNEW];
	}
}

std::tuple<SecurityList, SecurityList> SecurityDepartment::Execute(const std::string& specialist, int count)//Нахуй нам не нужон этот ваш count
{
	SecurityList oldOne;
	specialists[specialist][SecurityCheckList::ISDONE] += specialists[specialist][SecurityCheckList::APPROBATION];
	specialists[specialist][SecurityCheckList::APPROBATION] = specialists[specialist][SecurityCheckList::DEVELOPING];
	specialists[specialist][SecurityCheckList::DEVELOPING] = specialists[specialist][SecurityCheckList::ISNEW];
	specialists[specialist][SecurityCheckList::ISNEW] = 0;
	return std::tuple<SecurityList, SecurityList>();
}
