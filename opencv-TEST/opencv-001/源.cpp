#include <iostream>
#include "time.h"
#include "cv.hpp"
#include "cudaarithm.hpp"
#include "cudafilters.hpp"
using namespace cv;
using namespace std;


class String {
public:
    String(const char *str = nullptr)
    {
        if (str == nullptr) {
            m_str = nullptr;
        } 
        else
        {
            if (m_str != nullptr)
            {
                delete[]m_str;
                m_str = nullptr;
            }
            size_t sleng = strlen(str);
            m_str = new char[sleng + 1];
            memcpy(m_str, str, sleng);
            m_str[sleng] = '\0';
        }
    }
    String(const String &other)
    {
        if (this != &other)
        {
            if (other.m_str == nullptr) {
                m_str = nullptr;
            }
            else
            {
                if (m_str != nullptr)
                {
                    delete[]m_str;
                    m_str = nullptr;
                }
                size_t sleng = strlen(other.m_str);
                m_str = new char[sleng + 1];
                memcpy(m_str, other.m_str, sleng);
                m_str[sleng] = '\0';
            }
        }
    }
    String & operator =(String &other)
    {
        if (other.m_str == nullptr) {
            m_str = nullptr;
        }
        else
        {
            if (m_str != nullptr)
            {
                delete[]m_str;
                m_str = nullptr;
            }
            size_t sleng = strlen(other.m_str);
            m_str = new char[sleng + 1];
            memcpy(m_str, other.m_str, sleng);
            m_str[sleng - 1] = '\0';
        }
        return *this;
    }
    //String operator =()
    ~String(void)
    {
        if (m_str != nullptr)
        {
            delete[]m_str;
            m_str = nullptr;
        }
    }


private:
    char *m_str;
};











int main101010()
{
   
    return 0;
}




#include <stack>
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) :val(x), left(nullptr), right(nullptr) {};
};

void alongLeft(TreeNode *root, stack<TreeNode*> &elements)
{
    if (root == nullptr) return;
    elements.push(root);

    TreeNode* next_;
    while (root->left != nullptr)
    {
        next_ = root->left;
        elements.push(next_);
    }
}

bool isValidBST(TreeNode *root)
{
    if (root == nullptr) return false;
    if (root->left == nullptr && root->right == nullptr) return true;


    stack<TreeNode*> elements_;
    alongLeft(root, elements_);

    int val_cur_ = 0;
    int val_last_;

    int index_ = 0;

    TreeNode* cur_;
    TreeNode* prev_ = nullptr;
    while (elements_.size() > 0)
    {
        
        cur_ = elements_.top();
        elements_.pop();
        if (cur_ == nullptr)
        {
            continue;
        }
        index_++;

        val_last_ = val_cur_;
        val_cur_ = cur_->val;

        if (val_cur_ < val_last_ && index_ > 1)
        {
            return false;
        }

        if (prev_ != nullptr && cur_->val < prev_->val)
            return false;
        prev_ = cur_;

        alongLeft(cur_->right, elements_);
    }
    return true;
}

void preorder_iteration_alongleft(TreeNode *root, stack<TreeNode*> &elements)
{
    TreeNode *cur_ = root;
    while (cur_ != nullptr)
    {
        cur_->val;//val
        elements.push(cur_->right);
        cur_ = cur_->left;
    }
}
void preorder_iteration(TreeNode *root)
{
    stack<TreeNode*> elements_;
    preorder_iteration_alongleft(root,elements_);

    TreeNode* cur_;
    while (elements_.size() > 0)
    {

        cur_ = elements_.top();
        elements_.pop();
        if (cur_ == nullptr)
        {
            continue;
        }
        preorder_iteration_alongleft(cur_, elements_);
    }
}



void inorder_iteration_alongLeft(TreeNode *root, stack<TreeNode*> &elements)
{
    if (root == nullptr) return;
    elements.push(root);

    TreeNode* next_;
    while (root->left != nullptr)
    {
        next_ = root->left;
        elements.push(next_);
    }
}

bool inorder_iteration(TreeNode *root)
{
    if (root == nullptr) return false;
    if (root->left == nullptr && root->right == nullptr) return true;


    stack<TreeNode*> elements_;
    inorder_iteration_alongLeft(root, elements_);

    TreeNode* cur_;
    while (elements_.size() > 0)
    {

        cur_ = elements_.top();
        elements_.pop();
        if (cur_ == nullptr)
        {
            continue;
        }
        cur_->val;//val
        inorder_iteration_alongLeft(cur_->right, elements_);
    }
    return true;
}


void postorder_iteration_alongLeft(TreeNode *root, stack<TreeNode*> &elements)
{
    TreeNode* next_ = root;
    while (next_ != nullptr)
    {
        elements.push(next_);
        next_ = next_->left;
    }
}

bool postorder_iteration(TreeNode *root)
{
    if (root == nullptr)
    {
        return;
    }

    stack<TreeNode*> elements_;
    TreeNode * cur_ = root;
    postorder_iteration_alongLeft(cur_, elements_);

    TreeNode * lastVisited_ = nullptr;//记录上一次访问过的节点

    while (elements_.size()>0)
    {

        cur_ = elements_.top();

        //右孩子为空，或者右孩子上次已经访问完
        if (cur_->right == nullptr || cur_->right == lastVisited_)
        {
            cur_->val;//val

            lastVisited_ = cur_;//更新lastVisited
            elements_.pop();
            cur_ = nullptr;
        }
        else {
            cur_ = cur_->right;//这时p是第一次被访问，不能直接访问其指向的值，应该先访问右子树
        }
        postorder_iteration_alongLeft(cur_, elements_);

    }
    return true;
}
