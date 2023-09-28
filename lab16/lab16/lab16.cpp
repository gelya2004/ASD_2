#include <iostream>

using namespace std;

int main()
{
	setlocale(LC_ALL, "Rus");
	int W = 7;
	pair<int, int> things[] = { (make_pair(1, 2500)),make_pair(3, 2000),make_pair(3, 2000),make_pair(3, 2000),make_pair(4, 4000) ,make_pair(8, 4000) };

	int** c = new int* [size(things) + 1];
	for (int i = 0; i <= size(things); i++)
		c[i] = new int[W + 1];

	for (int i = 0; i <= size(things); i++)
	{
		for (int j = 0; j <= W; j++)
		{
			if (i == 0 || j == 0) // Если нет вещей или вместимость рюкзака равна нулю, то стоимость равна нулю
				c[i][j] = 0;

			else
			{
				if (things[i - 1].first > j) // Если вес текущей вещи больше вместимости рюкзака, то берем предыдущую вещь
					c[i][j] = c[i - 1][j];

				else
					c[i][j] = max(c[i - 1][j], things[i - 1].second + c[i - 1][j - things[i - 1].first]); // Иначе выбираем максимальную стоимость из предыдущей вещи и текущей вещи плюс стоимость оставшегося пространства в рюкзаке

			}
		}
	}

	for (int i = 0; i <= size(things); i++)   // Вывод таблицы стоимостей
	{
		for (int j = 0; j <= W; j++)
		{
			if (i == 0 || j == 0)
				cout << " \t";
			else
				cout << c[i][j] << " \t \t";
		}
		cout << endl;
	}
	cout << "Итоговая стоимость: " << c[size(things)][W];

	return 0;
}
