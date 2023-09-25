#include <iostream>
#include <string>
#include <vector>

using namespace std;

//функция выдаст строку с "уникальными" символами нашей подстроки
string Alphabet(string q)
{
	string time = "";//временная строка для обработки
	for (int i = 0; i < q.length(); i++)
		if (time.find(q[i]) == string::npos)//если встретили символ, которого еще нет
			time += q[i]; //то добавляем в наш результат

	return time;
}

void init_mas(int** mas, string q, int m)	//функция создания матрицы переходов 
{
	string Alph = Alphabet(q);
	int len = 0;//временная переменная для заполнения матрицы

	//заполняем первую строку нулями
	for (int j = 0; j < m; j++)
		mas[0][j] = 0;
	mas[0][0] = 1;//начальный символ

	for (int i = 1; i < q.length()+1; i++)
	{
		//копируем текущую строчку на индекс нашей переменной len
		for (int j = 0; j < m; j++)
			mas[i][j] = mas[len][j];

		mas[i][Alph.find(q[i])] = i + 1;//переход по следующей букве в следующее состояние

		len = mas[len][Alph.find(q[i])];//обновляем нашу переменную
	}
	 
	cout << "\n Таблица переходов: \nstate\t";
	for (int i = 0; i < Alph.size(); i++)
		cout << Alph[i] << " ";
	cout << endl;
	for (int i = 0; i < q.length()+1; i++)
	{
		cout << "  " <<  i << " \t";
		for (int j = 0; j < m; j++)
			cout << mas[i][j] << " ";
		cout << endl;
	}
	cout << endl;
}

void SM_pattern_search(string s, string q, int** mas)
{
	if (s.length() < q.length()) //защита
		exit(1);

	vector<int> k_mas;//вектор индексов
	int state = 0;//переменная состояния

	//тут бегаем по матрице и меняем состояние
	for (int i = 0; i < s.length(); i++)
	{
		if (Alphabet(q).find(s[i]) == string::npos) //если элемента строки нет в нашей подстроке, то переходим в состояние 0
			state = 0;
		else
			state = mas[state][Alphabet(q).find(s[i])]; //если элемент все-таки есть, то переходим в столбец по этому символу

		if (state == q.length())//если дошли до последнего состояния, то нашли всю подстроку
			k_mas.push_back(i - q.length() + 2);
	}

	if (k_mas.empty())
		cout << "\n Не найдено подстроки!! \n";
	else
	{
		cout << "\nНашли! \n";
		for (int i=0;i< k_mas.size();i++)
			cout << k_mas[i] << " ";
	}
}

int main()
{
	setlocale(LC_ALL, "Rus");
	string s = "ASACACAGAsdFGHADFH", q = "ACACAGA";
	cout << "Введите строку: \n";
	//getline(cin, s);
	cout << "Введите подстроку: \n";
	//getline(cin, q);
	
	//выпишем нашу строку с индексами
	for (int i = 0; i < s.length(); i++)
		cout << i + 1 << ":" << s[i] << "  ";
	cout << endl;

	int alphabet = Alphabet(q).length();//количество символов в алфавите
	//массив для матрицы переходов
	int** mas = new int* [q.length() + 1];
	for (int i = 0; i < q.length() + 1; i++)
		mas[i] = new int[alphabet];

	init_mas(mas, q, alphabet);//заполняем матрицу
	SM_pattern_search(s, q, mas);//запускаем поиск подстроки

	//очищаем за собой память
	for (int i = 0; i < q.length(); i++)
		delete[] mas[i];
	delete[] mas;
	return 0;
}