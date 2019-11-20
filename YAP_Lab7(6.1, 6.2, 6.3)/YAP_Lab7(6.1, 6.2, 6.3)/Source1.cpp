#include <iostream>
#include <vector>
using namespace std;
struct Dirrection
{
	int16_t dy;
	int16_t dx;
	Dirrection(int16_t a, int16_t b)
	{
		dy = a;
		dx = b;
	}
};
pair<Dirrection, Dirrection> FindWall(vector<vector<int16_t>> &matrix, int16_t i, int16_t j, bool vverh, bool vlevo)//‘ункци€ ищет проход. ѕриоритет отдаЄтс€ в таком пор€дке(вверх, вправо, вниз, влево)
{//“аким образом реализуетс€ оюход лабиринта по часовой стрелке. 
	vector<pair<int16_t, Dirrection>> variants;
	variants.push_back(pair<int16_t, Dirrection >(matrix[i - 1][j], Dirrection(-1, 0)));
	variants.push_back(pair<int16_t, Dirrection >(matrix[i][j + 1], Dirrection(0, 1)));
	variants.push_back(pair<int16_t, Dirrection >(matrix[i + 1][j], Dirrection(1, 0)));
	variants.push_back(pair<int16_t, Dirrection >(matrix[i][j - 1], Dirrection(0, -1)));

	if (variants[3].first == 1 && (variants[0].first == 0 || variants[0].first == 2) && vverh)//¬ узких "коридорах" направление определ€етс€ в зависимости от прошлого движени€
	{
		return pair<Dirrection, Dirrection>(variants[3].second, variants[0].second);
	}
	if (variants[2].first == 1 && (variants[3].first == 0 || variants[3].first == 2) && !vlevo)//¬ узких "коридорах" направление определ€етс€ в зависимости от прошлого движени€
	{
		return pair<Dirrection, Dirrection>(variants[2].second, variants[3].second);
	}
	for (int16_t lIndex=0; lIndex < 3; ++lIndex)
	{
		if (variants[lIndex].first == 1 &&( variants[lIndex + 1].first == 0 || variants[lIndex + 1].first == 2))
		{
			return pair<Dirrection, Dirrection>(variants[lIndex].second, variants[lIndex + 1].second);
		}
	}
	if (variants[2].first == 1 && (variants[3].first == 0 || variants[3].first == 2) && vlevo)//¬ узких "коридорах" направление определ€етс€ в зависимости от прошлого движени€
	{
		return pair<Dirrection, Dirrection>(variants[2].second, variants[3].second);
	}
	if (variants[3].first == 1 && (variants[0].first == 0 || variants[0].first == 2) && !vverh)//¬ узких "коридорах" направление определ€етс€ в зависимости от прошлого движени€
	{
		return pair<Dirrection, Dirrection>(variants[3].second, variants[0].second);
	}
	//ќбычно возвращаем вектор по которому двигатс€ и вектор, если стена р€дом пропадЄт.
	return pair<Dirrection, Dirrection>(Dirrection(0, 0), Dirrection(0, 0));//Ёто случай если изначально точка окружена стенами
}
int main()
{
	setlocale(0, "");
	int16_t n, m;//n - количество строк, m - количество столбцов
	cin >> n >> m;
	vector<vector<int16_t>> matrix;

	matrix.push_back({});//«аполн€ем матрицу m*n с проверкой на вводимые числа. ¬клеиваем еЄ в "рамку" из едениц, чтобы легче было учитывать случай выхода за границы
	for (int16_t j = 0; j <= m+1; ++j)
	{
		matrix[0].push_back(1);
	}
	for (int16_t i = 1; i <= n; ++i)
	{
		matrix.push_back({1});
		int16_t local;
		for (int16_t j = 0; j < m; ++j)
		{
			mark:
			cin >> local;
			if (local > 1 || local < 0)
			{
				cerr << "Ќедопустимыое значение. ¬ведите коректное значение" << endl;
				for (int16_t a : matrix[i])
				{
					cout << a << " ";
				}
				goto mark;
			}
			else
			{
				matrix[i].push_back(local);
			}
		}
		matrix[i].push_back(1);
	}
	matrix.push_back({});//конец заполнени€
	for (int16_t j = 0; j <= m+1; ++j)
	{
		matrix[n+1].push_back(1);
	}

	int i = 1, j = 1;
	Dirrection moving_vector(0, 0);
	Dirrection extra_vector(0, 0);
	do
	{
		pair<Dirrection, Dirrection> loc = FindWall(matrix, i, j, extra_vector.dy - 1, extra_vector.dx +1);//определ€ем куда двигатс€
		moving_vector = loc.second;
		extra_vector = loc.first;//так двигаемс€, если ближайша€ стена исчезает
		if (0 == moving_vector.dx && 0 == moving_vector.dy && 0 == extra_vector.dx && 0 == extra_vector.dy)//≈сли точка старта окруженна 4 стенами
			break;
		while (matrix[i + moving_vector.dy][j + moving_vector.dx] != 1 )
		{
			matrix[i][j] = 2;
			if (matrix[i + extra_vector.dy][j + extra_vector.dx] == 1)//двигаемс€
			{
				i += moving_vector.dy;
				j += moving_vector.dx;
				
			}
			//если стена пропала
			if (matrix[i + extra_vector.dy][j + extra_vector.dx] != 1 && !((i == 1 && j == 1) || (i == n && j == m)) )//2-3 проверка чтобы случайно не пройти конечную точку.
			{
				matrix[i][j] = 2;
				i += extra_vector.dy;
				j += extra_vector.dx;
				break;
			}
			if (((i == 1 && j == 1) || (i == n && j == m)))//проверки чтобы случайно не пройти конечную точку.
				break;
		}
	} while ( (i != 1 || j != 1) && (i != n || j != m) );

	if (i == n && j == m)
		cout << "YES" << endl;
	else
		cout << "NO" << endl;
	for (vector<int16_t> a : matrix)//вывод итоговой матрицы
	{
		for (int16_t b : a)
		{
			cout << b << " ";
		}
		cout << endl;
	}
	system("pause");
	return 0;
}