#include <iostream>
#include <vector>
#include <fstream>

using namespace std;
int Num = 0; // количество вершин
vector<int>* v; //списки смежности
vector<int>* B; //векторы, где хранятся вершины одного цвета
pair<int, int>* deg; //пара "вершина, степень(количество смежных вершин)"

void Read()
{
	int element;
	ifstream in; in.open("matrix.txt");
	if (!in)
	{
		cout << "File! \n";
		exit(1);
	}
	else
		while (in >> element)
			Num++;
	in.close();
	Num = sqrt(Num);
	deg = new pair<int, int>[Num];
	
	B = new vector<int>[Num];

	in.open("matrix.txt");
	v = new vector<int>[Num];
	for (int i = 0; i < Num; i++)
		for (int j = 0; j < Num; j++)
		{
			in >> element;
			if (element != 0)
			{
				v[i].push_back(j);
				deg[i].second++;
				deg[i].first = i;
			}
		}
	
	in.close();

	cout << "\nВершина: смежные с ней \n";
	for (int i = 0; i < Num; i++)
	{
		cout << i << ": "; 
		for (int j = 0; j < v[i].size(); j++)
			cout << v[i][j] << " ";
		cout << endl;
	}
}

void Sort()
{
	for (int i = 0; i < Num - 1; i++)
		for (int j = i + 1; j < Num; j++)
			if (deg[i].second < deg[j].second)
				swap(deg[i], deg[j]);
}

//проверка на смежность элемента j с вершинами вектора определенного цвета
bool Smegni(int j, vector<int>B_m)
{
	for (auto u : B_m)
		for (auto i = v[u].begin(); i != v[u].end(); i++)
			if (j == *i)
				return true;
	return false;
}

//проверка на закрашена или нет входящая вершина
bool Color_B(int u)
{
	for (int i = 0; i < Num; i++)
		for (int j = 0; j < B[i].size(); j++)
		{
			if (B[i][j] == u)
				return true;
			else
				continue;
		}
	return false;
}

//фуекция раскраски графа
void Paint()
{
	int k = 0;
	B[k].push_back(deg[0].first);//закинули начальную точку в первый цвет
Start:
	for (int i = 1; i < Num; i++)
	{
		if (!Color_B(deg[i].first) && !Smegni(deg[i].first, B[k])) //если вершина не окрашена и она не смежная с вершинами этого цвета
			B[k].push_back(deg[i].first);
		else 
			continue;
	}
	//проверяем покрасили ли все вершины
	for (int i = 0; i < Num; i++) {
		if (!Color_B(i)) {
			k++;
			goto Start;
		}
		else
			continue;
	}

	cout << endl;
	for (int i = 0; i < Num; i++)
	{
		if (!B[i].empty())
		{
			cout << char(i + 65) << ": ";
			for (int j = 0; j < B[i].size(); j++)
				cout << B[i][j] << " ";
			cout << endl;
		}
	}
}

int main()
{
	setlocale(LC_ALL, "Rus");
	Read();
	Sort();
	Paint();
	return 0;
}

//0 1 0 0 1 0 0 0 0
//1 0 1 1 1 0 0 0 0
//0 1 0 1 0 1 0 1 0
//0 1 1 0 1 1 1 0 0
//1 1 0 1 0 0 1 0 0
//0 0 1 1 0 0 1 1 1
//0 0 0 1 1 0 1 0 1
//0 0 1 0 0 1 0 0 1
//0 0 0 0 0 1 1 1 0


