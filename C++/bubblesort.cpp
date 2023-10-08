#include <bits/stdc++.h>

using namespace std;

int main()
{
	int a[] = {5,1,45,78,14,23,54,89,1,2,44,5,86,4,2,3};
	int len = sizeof(a)/sizeof(a[0]), temp;
	for(int i = 0; i < len; i++)
	{
		for(int j = 0; j < len - i - 1; j++)
		{
			if(a[j] > a[j+1])
			{
				temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp;
			}
		}
		//after every pass
		cout << "Pass#" << i + 1 << " :";
		for(int i = 0; i < len; i++)
		{
			cout << a[i] << " ";
		}
		cout << endl;
	}
	return 0;
}