#include <iostream>
#include <string>
#include <vector>

using namespace std;

//вернет разницу между длиной подстроки и последним индексом этого символа
int last(string q, char x)
{
	int count = 0;
	for (int i = 0; i < q.size(); i++)
		if (q[i] == x)
			count = i;

	return q.size() - 1 - count;
}

//вернет разницу между длиной подстроки и предпоследним индексом этого символа
int penultimate(string q, char x)
{
	int count1 = 0, count2 = 0;
	bool f = true;
	for (int i = 0; i < q.size(); i++)
		if (q[i] == x)
		{
			if (f)
				count1 = i;
			else
				count2 = i;
			f = !f;
		}

	return count1 > count2 ? q.size() - 1 - count2 : q.size() - 1 - count1;
}

//вернет сколько раз встречался этот символ в подстроке
int Num(string q, char x)
{
	int count = 0;
	for (int i = 0; i < q.size(); i++)
		if (q[i] == x)
			count++;
	return count;
}

void init_d(int*& d, string q)
{
	for (int i = 0; i < 256; i++)
	{
		if (q[q.size() - 1] != char(i) && Num(q, char(i)) != 0)//если символ не последний и встречался хоть 1 раз
			d[i] = last(q, char(i));//он равен разице между длиной подстроки и последним разом его встречи в подстроке

		else if (q[q.size() - 1] == char(i) && Num(q, char(i)) >= 2)//если символ последний и втречался, как минимум, 2 раза
			d[i] = penultimate(q, char(i));//он равен разице между длиной подстроки и предпоследним разом его встречи в подстроке

		else if (q[q.size() - 1] == char(i) && Num(q, char(i)) == 1)//если символ последний и встречался 1 раз
			d[i] = q.size() - 1;//он равен длине посдтроки -1
		else
			d[i] = q.size();//если не встретился, то равен длине подстроки
	}
	cout << "\nТаблица стоп символов: \n";
	for (int i = 0; i < 256; i++)
		if ((char(i)>='a' && char(i)<='z') || (char(i) >= 'A' && char(i) <= 'Z'))
			cout << char(i) << " " << d[i] << endl;
}

void BM_pattern_search(string s, string q)
{
	if (s.size() < q.size())//защита
		exit(1);

	vector<int> k_mas;//вектор индексов

	int* d = new int[256];//создаем массив стоп символов
	init_d(d, q);//заполняем массив стоп символов

	int j;
	cout << "\nИндекс символа строки для проверки, Стоп символ + отступ: \n";
	for (int k = 0; k <= s.size() - q.size(); k += d[s[k + q.size() - 1]])
	{
		cout << "k = " << k+1 << " " << s[k + q.size() - 1] << " + " << d[s[k + q.size() - 1]] << endl;//вывод действий программы

		for (j = q.size() - 1; j > 0; j--)//проверяем посимвольно с конца подстроку и кусочек строки
			if (s[k + j] != q[j])//если не совпали символы, прекращаем
				break;
		if (j == 0)//прошлись по всей подстроке, запомнили индекс
			k_mas.push_back(k + 1);
	}

	if (k_mas.empty())
		cout << "Не нашли !! \n";
	else
	{
		cout << "\n Нашли! \n";
		for (int i=0;i< k_mas.size();i++)
			cout << k_mas[i] << " ";
	}
	delete[] d;
}

int main()
{
	setlocale(LC_ALL, "Rus");
	string s = "", q = "";
	
	cout << "Введите строку: \n";
	getline(cin, s);
	cout << "Введите подстроку: \n";
	getline(cin, q);

	for (int i = 0; i < s.size(); i++)
		cout << s[i] << ":" << i + 1 << " ";
	cout << endl;
	BM_pattern_search(s, q);
	return 0;
}