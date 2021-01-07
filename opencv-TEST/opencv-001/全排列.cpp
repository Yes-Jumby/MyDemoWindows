#include <iostream>
#include <cstring>
#include <set>
#include <vector>
#include<algorithm>
#define N 100
using namespace std;
int num = 1;
void permutation(string a, int k, int m)//全排列 k start  m end
{
	cout <<"Sort:======="<< num<< a[0] << a[1] << a[2]<<endl;
	num++;
	int i, j;
		
	if (k == m)//递归基
	{
		for (i = 0; i <= m; i++)
			cout << a[i];
		cout << endl;
        return;
	}
	else
	{
        set<char> seen;
		for (j = k; j <= m; j++)
		{
            if (seen.count(a[j]) > 0)
            {
                continue;
            }
            seen.insert(a[j]);

			swap(a[j], a[k]);
			permutation(a, k + 1, m);
			swap(a[j], a[k]);
		}
	}
}

void combine_backtrack(int need_num, string a, int k, int m, vector<char> vecSelect, vector<bool>& used)//全排列
{
    //cout << "Sort:=======" << num << a[0] << a[1] << a[2] << endl;
    num++;
    int i, j;

    if (vecSelect.size() == need_num)//递归基
    {
        for (i = 0; i < need_num; i++)
            cout << vecSelect[i];

        //for (const char x : vecSelect)
        //    std::cout << ' ' << x;
        cout << endl;
        return;
    }
    else
    {
        for (j = k; j < m; j++)
        {
            if (j > 0 && a[j] == a[j - 1] && used[j - 1] == false)
            {
                continue;
            }
            vecSelect.push_back(a[j]);
            used[j] = true;
            combine_backtrack(need_num,a, k + 1, m,vecSelect,used);
            used[j] = false;
            vecSelect.pop_back();
        }
    }
}
class Solution {
private:
    vector<vector<int>> result;
    vector<int> path;
    void backtracking(vector<int>& nums, int startIndex, vector<bool>& used) {
        result.push_back(path);
        for (int i = startIndex; i < nums.size(); i++) {
            // used[i - 1] == true，说明同一树支candidates[i - 1]使用过
            // used[i - 1] == false，说明同一树层candidates[i - 1]使用过
            // 而我们要对同一树层使用过的元素进行跳过
            if (i > 0 && nums[i] == nums[i - 1] && used[i - 1] == false) {
                continue;
            }
            path.push_back(nums[i]);
            used[i] = true;
            backtracking(nums, i + 1, used);
            used[i] = false;
            path.pop_back();
        }
    }

public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        result.clear();
        path.clear();
        vector<bool> used(nums.size(), false);
        sort(nums.begin(), nums.end()); // 去重需要排序
        backtracking(nums, 0, used);
        return result;
    }
};
string solve(string str) {
    // write code here
    string mystr = str;
    int isize = str.size();
    if (isize == 0) return string();
    int istart = 0;
    int istop = isize - 1;
    char temp;
    while (istart<istop)
    {
        temp = mystr[istart];
        mystr[istart] = mystr[istop];
        mystr[istop] = temp;
        istart++ ;
        istop--;
    }
    return mystr;
}
int mainquanpailie()
{
    cout << solve("abcd").c_str() << endl;
    return 0;
	//char sArr[7] = "ILOVEC";
	//char tArr[7] = "565655";
	//memcpy(tArr, sArr, 5);
	//cout << tArr << endl;
	int n;
    cout << "permutation:" << endl;
	string str = "121";
	n = str.size() - 1;
	permutation(str, 0, n);
    cout << "combine_backtrack:" << endl;
    sort(str.begin(), str.end());
    vector<bool> used(str.size(), false);
    for (int i = 0; i <= n+1; i++)
    {
        cout << "combine_backtrack:"<< i << endl;
        vector<char> vecSelect;
        combine_backtrack(i, str, 0, n, vecSelect, used);
    }


    //Solution mySolution;
    //vector<int> nums;
    //nums.push_back(1);
    //nums.push_back(2);
    //nums.push_back(1);
    //vector<vector<int>> result = mySolution.subsetsWithDup(nums);

    //for (int i = 0; i < result.size(); i++)
    //{
    //    cout << "combine_backtrack:" << i << endl;
    //    for (int j = 0; j < result.at(i).size(); j++)
    //        cout << result[i][j];
    //    cout << endl;
    //}

	return 0;
}
