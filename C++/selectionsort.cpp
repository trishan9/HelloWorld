#include <bits/stdc++.h>
using namespace std;

int main()
{
	int a[] = {5,1,45,78,14,23,54,89,1,2,44,5,86,4,2,3};
	int len = sizeof(a)/sizeof(a[0]), temp, min = a[0], pos;
	for(int i = 0; i < len; i++)
	{	
		pos = i;
		for(int j = i; j < len; j++)
		{
			if(a[j] < a[pos])
			{
				pos = j;
			}
		}
		temp = a[i];
		a[i] = a[pos];
		a[pos] = temp;
	}
	for(int i = 0; i < len; i++)
	{
		cout << a[i] << " ";
	}
	return 0;
}
