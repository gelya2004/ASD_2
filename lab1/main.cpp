#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

struct Point
{
	int x, y;
};

int rotate(Point A, Point B, Point C)
{
	return (B.y - A.y)*(C.x - B.x)  - (B.x - A.x)*(C.y - B.y);
}

void write(vector<Point> mas, int n)
{
	for (int i = 0; i < n; i++)
		cout <<  " (" << mas[i].x << " ; " << mas[i].y << ")" << endl;
	cout << endl;
}

void Low_Point(vector<Point> &mas)
{
	for (int i = 0; i < mas.size(); i++)
	{
		if (mas[i].y < mas[0].y)
			swap(mas[i], mas[0]);
		else if (mas[i].y == mas[0].y)
		{
			if (mas[i].x < mas[0].x)
				swap(mas[i], mas[0]);
			else
				continue;
		}
	}
	cout << "Low: \n";
	write(mas, mas.size());
}

void Sort(vector<Point>& mas)
{
	int j = 0;
	for (int i = 2; i < mas.size(); i++)
	{
		j = i;
		while (j > 1 && (rotate(mas[0], mas[j - 1], mas[j]) < rotate(mas[0], mas[j-2], mas[j-1])))
		{
			swap(mas[j-1], mas[j]);-
			j--;		
		}
	}
	cout << "Sort1: \n";
	write(mas, mas.size());
}

void Delete_extra(vector<Point>& mas)
{
	for (int i = 3; i < mas.size(); i++)
		if ((rotate(mas[i - 2], mas[i - 1], mas[i]) < 0) || (rotate(mas[i - 2], mas[i - 1], mas[i]) == 0))
		{
			mas.erase(mas.cbegin() + (i - 1));
			i--;
		}
	cout << "Itog: \n";
	write(mas, mas.size());
}

void ConvexHull(vector<Point>& mas)
{
	cout << "Data: \n";
	write(mas, mas.size());
	Low_Point(mas);
	Sort(mas);
	Delete_extra(mas);
}

int main()
{
	vector<Point> mas = { {0,3},{1,1},{0,0},{1,2},{5,5},{2,2},{3,1},{3,3},{-5,-5 },{-5,5},{5,-5} };
	ConvexHull(mas);

	return 0;
}
