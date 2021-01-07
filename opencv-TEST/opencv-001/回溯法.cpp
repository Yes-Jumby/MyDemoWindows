#include <iostream>       // std::cout
#include <stack>          // std::stack
#include <vector>
using namespace std;
struct Queen
{ //皇后类
	int x, y; //皇后在棋盘上的位置坐标
	Queen(int xx = 0, int yy = 0) : x(xx), y(yy) {};
	bool operator==(Queen const& q) const
	{ //重载判等操作符，以检测不同皁后之间可能的冲突
		return (x == q.x) //行冲突（这一情况其实并不会发生，可省略）
			|| (y == q.y) //列冲突
			|| (x + y == q.x + q.y) //沿正对角线冲突
			|| (x - y == q.x - q.y); //沿反对角线冲突
	}
	bool operator!=(Queen const& q) const { return !(*this == q); } //重载不等操作符
};

template <class T>
class Stack
{//类模板，实现对任意类型数据进行存取
public://成员函数用来操作数据成员
	Stack()//构造函数
	{};
	void push(const T &x)//存入数据函数
	{
		_stack.push_back(x);
	};
	size_t size()
	{
		return _stack.size();
	};
	T &pop()
	{
		T t = _stack.back();
		_stack.pop_back();
		return t;
	};
	bool find(T &t)
	{
		for (int i = 0; i < _stack.size(); i++)
		{
			if (t == _stack.at(i))
			{
				return true;
			}
		}
		return false;
	};
	void printf()
	{
		cout << "****************解决方法****************" << endl;
		for (int i = 0; i < _stack.size(); i++)
		{
			cout << "X" << _stack.at(i).x << "Y" << _stack.at(i).y << endl;
		}
	};
private:
	vector<T> _stack;//item用于存放任意类型的数据

};

void placeQueens(int N)
{
	int nSolu = 0;
	//N皇后算法（迭代版）：采用试探/回溯的策略，借助栈记录查找的结果
	Stack<Queen> solu; //存放（部分）解的栈
	Queen q(0, 0); //从原点位置出发
	do
	{ //反复试探、回溯
		if (N <= solu.size() || N <= q.x)
		{
			//若已出界，则
			q = solu.pop();
			q.x++; //回溯一行，幵继续试探下一列
		}
		else
		{
			//否则，试探下一行    【放不在那里】
			while ((q.x < N) && (solu.find(q))) //通过与已有皇后的比对
			{
				//尝试找到可摆放下一皇后的列
				q.x++;
			}
			if (N > q.x)
			{ //若存在可摆放的列，则
				solu.push(q); //摆上当前皇后，并
				if (N <= solu.size())
				{
					solu.printf();
					nSolu++; //若部分解已成为全局解，则通过全局变量nSolu计数
				}


				q.y++;
				q.x = 0; //转入下一行，从第0列开始，试探下一皁后
			}
		}
	} while ((0 < q.y) || (q.x < N)); //所有分支均已穷举或剪枝之后，算法结束
	cout << "count :" << nSolu << endl;
	return;
}
class Solution {
public:
    struct Queen
    {
        int x, y;
        Queen(int xx = 0, int yy = 0) : x(xx), y(yy) {};
        bool operator==(Queen const& q) const
        {
            return (x == q.x)
                || (y == q.y)
                || (x + y == q.x + q.y)
                || (x - y == q.x - q.y);
        }
        bool operator!=(Queen const& q) const { return !(*this == q); }
    };

    template <class T>
    class Stack
    {
    public:
        Stack()
        {};
        void push(const T &x)
        {
            _stack.push_back(x);
        };
        size_t size()
        {
            return _stack.size();
        };
        T &pop()
        {
            T t = _stack.back();
            _stack.pop_back();
            return t;
        };
        bool find(T &t)
        {
            for (int i = 0; i < _stack.size(); i++)
            {
                if (t == _stack.at(i))
                {
                    return true;
                }
            }
            return false;
        };
        void printf()
        {
            for (int i = 0; i < _stack.size(); i++)
            {
                //cout << "X" << _stack.at(i).x << "Y" << _stack.at(i).y << endl;
            }
        };
    private:
        vector<T> _stack;

    };

    int Nqueen(int N)
    {
        int nSolu = 0;
        Stack<Queen> solu;
        Queen q(0, 0);
        do
        {
            if (N <= solu.size() || N <= q.x)
            {
                q = solu.pop();
                q.x++;
            }
            else
            {
                while ((q.x < N) && (solu.find(q)))
                {
                    q.x++;
                }
                if (N > q.x)
                {
                    solu.push(q);
                    if (N <= solu.size())
                    {
                        //solu.printf();
                        nSolu++;
                    }
                    q.y++;
                    q.x = 0;
                }
            }
        } while ((0 < q.y) || (q.x < N));
        return nSolu;
    }
};
int main3233223()
{
	placeQueens(8);
    Solution mySolution;
    cout << mySolution.Nqueen(9);
	system("PAUSE");
	return 0;
}
