#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <queue>
using namespace std;
//�ṹ��
typedef struct node
{
    char data;
    struct node *lchild, *rchild;
}binary_tree, *tree;

//����һ���������ַ�0��Ϊ��
void creat_tree(tree &t)
{
    char ch;
    cin >> ch;
    if (ch == '0')
    {
        t = NULL;
    }
    else
    {
        t = new binary_tree;
        if (!t) exit(0); //���û�ɹ�����ռ� ���˳�
        t->data = ch;
        creat_tree(t->lchild);
        creat_tree(t->rchild);
    }
}
//��ӡ·�� ��Ҷ�ӽڵ㵽���ڵ����
bool printPath(tree &t, char data)
{
    if (t == NULL)
        return false;

    if (t->data == data || printPath(t->lchild, data) || printPath(t->rchild, data))
    {
        cout << t->data;   //·���ϵĽ���ʶ��ӡ����
        return true;
    }

    return false;
}
//������������
tree MirrorBintree(tree&t)
{
    if (t == nullptr) return t;
    tree pleft = MirrorBintree(t->lchild);
    tree pright = MirrorBintree(t->rchild);
    t->lchild = pright; t->rchild = pleft;
    return t;
}
//���·������ �Ӹ��ڵ㵽Ҷ�ӽڵ����
void printLeavesDepth(tree &t, vector<char> vec,size_t depth = 0)
{
    if (t == NULL) return;
    if (t->lchild == NULL && t->rchild == NULL)
    {
        vec.push_back(t->data);
        cout << t->data << ": " << depth << endl;
        copy(vec.begin(), vec.end(), ostream_iterator<char>(cout, " "));
        cout << endl;
    }
    else
    {
        vec.push_back(t->data);
        printLeavesDepth(t->lchild,vec,depth + 1);
        printLeavesDepth(t->rchild,vec,depth + 1);
    }
}
//���Ҷ�ӽ��ֵ
void DispLeaf(tree &t)
{
    if (t)
    {
        if (t->lchild == NULL&&t->rchild == NULL)
        {
            cout << t->data << "  ";
        }
        DispLeaf(t->lchild);
        DispLeaf(t->rchild);
    }
}
void preorderTraversal(tree &t)
{
    if (t == NULL)
        return;
    cout << t->data << " ";
    preorderTraversal(t->lchild);
    preorderTraversal(t->rchild);
    //cout << endl;
}

void inorderTraversal(tree &t)
{
    if (t == NULL)
        return;  
    inorderTraversal(t->lchild);
    cout << t->data << " ";
    inorderTraversal(t->rchild);
    //cout << endl;
}

void postorderTraversal(tree &t)
{
    if (t == NULL)
        return;
    postorderTraversal(t->lchild);
    postorderTraversal(t->rchild);
    cout << t->data << " ";
    //cout << endl;
}

vector<vector<char>> levelOrder(tree  &root) {
    vector<vector<char>> res;
    if (!root) return res;
    queue<tree> qu;
    qu.push(root);
    while (!qu.empty())
    {
        vector<char> tmp;
        int len = qu.size();
        for (int i = 0; i<len; i++) {
            tree node = qu.front();
            qu.pop();
            tmp.push_back(node->data);
            if (node->lchild) qu.push(node->lchild);
            if (node->rchild) qu.push(node->rchild);
        }
        res.push_back(tmp);
    }
    return res;
}

int main���ڵ�()
{
    int len1 = 2;
    int len2 = 1;
    vector<vector<int>> vecTor(len1, vector<int>(len2));
    tree t;
    vector<char> vecVector;
    cout << "������������ڵ㣺����������:ab00c00��";
    creat_tree(t);
    cout << "���Ҷ�ӽ��" << endl;
    DispLeaf(t);
    cout << endl;
    cout << "����Ҷ�ӽ�㵽������·������" << endl;
    printLeavesDepth(t, vecVector, 0);

    //Ҷ�ӵ���
    printPath(t, 'd');
    cout << endl;
    preorderTraversal(t);
    cout << endl;
    inorderTraversal(t);
    cout << endl;
    postorderTraversal(t);
    cout << endl;
    cout << endl;
    
    cout << endl;
    vector<vector<char>> levelTravel = levelOrder(t);
    system("pause");
    return 0;
}