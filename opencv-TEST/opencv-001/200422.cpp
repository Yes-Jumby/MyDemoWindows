#include <iostream>
#include <cstring>
#define N 100
using namespace std;
int num = 1;
void permutation(string a, int k, int m)//È«ÅÅÁĞ
{
	cout <<"Sort:======="<< num<< a[0] << a[1] << a[2]<<endl;
	num++;
	int i, j;
		
	if (k == m)//µİ¹é»ù
	{
		for (i = 0; i <= m; i++)
			cout << a[i];
		cout << endl;
	}
	else
	{
		for (j = k; j <= m; j++)
		{
			swap(a[j], a[k]);
			permutation(a, k + 1, m);
			swap(a[j], a[k]);
		}
	}
}

int main0422()
{
	//char sArr[7] = "ILOVEC";
	//char tArr[7] = "565655";
	//memcpy(tArr, sArr, 5);
	//cout << tArr << endl;
	int n;
	string str = "123";
	n = str.size() - 1;
	permutation(str, 0, n);
	return 0;
}
