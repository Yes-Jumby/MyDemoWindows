// ��̬.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "��̬.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Ψһ��Ӧ�ó������

CWinApp theApp;

using namespace std;




class A
{
public:
	virtual void out1() = 0; //������ʵ�֣����麯��������ʵ��
	virtual ~A() {};
	virtual void out2() //Ĭ��ʵ�֣����������д�������麯����Ϊ�������û����ָ������������ĺ���
	{
		cout << "A(out2)" << endl;
	}
	void out3() //ǿ��ʵ�֣����಻Ӧ����д����
	{
		cout << "A(out3)" << endl;
	}
    void out5() //ǿ��ʵ�֣����಻Ӧ����д����
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
	//�Լ���ӵ�
	void out4()//�����п����и���û�еĺ���
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
//	virtual void makeSound() { cout << "����" << endl; }
//};
//
//class Dog : public Animal
//{
////public:
////	/*virtual */void makeSound() { cout << "����" << endl; }
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
