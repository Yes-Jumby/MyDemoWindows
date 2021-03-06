#include <vector>
#include <iostream>

int main0529()
{
	using namespace std;
	vector<int> v1, v2, v3;
	vector<int>::iterator iter;

	v1.push_back(10);
	v1.push_back(20);
	v1.push_back(30);
	v1.push_back(40);
	v1.push_back(50);
	v2.push_back(1);
	v2.push_back(2);

	cout << "v1 = ";
	for (iter = v1.begin(); iter != v1.end(); iter++)
		cout << *iter << " ";
	cout << endl;

	cout << "v2 = ";
	for (iter = v2.begin(); iter != v2.end(); iter++)
		cout << *iter << " ";
	cout << endl;

	v2 = v1;
	//cout << "v2 = ";
	//for (iter = v2.begin(); iter != v2.end(); iter++)
	//	cout << *iter << " ";
	//cout << endl;

	v2.assign(v1.begin(), v1.end());
	cout << "v2 = ";
	for (iter = v2.begin(); iter != v2.end(); iter++)
		cout << *iter << " ";
	cout << endl;

	int aaa[2] = { 1001,1001 };
	v2.assign(aaa, aaa+2);
	cout << "v2 = ";
	for (iter = v2.begin(); iter != v2.end(); iter++)
		cout << *iter << " ";
	cout << endl;

	v3.assign(7, 3);
	cout << "v3 = ";
	for (iter = v3.begin(); iter != v3.end(); iter++)
		cout << *iter << " ";
	cout << endl;

	return 0;
}