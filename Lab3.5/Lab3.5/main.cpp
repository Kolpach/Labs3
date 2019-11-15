#include"SecurityDepartment.h"
using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::map;
using std::tuple;

int main()
{
	SecurityDepartment Department;
	Department.CreateNew("Vlad");
	Department.Execute("Vlad", 1);
	return 0;
}