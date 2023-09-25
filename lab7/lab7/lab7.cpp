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

int Num = 0;//число вершин
vector<int>* v;//списки смежности
vector<Edge> g;//вектор <левая, правая, вес>
int* parent;//массив родителей
vector <bool> inMST; //для каждой вершины скажем, она в минимальном остовном дереве или нет

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
	v = new vector<int>[Num];
	in.open("matrix.txt");
	for (int i = 0; i < Num; i++)
		for (int j = 0; j < Num; j++)
		{
			in >> element;
			if (element != 0)
			{
				v[i].push_back(j);
				g.push_back(Edge(i, j, element));
			}
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
// вернет вершину с минмальным числом до другой вершины (минимальное ребро)
pair<int, int> Extract_Min(vector<pair<int, int>>& Q_m)
{
	int minn = INF, x = 0; 
	pair<int, int> u;
	for (int i = 0; i < Q_m.size(); i++)
		if (Q_m[i].second < minn)
		{
			minn = Q_m[i].second;
			u = Q_m[i];
			x = i;
		}

	Q_m.erase(Q_m.begin() + x);
	return u;
}

// возращает вес ребра между этими вершинами
int w(int u, int v)
{
	for (int i = 0; i < g.size(); i++)
		if ((g[i].left == u && g[i].right == v) || (g[i].left == v && g[i].right == u))
			return g[i].weight;
}

//вернет номер вершины в векторе
int Find(vector<pair<int, int>> Q_m, int r)
{
	for (int i = 0; i < Q_m.size(); i++)
		if (Q_m[i].first == r)
			return i;
}

bool inQueue(vector<pair<int, int>> Q, int v)
{
	for (int i = 0; i < Q.size(); i++)
		if (Q[i].first == v)
			return true;

	return false;
}

void MST_Prim(int r)
{
	//<вершина, приоритет(расстояние до остовного дерева)//
	vector<pair<int, int>> Q;
	
	//изначально расстояние до всех вершин бесконечность
	for (int u = 0; u < Num; u++)
		Q.push_back(make_pair(u, INF));

	parent[Find(Q, r)] = -1;//для начальной вершины говорим, что ее родителя нет
	Q[Find(Q, r)].second = 0; //вес до самой себя 0

	while (!Q.empty())
	{
		pair<int, int> u = Extract_Min(Q);//забрали вершину с минимальным значением 

		if (inMST[u.first])//если вершина уже в дереве, не смотрим, ищем дальше 
			continue;

		inMST[u.first] = true;

		for(int i=0;i<v[u.first].size();i++)
		{
			//если эта смежная вершина есть еще в нашем списке + вес ребра между ними меньше, чем текущий "вес" смежной вершины
			if (inQueue(Q, v[u.first][i]) && w(u.first, v[u.first][i]) < Q[Find(Q, v[u.first][i])].second) 
			{
				parent[v[u.first][i]] = u.first;//меняем родителя
				Q[Find(Q, v[u.first][i])].second = w(u.first, v[u.first][i]);//меняем вес на меньший
			}
		}
	}
}

void MST()
{
	parent = new int[Num];

	for (int i = 0; i < Num; i++)
		inMST.push_back(false);//все не в MST

	for (int i = 0; i < Num; i++)
		if (!inMST[i]) //пока все вершины не в MST
			MST_Prim(i);

	ofstream out; out.open("out.txt");
	out << "Вершина - ее родитель: вес между ними \n";
	cout << "\n Вершина - ее родитель: вес между ними \n";
	for (int i = 0; i < Num; i++)
	{
		if (parent[i] != -1)
		{
			out << i << " - " << parent[i] << " : " << w(i, parent[i]) << endl;
			cout << i << " - " << parent[i] << " : " << w(i, parent[i]) << endl;
		}
		else
		{
			out << i << " - начало" << endl;
			cout << i << " - начало" << endl;
		}
	}

	delete[] parent;
}

int main()
{
	setlocale(LC_ALL, "Rus");
	Read();
	MST();
	return 0;
}