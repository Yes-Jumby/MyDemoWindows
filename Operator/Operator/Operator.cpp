// Operator.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include<iostream>
#include<string>
using namespace std;

class Data
{
private:
    int data;
public:
    Data() { cout << "constructor" << endl; };
    ~Data() { cout << "destructor" << endl; };

    Data(int _data)
        :data(_data)
    {
        cout << "constructor int" << endl;
    }

    Data(const Data& str)
    {
        cout << "copy constructor int" << endl;
        data = str.data;
    }

    Data& operator=(const Data &_data)
    {
        cout << "operator=(const Data &_data)" << endl;
        if (this != &_data)
        {
            this->data = _data.data;
        }
        return *this;
    }
    Data& operator=(const int &_data)
    {
        cout << "operator=(const int &_data)" << endl;
        data = _data;
        return *this;
    }
    Data operator+(const Data &_data)
    {
        cout << "operator+(const Data &_data)" << endl;
        Data data_0 = this->data + _data.data;
        //data_0.data = this->data + _data.data;
        cout << data_0.data << endl;

        return data_0;
    }
    Data operator-(const Data &_data)
    {
        cout << "operator-(const Data &_data)" << endl;
        Data data_0 = this->data - _data.data;
        cout << data_0.data << endl;

        return data_0;
    }
    //Data& operator+(const Data &_data)
    //{
    //    cout << "operator+(const Data &_data)" << endl;
    //    this->data = this->data + _data.data;
    //    //data_0.data = this->data + _data.data;
    //    cout << this->data << endl;

    //    return *this;
    //}
    //Data& operator-(const Data &_data)
    //{
    //    cout << "operator+(const Data &_data)" << endl;
    //    this->data = this->data - _data.data;
    //    //data_0.data = this->data + _data.data;
    //    cout << this->data << endl;

    //    return *this;
    //}
    //Data operator+(const Data &_data)
    //{
    //    cout << "operator+(const Data &_data)" << endl;
    //    Data data_0 = this->data + _data.data;
    //    //data_0.data = this->data + _data.data;
    //    cout << data_0.data << endl;

    //    return data_0;
    //}
    //Data& operator-(const Data &_data)
    //{
    //    cout << "operator+(const Data &_data)" << endl;
    //    this->data = this->data - _data.data;
    //    //data_0.data = this->data + _data.data;
    //    cout << this->data << endl;

    //    return *this;
    //}
};
void fun1(Data a)
{
    cout << "fun1" << endl;
}
Data fun2()
{
    cout << "fun2" << endl;
    Data data(0);
    return data;
}
int main()
{
    Data data1 = 1;
    Data data2, data3,data4,data5;
    cout << "=====================" << endl;
    data2 = 1;
    cout << "=====================" << endl;
    data3 = data2;
    cout << "=====================" << endl;
    cout << "=====================" << endl;
    data4 = data3 + data2;
    cout << "=====================" << endl;
    cout << "=====================" << endl;
    data5 = data4 - data3;
    cout << "=====================" << endl;
    cout << "=====================" << endl;
    fun1(data4);
    cout << "=====================" << endl;
    cout << "=====================" << endl;
    fun2();
    
    return 0;
}
