#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <fstream>

const int INF=1e11;
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

class Graph
{
public:
	Graph()
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
		d = new int[Num];
		v = new list<int>[Num];
	}
	void AddVers()
	{
		int element;
		ifstream in; in.open("matrix.txt");
		if (!in)
		{
			cout << "File! \n";
			exit(1);
		}
		else
		{
			for (int i = 0; i < Num; i++)
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
		
		cout << "\n Dano: \n";
		for (int i = 0; i < Num; i++)
		{
			cout << i << ": "; copy(v[i].begin(), v[i].end(),ostream_iterator<int>(cout, " "));
			cout << endl;
		}
	}
	void BellmanFord(int src)
	{
		for (int i = 0; i < Num; i++)
			d[i] = INF;
		d[src] = 0;

		for (int i = 0; i < Num-1; i++)
			for (int j = 0; j < g.size(); j++)
				if (d[g[j].left]!=INF && d[g[j].left] + g[j].weight < d[g[j].right])
					d[g[j].right] = d[g[j].left] + g[j].weight;

		
		for (int j = 0; j < g.size(); j++)
			if (d[g[j].left] != INF && d[g[j].left] + g[j].weight < d[g[j].right])
			{
				ofstream out; out.open("D:/GitKraken/Lab_works/4 semester/ASD/lab9/out.txt");
				cout << "Graph contains negative weight cycle";
				out << "Graph contains negative weight cycle";
				break;
			}
			else
			{
				ofstream out; out.open("D:/GitKraken/Lab_works/4 semester/ASD/lab9/out.txt");
				out << "V : length \n";
				for (int i = 0; i < Num; i++)
					out << i << " : " << d[i] << endl;
			}	
	}
	
private:
	int Num=0;
	list<int> *v;
	vector<Edge> g;
	int *d;
};

int main()
{
	Graph G;
	G.AddVers();
	G.BellmanFord(0);
	return 0;
}