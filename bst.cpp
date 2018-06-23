#include <iostream>
#include <stack>
using namespace std;

template <class T>
class Node
{
public:
    Node* left;
    Node* right;
    T data;
    Node(T data, Node* left, Node* right):data(data), left(left), right(right)
    {}
    Node():data(0), left(nullptr), right(nullptr)
    {}
};

template <class T>
class BST_iter
{
private:
    Node<T>* node_ptr;

public:
    stack<Node<T>* > s;

    BST_iter(Node<T>* node_ptr):node_ptr(node_ptr)
    {}

    bool operator== (const BST_iter& other) const
    {
        return other.node_ptr == this->node_ptr;
    }

    T& operator* () const
    {
        return node_ptr->data;
    }

    bool operator!= (const BST_iter& other) const
    {
        return other.node_ptr != this->node_ptr;
    }

    BST_iter& operator++()
    {
        if (node_ptr != nullptr)
        {
            if (node_ptr->right != nullptr)
                s.push(node_ptr->right);
            if (node_ptr->left != nullptr)
                node_ptr = node_ptr->left;
            else
            {
                node_ptr = s.top();
                s.pop();
            }
        }
        return *this;
    }

    BST_iter operator++(int)
    {
        if (node_ptr != nullptr)
        {
            if (node_ptr->right != nullptr)
                s.push(node_ptr->right);
            if (node_ptr->left != nullptr)
                node_ptr = node_ptr->left;
            else
            {
                node_ptr = s.top();
                s.pop();
            }
        }
        return *this;
    }
};

template <class T>
class BST
{
private:
    Node<T>* root;
    size_t size;
    int quantity;

public:

    int get_quantity()
    {
        return quantity;
    }

    void copy_bst(Node<T>*& curr, Node<T>& other)
    {
        curr = new Node<T>;
        curr.left = other.left;
        curr.right = other.right;
        curr.data = other.data;
        if (other.left != nullptr)
            copy_bst(curr.left, other.left);
        if (other.right != nullptr)
            copy_bst(curr.right, other.right);
    }

    BST()
    {
        root = nullptr;
        quantity = 0;
    }

    BST(const BST*& other)
    {
        if (other.root != nullptr)
            copy_bst(this->root, other.root);
        this->quantity = other.quantity;
    }

    ~BST()
    {
        delete root;
    }

    BST& operator= (const BST& other)
    {
        if (other.root != nullptr)
            copy_bst(this->root, other.root);
        return *this;
    }

    BST_iter<T> begin()
    {
        return BST_iter<T>(root);
    }

    BST_iter<T> cbegin() const
    {
        return BST_iter<T>(root);
    }

    BST_iter<T> end()
    {
        return BST_iter<T>(NULL);
    }

    BST_iter<T> cend() const
    {
        return BST_iter<T>(NULL);
    }

    Node<T>* minimum(Node<T>* root)
    {
        while (root->left)
        {
            root = root->left;
        }
        return root;
    }

    Node<T>* next(Node<T>* root)
    {
        if (root->right)
            return minimum(root->right);
        return root;
    }

    Node<T>* exist_node(Node<T>*& root, const T data) {
        if (root == nullptr)
            return nullptr;
        if (root->data == data)
            return root;
        if (root->data > data)
            return exist_node(root->left, data);
        else
            return exist_node(root->right, data);
    }

    BST_iter<T> find(const T data)
    {
        if (exist_node(root, data))
            return BST_iter<T>(exist_node(root, data));
        cout << "This node does not exist." << endl;
    }

    BST_iter<T> find(const T data) const
    {
        if (exist_node(root, data))
            return BST_iter<T>(exist_node(root, data));
        cout << "This node does not exist." << endl;
    }

    BST_iter<T> insert_(const T& data)
    {
        size++;
        quantity++;
        Node<T>* res = root;
        insert_node(root, data, &res);
        return BST_iter<T>(res);
    }

    void insert_node (Node<T>*& root, T data, Node<T>** res)
    {
        if (root == nullptr)
        {
            root = new Node<T>(data, nullptr, nullptr);
            *res = root;
            return;
        }
        if (data < root->data)
            insert_node(root->left, data, res);
        else if (data > root->data)
            insert_node(root->right, data, res);
        if (data == root->data)
        {
            BST::quantity--;
            return;
        }
    }

    BST_iter<T> delete_(const T& data){
        size--;
        quantity--;
        Node<T>* res;
        delete_node(root, data, &res);
        return BST_iter<T>(res);
    }

    void delete_node(Node<T>*& root, T data, Node<T>** res)
    {
        if (root == nullptr)
        {
            quantity++;
            return;
        }
        if (root->data < data)
            delete_node(root->right, data, res);
        if (root->data > data)
            delete_node(root->left, data, res);
        else
        {
            if (!root->left || !root->right)
            {
                Node<T>* tmp = nullptr;
                if (!root->left)
                    tmp = root->right;
                else
                    tmp = root->left;

                if (!tmp)
                {
                    tmp = root;
                    root = nullptr;
                }
                else
                    *root = *tmp;
                *res = tmp;
            }
            else
            {
                Node<T>* tmp = next(root);
                root->data = tmp->data;
                delete_node(root->right, tmp->data, res);
            }
        }
    }
};

int main()
{
    BST<int> bst1;
    cout << "Ins:" << *bst1.insert_(4) << endl;
    cout << "Ins:" << *bst1.insert_(2) << endl;
    cout << "Ins:" << *bst1.insert_(6) << endl;
    cout << "Ins:" << *bst1.insert_(9) << endl;
    cout << "Ins:" << *bst1.insert_(1) << endl;

    cout << "Del:" << *bst1.delete_(1) << endl;

    cout << "Find:" << *bst1.find(9) << endl;

    BST<int> bst2 = bst1;

    int counter = 0;
    for (BST_iter<int> i = bst2.begin(); counter < bst2.get_quantity(); counter++)
    {
        cout << *i << endl;
        if (counter != bst2.get_quantity() - 1)
            ++i;
    }
    return 0;
}
