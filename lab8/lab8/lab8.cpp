#include <iostream>
#include <vector>
#include <fstream>

const int INF = 1e11;
using namespace std;
struct Edge {
	int left, right, weight;
	Edge(int m_left, int m_right, int m_weight)
	{
		left = m_left;
		right = m_right;
		weight = m_weight;
	}
};
int Num = 0; //количество вершин
vector <int>* v; //списки  смежности
vector<Edge> g; //хранятся все ребра
int* d; //расстояние каждой вершины

void Read()
{
	int element;
	ifstream in; in.open("matrix.txt");
	if (!in)
	{
		cout << "File!";
		exit(1);
	}
	else
		while (in >> element)
			Num++;

	in.close();
	Num = sqrt(Num);
	
	in.open("matrix.txt");
	v = new vector<int>[Num];
	for (int i = 0; i < Num; i++)
	{
		for (int j = 0; j < Num; j++)
		{
			in >> element;
			if (element != 0)
			{
				g.push_back(Edge(i, j, element));
				v[i].push_back(j);
			}
		}
	}
	
	in.close();

	cout << "Списки смежности. \nВершина: смежные с ней \n";
	for (int i = 0; i < Num; i++)
	{
		cout << i << ": "; 
		for (int j = 0; j < v[i].size(); j++)
			cout << v[i][j] << " ";
		cout << endl;
	}
}
//вернет вершину с минимальным расстоянием до остновоного дерева (пару "вершина, посещена или нет")
pair<int, bool> Extract_Min(vector<pair<int, bool>>& Q_m)
{
	int minn = INF, x = -1; 
	pair<int, bool> u; //временная пара
	for (int i = 0; i < Q_m.size(); i++)
	{
		if (Q_m[i].second)//проверяем, что ее посещали и ее можно брать
			//поиск минимального расстояния и запоминания индекса, чтобы ее потом забрать и удалить
			if (d[Q_m[i].first] < minn)
			{
				minn = d[Q_m[i].first];
				u = Q_m[i];
				x = i;
			}
	}
	//если индекс изменился, то удаляем эту вершину
	if (x != -1)
		Q_m.erase(Q_m.begin() + x);
	return u;
}

//вернет длину вектора между вершинами
int w(int u, int v)
{
	for (int i = 0; i < g.size(); i++)
		if ((g[i].left == u && g[i].right == v) || (g[i].left == v && g[i].right == u))
			return g[i].weight;
}

//возвращает индекс вершины в векторе(т.к. они удаляются и идут не по порядку)
int find(vector<pair<int, bool>> Q_m, int r)
{
	for (int i = 0; i < Q_m.size(); i++)
		if (Q_m[i].first == r)
			return i;
}

void Dijkstra(int a)
{
	vector <pair<int, bool>> Q;//пара "вершина, заходили в нее или нет"
	d = new int[Num]; //создаем для каждой вершины расстояние 

	for (int v = 0; v < Num; v++)
	{
		d[v] = INF;
		Q.push_back(make_pair(v, false)); //создаем пары "вершина, заходили в нее или нет"
	}

	d[a] = 0;
	Q[a].second = true;

	while (!Q.empty())
	{
		pair<int, bool> u = Extract_Min(Q); //забрали вершину с минимальным расстоянием до остовного дерева
		for(int i=0;i<v[u.first].size();i++)
		{
			if (d[u.first] + w(u.first, v[u.first][i]) < d[v[u.first][i]])//проверяем, расстояние текущей вершины + длина дуги до смежной вершины < чем текущее расстояние вершины
			{
				Q[find(Q, v[u.first][i])].second = true; //говорим, что эту вершину мы посетили
				d[v[u.first][i]] = d[u.first] + w(u.first, v[u.first][i]);//меняем расстояние смежной вершины до меньшего
			}
		}
	}

	ofstream out; out.open("out.txt");
	out << "Вершина : расстояние от " << a << endl;
	cout << "Вершина : расстояние от " << a << endl;
	for (int i = 0; i < Num; i++)
	{
		
		if (d[i] != INF)
		{
			out << i << " : " << d[i] << endl;
			cout << i << " : " << d[i] << endl;
		}
		else
		{
			out << i << " : недостежимо" << endl;
			cout << i << " : недостежимо"  << endl;
		}

	}

}
void Min_rast(int a)
{
	if (v[a].empty())
		cout << "Нет смежных! Значит расстояние до всех бесконечность \n";
	else
		Dijkstra(a);
}

int main()
{
	setlocale(LC_ALL, "Rus");
	Read();
	Min_rast(0);
	return 0;
}