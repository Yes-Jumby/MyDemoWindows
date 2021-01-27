#include <iostream>
#include <String>

using namespace std;

// ����
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
		cout << this->name << endl; // 1���ڱ����ܹ�������Ĺ������ݳ�Ա
		cout << this->age << endl;  // 1���ڱ����ܹ�������ı������ݳ�Ա
		cout << this->sex << endl;  // 1���ڱ����ܹ��������˽�����ݳ�Ա
		showpublic();
		showprotected();
		showprivate();
	}
};

// ������ - public�̳�
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
		cout << this->name << endl; // 2��public�̳У������������ܹ����ʻ���Ĺ������ݳ�Ա
		cout << this->age << endl;  // 2��public�̳У������������ܹ����ʻ���ı������ݳ�Ա
									//cout << this->sex << endl;  // error:2����c���в��ܷ��ʻ����˽�����ݳ�Ա
		showpublic();
		showprotected();
		//showprivate();
	}
};

// ������ - protected�̳�
class protected_Sub : protected student
{
public:
	void show()
	{
		cout << this->name << endl; // 3��protected�̳У������������ܹ����ʻ���Ĺ������ݳ�Ա
		cout << this->age << endl;  // 3��protected�̳У������������ܹ����ʻ���ı������ݳ�Ա
									//cout << this->sex << endl;  // error:3�����������в��ܷ��ʻ����˽�����ݳ�Ա
		showpublic();
		showprotected();
		//showprivate();
	}
};

// ������ - private�̳�
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
		cout << this->name << endl; // 2��public�̳У������������ܹ����ʻ���Ĺ������ݳ�Ա
		cout << this->age << endl;  // 2��public�̳У������������ܹ����ʻ���ı������ݳ�Ա
									//cout << this->sex << endl;  // error:2����c���в��ܷ��ʻ����˽�����ݳ�Ա
		showpublic();
		showprotected();
		//showprivate();
	}
};

int main()
{
	student stu;
	cout << stu.name << endl;   // 5����������Է�����Ĺ������ݳ�Ա
								//cout << stu.age << endl;    // error,5�������ⲻ�ܷ�����ı������ݳ�Ա
								//cout << stu.sex << endl;    // error,5�������ⲻ�ܷ������˽�����ݳ�Ա
	private_Sub sub;
	sub.show();
	return 0;
}