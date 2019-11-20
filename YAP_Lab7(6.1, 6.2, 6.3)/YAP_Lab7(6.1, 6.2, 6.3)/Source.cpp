#include <iostream>
#include <vector>
#define M 4
#define N 6
using namespace std;
void show(vector<vector<int16_t>> &mat)
{
	for (vector<int16_t> stroke : mat)
	{
		for (int16_t element : stroke)
		{
			cout << element << " ";
		}
		cout << endl;
	}
}
int main()
{
	setlocale(0, "");
	vector<vector<int16_t>> matrix = {  {1,		12,		37,		26}, 
										{28,	6,		125,	14},
										{81,	0,		77,		121},
										{111,	56,		31,		72},
										{40,	14,		65,		58},
										{21,	17,		49,		86} };
	cout << "Исходная матрица: " << endl;
	show(matrix);
	int buffer;
	for (int i = 0; i < N / 2; ++i)
	{
		for (int j = 0; j < M / 2; ++j)
		{
			buffer = matrix[i][j];
			matrix[i][j] = matrix[i + N / 2][j + M / 2];
			matrix[i + N / 2][j + M / 2] = buffer;
		}
	}
	cout << "Матрица после перестановки: " << endl;
	show(matrix);
	cout << endl;
	system("pause");
	return 0;
}