#include <iostream>
#include <string>
#include <vector>

using namespace std;
//считываем код каждого символа
int Hash(string s, int M)
{
	int h = 0;
	for (int i = 0; i < M; i++)
		h += s[i];
	return h;
}
int hash_update(int hs, char out, char in)
{
	return hs + in - out;
}

void RK_pattern_search(string s, string q)
{
	if (q.size() > s.size())//если подстрока больше строки, выход
		exit(1);

	vector<int> k_mas;//вектор индексов
	int hs = Hash(s, q.size()); //значение хеш-функции для строки(размер нашей подстроки)
	int hq = Hash(q, q.size());	//значение хеш-функции для подстроки

	for (int k = 0; k <= s.size() - q.size(); k++)
	{
		int j = 0;//индекс для обработки подстркои
		if (hs == hq)//если хещ-функции совпали, то сравниваем посимвольно строку и подстроку
		{
			for (j = 0; j < q.size(); j++)
				if (s[k + j] != q[j])
					break;

			if (j == q.size())//если дошгли до конца, то это наша строка
				k_mas.push_back(k + 1);//запоминаем инлекс
		}

		hs = hash_update(hs, s[k], s[k + q.size()]);//если хеш-функции не совпали, то обновляем хеш-функцию для кусочка сроки
	}

	if (k_mas.empty())
		cout << "Не найдено !! \n";
	else
	{
		cout << "\n Нашли! \n";
		for (int i=0;i<k_mas.size();i++)
			cout << k_mas[i] << " ";
	}
}

int main()
{
	setlocale(LC_ALL, "Rus");
	string s, q;
	cout << "Введите строку: \n";
	getline(cin, s);
	cout << "Введите подстроку: \n";
	getline(cin, q);

	RK_pattern_search(s, q);
	return 0;
}