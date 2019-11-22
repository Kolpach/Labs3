#include "Date.h"
using namespace std;
int main() {
	DT::Date a(1, static_cast<DT::Months>(1), 1 , -45, 30, 30);
	DT::Date c;
	DT::Date c2;
	cout << a << endl;
	cout << a.addSecond(120) << endl;
	cout << c << endl;
	c2 = c.addYear(5);
	c2 = c2.addMonth(10);
	c2 = c2.addDay(-15);
	cout << c2.toString() << endl;
	return 0;
}