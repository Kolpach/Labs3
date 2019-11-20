#include <iostream>
#include <cmath>


using namespace std;
int main()
{
	double a11 = 1.09, a12 = -0.04, a13 = 0.21, a14 = -18;  // матрица 
	double a21 = 0.25, a22 = -1.23, a23 = -0.16, a24 = -0.09;
	double a31 = -0.21, a32 = -0.16, a33 = 0.8, a34 = -0.13;
	double a41 = 0.15, a42 = -1.31, a43 = 0.06, a44 = 0.84;
	double b1 = -1.24, b2 = 0.84, b3 = 2.56, b4 = 1.09;      // столбец свободных членов

	double x1 = 0, x2 = 0, x3 = 0, x4 = 0;          // начальное приближение
	double x1n, x2n, x3n, x4n;
	double eps = 0.0000000000001;
	int count;

	if (fabs(a11) > fabs(a12) + fabs(a13) + fabs(a14) &&
		fabs(a22) > fabs(a21) + fabs(a23) + fabs(a24) &&
		fabs(a33) > fabs(a31) + fabs(a32) + fabs(a34) &&
		fabs(a44) > fabs(a41) + fabs(a42) + fabs(a43))
		cout << "Diagonal'noe preobladaniye ne narushaetsya" << endl;
	else
	{
		cout << "Diagonal'noe preobladaniye narushaetsya" << endl;
	}
	count = 0;
	do
	{
		x1n = (b1 - (a12*x2 + a13 * x3 + a14 * x4)) / a11;
		x2n = (b2 - (a21*x1 + a23 * x3 + a24 * x4)) / a22;
		x3n = (b3 - (a31*x1 + a32 * x2 + a34 * x4)) / a33;
		x4n = (b4 - (a41*x1 + a42 * x2 + a43 * x3)) / a44;
		count = count + 1;
		if (fabs(x1n - x1) < eps &&
			fabs(x2n - x2) < eps &&
			fabs(x3n - x3) < eps &&
			fabs(x4n - x4) < eps) break;
		x1 = x1n;
		x2 = x2n;
		x3 = x3n;
		x4 = x4n;

		//  cout << "x1 = " << x1n << endl << "x2 = " << x2n << endl << "x3 = " << x3n << endl << "x4 = " << x4n << endl;   
	} while (1);
	x1 = x1n;
	x2 = x2n;
	x3 = x3n;
	x4 = x4n;
	cout << "Kolichestvo iter. = " << count << endl << "x1 = " << x1 << endl
		<< "x2 = " << x2 << endl << "x3 = " << x3 << endl << "x4 = " << x4 << endl;
	system("pause");
	return 0;
}