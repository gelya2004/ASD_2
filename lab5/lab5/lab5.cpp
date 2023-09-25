#include <iostream>
#include <vector>
#include <fstream>

using namespace std;
int Num = 0;
bool* visit=new bool[Num];//массив для каждой вершины(посетили ее или нет)
vector<int>* v;//списки смежности для начальных ребер
vector<int>* v1;//списки смежности для инвертированных ребер
vector<int> t;//тут хранится время выхода каждой вершины

void Read()
{
	//счаитли матрицу, посчитав сколько вершин
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

	//обнулили время каждоый вершины
	for (int i = 0; i < Num; i++)
		t.push_back(0);

	//еще раз считали матрицу смежности,но теперь заполняем списки смежности
	in.open("matrix.txt");
	v = new vector <int>[Num];
	for (int i = 0; i < Num; i++)
		for (int j = 0; j < Num; j++)
		{
			in >> element;
			if (element == 1)
				v[i].push_back(j);
		}
	in.close();

	cout << "\n Вершина: смежные с ней \n";
	for (int i = 0; i < Num; i++)
	{
		cout << i << ": "; 
		for (int j=0;j < v[i].size();j++)
			cout << v[i][j] << " ";
		cout << endl;
	}
}

//поиск в глубину
void Find(int u, int &time)
{
	visit[u] = true;
	t[u] = ++time;

	for (int i=0;i<v[u].size();i++)
		if (!visit[v[u][i]])
			Find(v[u][i], time);

	t[u] = time++;
}

// #1 этап. Обычный поиск в глубину с запоминанием времени выхода
void DFS()
{
	int time = 0;
	for (int u = 0; u < Num; u++)
		visit[u] = false;

	for (int u = 0; u < Num; u++)
		if (!visit[u])
			Find(u, time);

	cout << "\n #1 этап. Поиск в глубину: \n Вершина: время выхода \n";
	for (int i = 0; i < Num; i++)
		cout << i << ": " << t.at(i) << endl;
	cout << endl;
}

// #2 этап. Инвертируем ребра
void Invers()
{
	cout << "\n #2 этап. Инвертируем ребра \n";
	v1 = new vector<int>[Num];

	//создали вспомогательную матрицу
	int** mas = new int* [Num];
	for (int i = 0; i < Num; i++)
		mas[i] = new int[Num];

	//считываем теперь матрицу как транспонированную
	int element;
	ifstream in; in.open("matrix.txt");
	for (int i = 0; i < Num; i++)
		for (int j = 0; j < Num; j++)
			in >> mas[j][i];
	in.close();

	//проходимся по новой матрице и заполняем новые списки смежности
	for (int i = 0; i < Num; i++)
		for (int j = 0; j < Num; j++)
			if (mas[i][j] == 1)
				v1[i].push_back(j);

	cout << "\n Вершина: смежные с ней \n";
	for (int i = 0; i < Num; i++)
	{
		cout << i << ": "; 
		for (int j = 0; j < v1[i].size(); j++)
			cout << v1[i][j] << " ";
		cout << endl;
	}

	//подчищаем за собой
	for (int i = 0; i < Num; i++)
		delete[] mas[i];
	delete[] mas;
}

//для поиска максимального элемента в векторе
int MAXX(vector<int> mas)
{
	int maxs = -1;
	for (int i = 0; i < mas.size(); i++)
		if (mas[i] > maxs)
			maxs = mas[i];
	return maxs;
}

//поиск в глубину (учитывая время по убыванию)
void Find_for_DFSwM(int u, vector<int>* Q_m)
{
	visit[u] = true;
	for(int i=0;i<v1[u].size();i++)
		if (!visit[v1[u][i]])
			Find_for_DFSwM(v1[u][i], Q_m);
	Q_m->push_back(u);

	t[u] = 0;//вершину обработали, время обнулили
}

// #3 этап. Теперь запускаем поиск в глубину, учитывая время выхода (идем по его убыванию)
void DFS_with_max()
{
	cout << "\n #3 этап. Поиск в глубину, учитывая время выхода (идем по его убыванию) \n";
	vector<vector<int>> Q; //тут хранятся сильно связанные компоненты
	for (int u = 0; u < Num; u++)
		visit[u] = false;

	vector<int> time_queue;

	for (int i = 0; i < Num; i++)
		for (int u = 0; u < Num; u++)
		{
			if (!visit[u] && t.at(u) == MAXX(t))
				Find_for_DFSwM(u, &time_queue);

			Q.push_back(time_queue);
			time_queue.clear();
		}

	ofstream out; out.open("out.txt");
	out << "Сильно связанные компоненты: \n";
	cout << "Сильно связанные компоненты: \n";
	for (int i = 0; i < Q.size(); i++)
	{
		if (!Q[i].empty()) {
			for (int j = 0; j < Q[i].size(); j++)
			{
				out << Q[i][j] << " ";
				cout << Q[i][j] << " ";
			}		
			out << endl;
			cout << endl;
		}
	}
}


void Strongly_coupled_components()
{
	cout << "\n Запускаем метод Касарайю \n";
	DFS();
	Invers();
	DFS_with_max();
}

int main()
{
	setlocale(LC_ALL, "Rus");

	Read();
	Strongly_coupled_components();

	return 0;
}
