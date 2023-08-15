#include <bits/stdc++.h>

template<typename T>
class Node {
    public:
        T data;
        Node<T>* leftchild;
        Node<T>* rightsibling;

        Node(T data):data{data},leftchild{nullptr},rightsibling{nullptr}{}
};

template <typename T>
class Tree {
    public:
        Node<T>* root;

        Tree():root{nullptr}{}

        void insert(Node<T>*(&r), T d) {
            if(!r)
                r = new Node<T>(d);
            else if(!r->leftchild)
                r->leftchild = new Node<T>(d);
            else if(!r->leftchild->rightsibling)
                r->leftchild->rightsibling = new Node<T>(d);
            else {
                Node<T>* temp = r->leftchild->rightsibling;
                while(temp->rightsibling != nullptr) {
                    temp = temp->rightsibling;
                }
                temp->rightsibling = new Node<T>(d);
            }
        }

        void dfs() {
            dfsRec(root);
            std::cout<<std::endl;
        }

        void dfsRec(Node<T> *r) {
            if(r==nullptr)
                return;
            else {
                std::cout<<r->data<<" ";
                dfsRec(r->leftchild);
                dfsRec(r->rightsibling);
            }
        }

        void bfs() {
            std::queue<Node<T> *> q;
            if (this->root)
                q.push(this->root);
            while (!q.empty()) {
                Node<T> *curr = q.front();
                q.pop();
                std::cout << (curr->data) << " ";
                curr = curr->leftchild;
                if (curr) {
                    q.push(curr);
                    curr = curr->rightsibling;
                }
                while (curr) {
                    q.push(curr);
                    curr = curr->rightsibling;
                }
            }
            std::cout << std::endl;
        }
};

int main() {
    Tree<int> t;
    t.insert(t.root, 10);
    t.insert(t.root, 7);
    t.insert(t.root, 6);
    t.insert(t.root, 5);
    t.insert(t.root->leftchild, 8);
    t.insert(t.root->leftchild, 9);
    t.insert(t.root->leftchild, 3);
    t.insert(t.root->leftchild, 2);
    std::cout<<"DFS: ";
    t.dfs();
    std::cout<<"BFS: ";
    t.bfs();
    return 0;
}
