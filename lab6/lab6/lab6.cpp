#include <iostream>
#include <string>
#include <vector>
#include <fstream>

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
bool* visit;
vector<int>* v;//списки смежности
vector<Edge> g;//вектор <левая, правая, вес>
int* parent;//массив множеств

void Quick_Sort(int low, int high, vector<Edge>& x)
{
	if (low >= high)
	{
		return;
	}
	int m = (low + high) / 2 + 1;
	int k = x[m].weight;
	int l = low - 1;
	int r = high + 1;
	while (1)
	{
		do
		{
			l++;
		} while (x[l].weight < k);
		do
		{
			r--;
		} while (x[r].weight > k);
		if (l >= r)
		{
			break;
		}
		swap(x[l], x[r]);
	}
	r = l;
	l--;
	Quick_Sort(low, l, x);
	Quick_Sort(r, high, x);
}
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
	if (!in)
		exit(1);
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

	cout << "\nВершина: смежные с ней \n";
	for (int i = 0; i < Num; i++)
	{
		cout << i << ": "; 
		for (int j = 0; j < v[i].size(); j++)
			cout << v[i][j] << " ";
		cout << endl;
	}

	cout << "\n <Левая вершина, правая вершина : длина ребра> \n";
	for (int i=0;i<g.size();i++)
		cout << "<" << g[i].left << ", " << g[i].right << " : " << g[i].weight << ">" << endl;
}

//поиск множества данной вершины
int Find_Set(int i)
{
	if (parent[i] == i)
		return i;
	else
		return Find_Set(parent[i]);
}

//объединение множества (мн-во вершины u теперь будет равно мн-ву вершины v)
void Union(int u, int v)
{
	parent[u] = parent[v];
}

void MST_Kruskal()
{
	parent = new int[Num];	
	vector<Edge> MST; //место хранения нашего минимально остовного дерева
	for (int i = 0; i < Num; i++)
		parent[i] = i;
	//отсортировали по весу ребра (по возрастанию)
	Quick_Sort(0, g.size() - 1, g);
	 
	//проверяем, если две смежные вершины не в одном мн-ве, то добавляем + обновление мн-ва
	for (int i = 0; i < g.size(); i++)
		if (Find_Set(g[i].left) != Find_Set(g[i].right))
		{
			MST.push_back(g[i]);
			Union(Find_Set(g[i].left), Find_Set(g[i].right));
		}

	ofstream out; out.open("out.txt");
	cout << "\n Минимальное остновное дерево: \n";
	out << "\n Пара вершин : вес ребра \n";
	cout << "\n Пара вершин : вес ребра \n";
	for (int i = 0; i < MST.size(); i++)
	{
		out << i + 1 << ". " << MST[i].left << " - " << MST[i].right << " : " << MST[i].weight << "\n";
		cout << i + 1 << ". " << MST[i].left << " - " << MST[i].right << " : " << MST[i].weight << "\n";
	}
}

int main()
{
	setlocale(LC_ALL, "Rus");
	Read();
	MST_Kruskal();
	return 0;
}

//
//0 2 0 1 3 0 2 0 0
//2 0 0 0 3 0 0 5 0
//0 0 0 0 0 1 0 0 2
//1 0 0 0 0 0 3 0 0
//3 3 0 0 0 0 4 4 0
//0 0 1 0 0 0 0 0 2
//2 0 0 3 4 0 0 0 0
//0 5 0 0 4 0 0 0 0
//0 0 2 0 0 2 0 0 0