#include <iostream>
#include <list>
#include <queue>
#include <fstream>
const int n = 8;
using namespace std;

void BFS(int s, int n)
{
	setlocale(LC_ALL, "Rus");
	list<int>* v=new list<int>[n];
	int element;
	ifstream in; in.open("matrix.txt");
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			in >> element;
			if (element == 1)
				v[i].push_back(j);
		}
	in.close();

	cout << "\n Дано: \n";
	for (int i = 0; i < n; i++)
	{
		cout << i << ": "; copy(v[i].begin(), v[i].end(), ostream_iterator<int>(cout, " "));
		cout << endl;
	}

	queue<int> Q; 
	bool* visit = new bool[n];
	int* d = new int[n];
	for (int u = 0; u < n; u++)
	{
		visit[u] = false;
		d[u] = -1;
	}
	d[s] = 0;
	visit[s] = true;
	Q.push(s);
	int u = 0;
	while (!Q.empty())
	{
		u = Q.front(); Q.pop();
		for (auto i = v[u].begin(); i != v[u].end(); i++)
			if (!visit[*i])
			{
				visit[*i] = true;
				d[*i] = d[u] + 1;
				Q.push(*i);
			}
	}
	ofstream out; out.open("out.txt");
	out << "Расстояние от " << s << endl;
	for (int i = 0; i < n; i++)
		out << i << ": " << d[i] << endl;

	out.close();

	delete[]v;
	delete[]d;
	delete[]visit;
}

int main()
{
	BFS(0, n);
	return 0;
}
