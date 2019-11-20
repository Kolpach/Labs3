#include <iostream>
using namespace std;
double multipliy_Array_Array(const double *A, const double *X, size_t size)
{
	double result = 0;
	double a, b;
	for (size_t i = 0; i < size; ++i)
	{
		a = *(A + i);
		b = *(X + i);
		result += (a * b);
	}
	return result;
}
bool check(const double A[], const double B[], double e = 1)
{
	bool result = false;
	for (size_t i = 0; i < 4; ++i)
	{
		if (A[i] - B[i]  > e || A[i] - B[i] < -e)
		{
			result = true;
			break;
		}
	}
	return result;
}
int main()
{
	setlocale(0, "");

	const double A[4][4] = { {1.09, -0.04, 0.21, -18},{0.25, -1.23, -0.16, -0.09},{-0.21, -0.16, 0.8, -0.13},{0.15, -1.31, 0.06, 0.84} };
	double C[4][4] = { {0, -A[0][1] / A[0][0], -A[0][2] / A[0][0], -A[0][3] / A[0][0]},
							 {-A[1][0] / A[1][1], 0, -A[1][2] / A[1][1], -A[1][3] / A[1][1]},
							 {-A[2][0] / A[2][2], -A[2][1] / A[2][2], 0, -A[2][3] / A[2][2]},
							 {-A[3][0] / A[3][3], -A[3][1] / A[3][3], -A[3][2] / A[3][3], 0}, };
	double B[4] = { -1.24, 0.84, 2.56, 1.09 };
	double x_k[4] = { 1, 1, 1, 1 };
	double x_k2[4] = { 0, 0, 0, 0 };//привближение x0
	do
	{

		for (size_t i = 0; i < 4; ++i)
		{
			x_k[i] = x_k2[i];
			x_k2[i] = 0;
		}
		for (size_t i = 0; i < 4; ++i)
		{
			x_k2[i] = B[i] / A[i][i] + multipliy_Array_Array(&(C[i][0]), x_k, 4);
		}
	} while (check(x_k2, x_k));
	
	system("pause");
	return 0;
}