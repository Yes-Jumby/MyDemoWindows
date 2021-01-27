#include <iostream>
#include <String>

using namespace std;

// 基类
class student
{
public:
	string name;
	void showpublic()
	{
		cout << "public" << endl;
	}
protected:
	int age;
	void showprotected()
	{
		cout << "protected" << endl;
	}
private:
	char sex;
	void showprivate()
	{
		cout << "private" << endl;
	}

public:
	void showStu()
	{
		cout << this->name << endl; // 1、在本类能够访问类的公有数据成员
		cout << this->age << endl;  // 1、在本类能够访问类的保护数据成员
		cout << this->sex << endl;  // 1、在本类能够访问类的私有数据成员
		showpublic();
		showprotected();
		showprivate();
	}
};

// 派生类 - public继承
class public_Sub : public student
{
public:
	void show()
	{
		show1();
	}
protected:
	void show1()
	{
		cout << this->name << endl; // 2、public继承，在派生类中能够访问基类的公有数据成员
		cout << this->age << endl;  // 2、public继承，在派生类中能够访问基类的保护数据成员
									//cout << this->sex << endl;  // error:2、在c类中不能访问基类的私有数据成员
		showpublic();
		showprotected();
		//showprivate();
	}
};

// 派生类 - protected继承
class protected_Sub : protected student
{
public:
	void show()
	{
		cout << this->name << endl; // 3、protected继承，在派生类中能够访问基类的公有数据成员
		cout << this->age << endl;  // 3、protected继承，在派生类中能够访问基类的保护数据成员
									//cout << this->sex << endl;  // error:3、在派生类中不能访问基类的私有数据成员
		showpublic();
		showprotected();
		//showprivate();
	}
};

// 派生类 - private继承
class private_Sub : private student
{
public:
	void show()
	{
		show1();
	}
private:
	void show1()
	{
		cout << this->name << endl; // 2、public继承，在派生类中能够访问基类的公有数据成员
		cout << this->age << endl;  // 2、public继承，在派生类中能够访问基类的保护数据成员
									//cout << this->sex << endl;  // error:2、在c类中不能访问基类的私有数据成员
		showpublic();
		showprotected();
		//showprivate();
	}
};

int main()
{
	student stu;
	cout << stu.name << endl;   // 5、在类外可以访问类的公有数据成员
								//cout << stu.age << endl;    // error,5、在类外不能访问类的保护数据成员
								//cout << stu.sex << endl;    // error,5、在类外不能访问类的私有数据成员
	private_Sub sub;
	sub.show();
	return 0;
}