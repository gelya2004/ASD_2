#include <iostream>
#include <vector>
using namespace std;

void Quick_Sort(int low, int high, vector<int> &x)
{
	if (low >= high)
	{
		return;
	}
	int m = (low + high) / 2 + 1;
	int k = x[m];
	int l = low - 1;
	int r = high + 1;
	while (1)
	{
		do
		{
			l++;
		} while (x[l] < k);
		do
		{
			r--;
		} while (x[r] > k);
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
bool SummSubb(vector<int> numbers, int sum)
{
	int i = 0, s=0;
	vector<int>summ;
	start:
	if (s + numbers[i] <= sum)
	{
		s += numbers[i];
		summ.push_back(numbers[i]);
		i++;
		
		if (i < numbers.size())
		{
			goto start;
		}
	}

	if (s == sum)
	{ 
		cout << "\n Sum is found! \n Sum:\n";
		for (int i : summ)
			cout << i << " ";
		return true;
	}
	else
	{
		cout << "\n Oh no :( \n";
		return false;
	}
}
int main()
{
	cout << "Sum?  ";
	int sum; cin >> sum;
	cout << "How many numbers? ";
	int count; cin >> count;
	if (count < 1)
		exit(1);
	vector<int>numbers;
	int a;
	while(numbers.size() < count)
	{
		cin >> a;
		numbers.push_back(a);
	}
	for(auto i: numbers)
		cout << i << " ";
	Quick_Sort(0, numbers.size()-1, numbers);
	SummSubb(numbers, sum);
	return 0;
}