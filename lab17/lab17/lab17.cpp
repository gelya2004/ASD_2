#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

float weight(vector<float> basket)
{
	float count = 0;
	for (int i = 0; i < basket.size(); i++)
		count += basket[i];
	return count;
}

int main()
{
	setlocale(LC_ALL, "Rus");
	cout << "Какой вес ящиков? ";
	int W;	cin >> W;

	cout << "Сколько вещей? ";
	int count;	cin >> count;

	

	cout << "Вводите вес передметов. \n";
	vector <float> things;
	float a; 
	while (things.size() < count)
	{
		cin >> a;
		if (a < 0)
		{
			cout << "Отрицательный вес!!! :(";
			exit(1);
		}
		things.push_back(a);
	}

	for (int i = 0; i < things.size(); i++)
	{
		if (things[i] > W)
		{
			things.erase(things.begin() + i);
			i--;
		}
	}
		

	vector<vector<float>> baskets;

	while (!things.empty())
	{
		for (int i = 0; i < things.size(); i++)
		{
			vector<float> basket;
			while (weight(basket) <= W)
			{
				if (weight(basket) + things[i] <= W)
				{
					basket.push_back(things[i]);
					things.erase(things.begin() + i);
					i--;
				}
				i++;
				if (i >= things.size())
					break;
			}
			baskets.push_back(basket);
			basket.clear();
		}
	}
	cout << "\n \nНужно " << baskets.size() << " ящиков \n";
	for (int i = 0; i < baskets.size(); i++)
	{
		cout << i + 1 << ":";
		for (int j=0;j<baskets[i].size();j++)
			cout << baskets[i][j] << " ";
		cout << endl;
	}
	return 0;
}