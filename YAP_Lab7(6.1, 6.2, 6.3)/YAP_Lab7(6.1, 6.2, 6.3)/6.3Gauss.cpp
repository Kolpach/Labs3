#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
void swapMat(double A[4][4], int begin_index, int stolbec_index, int stroke_index)
{
	double buffer;
	if(begin_index != stolbec_index)
	for(int i =0; i<4; ++i)
	{
		buffer = A[i][stolbec_index];
		A[i][stolbec_index] = A[i][begin_index];
		A[i][begin_index] = buffer;
	}
	if (begin_index != stroke_index)
	for (int i = 0; i < 4; ++i)
	{
		buffer = A[stroke_index][i];
		A[stroke_index][i] = A[begin_index][i];
		A[begin_index][i] = buffer;
	}
}
void show(double A[4][4])
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			cout << A[i][j] << "       \t";
		}
		cout << endl;
	}
	cout << "--------" << endl;
}
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
int main()
{
	const double eps = 0.001;
	setlocale(0, "");

	double A[4][4] = { {1.09, -0.04, 0.21, -18},{0.25, -1.23, -0.16, -0.09},{-0.21, -0.16, 0.8, -0.13},{0.15, -1.31, 0.06, 0.84} };
	double B[4] = { -1.24, 0.84, 2.56, 1.09 };
	double x_k[4] = { 0, 0, 0, 0 };
	double max = A[0][0];
	int maxI = 0, maxJ = 0;
	for (int stolbec = 0; stolbec < 3; ++stolbec)//переставляем строки и столбцы, чтобы получить наиб. на диагонали
	{
		max = A[stolbec][stolbec];
		maxI = stolbec;
		maxJ = stolbec;
		for (int i = stolbec; i < 4; ++i)
		{
			for (int j = stolbec; j < 4; ++j)
			{
				if (abs(A[i][j]) > abs(max))
				{
					max = A[i][j];
					maxI = i;
					maxJ = j;
				}
			}
		}
		swapMat( A, stolbec, maxJ, maxI);
	}
	show(A);

	for (int stolbec = 0; stolbec < 3; ++stolbec)//приводим к треугольному виду
	{
		//double koeficent = A[stolbec + 1][stolbec] / A[stolbec][stolbec];
		for (int i = stolbec; i < 3; ++i)
		{
			for (int j = 3; j > stolbec - 1; --j)
			{
				A[i+1][j] -= A[i+1][stolbec] * A[stolbec][j] / A[stolbec][stolbec];
			}
		}
	}
	show(A);

	for (int stolbec = 3; stolbec >= 0; --stolbec)//обратный ход
	{
		x_k[stolbec] = B[stolbec] / A[stolbec][stolbec];
		for (int i = 0; i < 4; ++i)
		{
			B[i] -= A[i][stolbec] * x_k[stolbec];
		}

	}
	cout << "Roots: ";
	for (int i = 0; i < 4; ++i)//вывод
	{
		cout << setprecision(5) << x_k[i] << "\t";
	}
	cout << endl;
	cout << endl << "Check: " << endl;
	for (int i = 0; i < 4; ++i)
	{
		cout << multipliy_Array_Array(A[i], x_k, 4) << endl;
	}
	cout << endl;
	system("pause");
	return 0;
}