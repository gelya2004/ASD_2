#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <fstream>
using namespace std;

int Num=0;//число вершин
bool* visit;
list<int>* v;//списки смежности

void Read()
{
	//считаем файл и считываем сколько вершин
	int element;
	ifstream in; in.open("matrix.txt");
	if (!in)
		exit(1);
	else
		while (in >> element)
			Num++;
	in.close();
	Num = sqrt(Num);

	//считываем файл и запоминаем смежные вершины
	v = new list<int>[Num];
	in.open("matrix.txt");
	if (!in)
		exit(1);
	for (int i = 0; i < Num; i++)
		for (int j = 0; j < Num; j++)
		{
			in >> element;
			if (element == 1)
				v[i].push_back(j);
		}
	in.close();

	cout << "Вершина: смежные с ней \n";
	for (int i = 0; i < Num; i++)
	{
		cout << i << ": "; copy(v[i].begin(), v[i].end(), ostream_iterator<int>(cout, " "));
		cout << endl;
	} 
}

void BFS(int s, vector<int>* Q_m)
{
	queue <int> Q;
	Q.push(s);
	int u = 0;
	while (!Q.empty())
	{
		u = Q.front();
		visit[u] = true;
		Q_m->push_back(Q.front());
		Q.pop();

		for (auto i = v[u].begin(); i != v[u].end(); i++)
			if (!visit[*i])
			{
				visit[*i] = true;
				Q.push(*i);
			}
	}
}
void Component()
{
	vector<vector<int>> comp;//сохраняем туда все компонент связности
	visit = new bool[Num];
	for (int u = 0; u < Num; u++)
		visit[u] = false;

	vector<int> time_comp;//туда кидаем текущую компонент связность

	//запускаем поиск в ширину для каждой непосещенной вершины
	for (int u = 0; u < Num; u++)
	{
		if (!visit[u])
			BFS(u, &time_comp);
		comp.push_back(time_comp);
		time_comp.clear();
	}

	//вывод компонент связностей
	ofstream out; out.open("out.txt");
	out << "\n Компонент связности: \n";
	cout << "\n Компонент связности: \n";
	for (int i = 0; i < comp.size(); i++){
		if (!comp[i].empty())
		{
			for (int j = 0; j < comp[i].size(); j++) {
				out << comp[i][j] << " ";
				cout << comp[i][j] << " ";
			}
			out << endl;
			cout << endl;
		}
	}


	delete[] visit;
	delete[] v;
}

int main()
{
	setlocale(LC_ALL, "Rus");
	Read();
	Component();
	return 0;
}