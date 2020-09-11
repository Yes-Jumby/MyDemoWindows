// 多态.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "多态.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 唯一的应用程序对象

CWinApp theApp;

using namespace std;




class A
{
public:
	virtual void out1() = 0; //由子类实现：纯虚函数由子类实现
	virtual ~A() {};
	virtual void out2() //默认实现：子类可以重写函数。虚函数是为了允许用基类的指针来调用子类的函数
	{
		cout << "A(out2)" << endl;
	}
	void out3() //强制实现：子类不应该重写函数
	{
		cout << "A(out3)" << endl;
	}
    void out5() //强制实现：子类不应该重写函数
    {
        cout << "A(out5)" << endl;
    }
};

class B :public A
{
public:
	virtual ~B() {};
	void out1()
	{
		cout << "B(out1)" << endl;
	}
	void out2()
	{
		cout << "B(out2)" << endl;
	}
	void out3()
	{
		cout << "B(out3)" << endl;
	}
	//自己添加的
	void out4()//子类中可以有父类没有的函数
	{
		cout << "B(out4)" << endl;
	}
}; 
int main() 
{ 
	A *ab=new B();
	ab->out1(); 
	ab->out2(); 
	ab->out3(); 
	((B*)ab)->out4();
	cout << "************************" << endl; 
	B *bb = new B();
	bb->out1(); 
	bb->out2(); 
	bb->out3(); 
	bb->out4();

    ((A*)bb)->out5();

	delete []ab; 
	delete []bb; 
    DWORD  dwTime = 3200000000;
    int a = sizeof(dwTime);
    printf("%u\n%lu\n", dwTime, dwTime);
    system("PAUSE");
	return 0; }

//class Animal
//{
//public:
//	virtual void makeSound() { cout << "声音" << endl; }
//};
//
//class Dog : public Animal
//{
////public:
////	/*virtual */void makeSound() { cout << "狗叫" << endl; }
//};
//
//int main()
//{
//	Animal animal;
//	animal.makeSound(); // rawr (1)
//
//	Dog dog;
//	dog.makeSound();  // bark (2)
//
//	Animal badDog = Dog();
//	badDog.makeSound();  // (3) rawr !!!!!!!!!!!!!!!!!!!
//
//	Animal* goodDog = new Dog();
//	goodDog->makeSound();  // bark (4)
//	system("PAUSE");
//	delete[]goodDog;
//	goodDog = nullptr;
//	return 0;
//}
//
