#include <iostream>
#include <vector>
#include <fstream>

using namespace std;
int Num = 0;//число вершин
bool* visit;
vector<int>* v;//списки смежности
void Read()
{
	//считаем файл и считаем сколько вершин
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
	v = new vector<int>[Num];
	in.open("matrix.txt");

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
		cout << i << ": ";
		for (int j = 0; j < v[i].size(); j++)
			cout << v[i][j] << " ";
		cout << endl;
	}
}

void DFS(int u, vector<int>* Q_m)
{
	visit[u] = true;

	for (int i = 0; i < v[u].size(); i++)
		if (!visit[v[u][i]])
			DFS(v[u][i], Q_m);
	Q_m->push_back(u);
}

void Component()
{
	vector<vector<int>> comp;//сохраняем туда все компонент связности
	visit = new bool[Num];
	for (int u = 0; u < Num; u++)
		visit[u] = false;

	vector<int> time_comp;//туда кидаем текущую компонент связность

	//запускаем поиск в глубину для каждой непосещенной вершины
	for (int u = 0; u < Num; u++)
	{
		if (!visit[u])
			DFS(u, &time_comp);

		comp.push_back(time_comp);
		time_comp.clear();
	}

	//вывод компонент связностей
	ofstream out; out.open("out.txt");
	out << "\n Компонент связности: \n";
	cout << "\n Компонент связности: \n";
	for (int i = 0; i < comp.size(); i++) {
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