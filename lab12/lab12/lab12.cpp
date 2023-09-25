﻿#include <iostream>
#include <string>
#include <vector>

using namespace std;
//префикс функция
void kmp_init(int*& prefix, string q)
{
	int len = 0;//временная переменная для длины
	prefix[0] = 0;//префикс нулевого символа = 0 (нет пар для сравнения) 
	int i = 1;//начинаем с 1 символа
	while (i < q.length())//пока не дошли до конца подстроки
	{
		if (q[i] == q[len])//если символы i-го символа и символа len совпали
		{
			len++;//увеличиваем максимальную длину этого приефикса
			prefix[i] = len;//даем этому символу данную длину
			i++;//идем проверять дальше
		}
		else
		{
			if (len != 0)//если длина была больше 0
				len = prefix[len - 1];//даем ей значение прошлой ячейки
			else
			{
				prefix[i] = 0;//длина по этому индексу = 0
				i++;//проверяем дальше
			}
		}
	}
}
void KMP_pattern_search(string s, string q)
{
	if (s.length() < q.length())//защита
		exit(1);

	vector<int> k_mas;//вектор индексов
	int* prefix = new int[q.length()];//массив для префиксов
	kmp_init(prefix, q);//заполняем префиксы

	int j = 0, i = 0;//индексы для проверки строки (i) и подстроки (j)

	while (i <= s.length())//пока не дойдем до конца строки
	{
		if (q[j] == s[i])//если символы совпали
		{
			//идем проверять дальше
			i++;
			j++;
		}
		if (j == q.length())//если дошли до конца подстроки, занчит нашли подстроку в строке
		{
			k_mas.push_back(i - j + 1);//запоминаем индекс начала(в скобках так вычисляется индекс подстроки)+1 ротому что индексация с 1 должна начаться
			j = prefix[j - 1];//перемещяемся на проверку подстроки по предспоследнему совпадению в массиве префиксов
		}
		else if (i <= s.length() && q[j] != s[i])//если же не дошли до конца строки и символы не совпали
		{
			if (j == 0)//если находимся в начале подстроки, то просто начинаем смотреть со следующего символа в строке
				i++;
			else
				j = prefix[j - 1];//иначе, перемещаемся на проверку подстроки по предпоследнему совпадению
		}
	}
	if (k_mas.empty())
		cout << "Не нашли!! \n";
	else
	{
		cout << "\nНашли! \n";
		for (int i=0;i< k_mas.size();i++)
			cout <<k_mas[i] << " ";
	}
	//подчищаем за собой память
	delete[] prefix;
}

int main()
{
	setlocale(LC_ALL, "Rus");
	string s = "", q = "";
	
	cout << "Введите строку: \n";
	getline(cin, s);
	cout << "Введите подстроку: \n";
	getline(cin, q);

	for (int i = 0; i < s.length(); i++)
		cout << s[i] << ":" << i + 1 << " ";
	cout << endl;

	KMP_pattern_search(s, q);
	return 0;
}