#include <bits/stdc++.h>

template<typename T>
class Node {
    public:
        T data;
        Node* leftchild;
        Node* rightsibling;

        Node(T data):data{data},leftchild{nullptr},rightsibling{nullptr}{}

        void insert_child(T d) {
            if(leftchild == nullptr)
                leftchild = new Node<T>(d);
            else if(rightsibling == nullptr)
                rightsibling = new Node<T>(d);
            else{
                Node<T>* temp = rightsibling;
                while(temp->rightsibling != nullptr) {
                    temp = temp->rightsibling;
                }
                temp->rightsibling = new Node<T>(d);
            }
        }
};

template <typename T>
class Tree {
    public:
        Node<T>* root;

        Tree():root{nullptr}{}

        void insert(Node<T>*(&r), T d) {
            if(r==nullptr)
                r = new Node<T>(d);
            else
                r->insert_child(d);
        }

        void display() {
            displayRec(root);
        }

        void displayRec(Node<T> *r) {
            if(r==nullptr)
                return;
            else {
                std::cout<<r->data<<std::endl;
                displayRec(r->leftchild);
                displayRec(r->rightsibling);
            }
        }
};

int main() {
    Tree<int> t;
    t.insert(t.root, 10);
    t.insert(t.root, 7);
    t.insert(t.root, 6);
    t.insert(t.root, 5);

    t.insert(t.root->leftchild, 8);
    t.display();
    return 0;
}
