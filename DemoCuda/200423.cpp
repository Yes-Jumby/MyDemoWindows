#include <vector>
#include <iterator>
#include <algorithm>
#include <iostream>
using namespace std;
int num1 = 1;
//多个数组进行组合
void show(vector<vector<int>> &ve, vector<int> &flag, int k)//多个数组进行组合
{
	cout << "Sort:=======" << ++num1 <<"========";
	//num++;
	copy(flag.begin(), flag.end(), ostream_iterator<int>(cout, " "));
	cout << endl;
	if (k < ve.size())
	{
		for (int i = 0; i < ve[k].size(); ++i)
		{
			flag.push_back(ve[k][i]);
			show(ve, flag, k + 1);
			flag.pop_back();
		}
	}
	if (flag.size() == ve.size())//递归基
	{
		//输出
		copy(flag.begin(), flag.end(), ostream_iterator<int>(cout, " "));
		cout << endl;

	}
}
//recursion
int mysum(vector<int> &flag,int index)
{
	cout << index << endl;
	if (index < 0)
	{
		return 0;
	}
	else
	{
		return flag[index]+mysum(flag, index-1);
	}
}
int main0423()
{

	////////////////////////////////////////
	//测试使用
	vector<vector<int>> ve1;
	ve1.resize(4);
	ve1[0].push_back(1);
	ve1[0].push_back(2);
	ve1[1].push_back(3);
	ve1[1].push_back(4);
	ve1[2].push_back(5);
	ve1[3].push_back(6);
	ve1[3].push_back(7);
	cout<< mysum(ve1[3],1)<<endl;
	vector<int> flag;
	show(ve1, flag, 0);
	return 0;
}
