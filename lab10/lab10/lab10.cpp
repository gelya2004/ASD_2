#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <fstream>
#include <stack>

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

int Num = 0; // кол-во вершин
vector<Edge> g; // вектор ребер
int* deg; // массив, хранящий степени вершин

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

	deg = new int[Num];
	for (int i = 0; i < Num; i++)
		deg[i] = 0;

	in.open("matrix.txt");
	for (int i = 0; i < Num; i++)
		for (int j = 0; j < Num; j++)
		{
			in >> element;
			if (element != 0)
			{
				g.push_back(Edge(i, j, element));
				deg[i] += 1;
			}
		}
	
	in.close();
}

int CheckForEuler()
{
	int count = 0;
	for (int i = 0; i < Num; i++)
		if (deg[i] % 2 == 1)
			count++;

	return count;
}

bool FindE(int w, int u)
{
	for (int i = 0; i < g.size(); i++)
	{
		if (g[i].left == w && g[i].right == u)
			return true;
		else if (g[i].right == w && g[i].left == u)
			return true;
	}

	return false;
}
void DelE(int w, int u)
{
	for (int i = 0; i < g.size(); i++)
	{
		if (g[i].left == w && g[i].right == u)
		{
			g.erase(g.cbegin() + i);
			i--;
		}
		else if (g[i].left == u && g[i].right == w)
		{
			g.erase(g.cbegin() + i);
			i--;
		}
	}
}

void EulerPath(int a)
{
	ofstream out; out.open("out.txt");
	//если есть вершина с нечетной степени, начнем с нее
	for (int i = 0; i < Num; i++)
		if (deg[i] % 2 == 1)
		{
			a = i;
			break;
		}
	stack<int>S;
	S.push(a);//закинули начальную вершину
	bool found_edge; 
	int w = -1;//временная переменная для вершины
	while (!S.empty())
	{
		w = S.top();
		found_edge = false;
		for (int u = 0; u < Num; u++)
			if (FindE(w, u))//нашли ребро с нашей вершиной и ее смежной
			{
				S.push(u);//добавили смежную вершмну в наш стек
				DelE(w, u);//удаляем ребро, которое нашли
				found_edge = true; //говорим, что нашли ребро
				break;
			}

		if (!found_edge) //если не нашли ребер, то выводим нашу вершину(ее обработали)
		{
			S.pop();
			cout << w << " ";
			out << w << " ";
		}
	}
	out.close();
}

int main()
{
	setlocale(LC_ALL, "Rus");
	Read();
	if (CheckForEuler()==0 || CheckForEuler() == 2)
		EulerPath(0);
	else
		cout << "Not Euler!";
	return 0;
}