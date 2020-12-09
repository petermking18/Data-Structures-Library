/// Peter King
#ifndef AVLTREE_H
#define AVLTREE_H

#include <stdexcept>
#include <iostream>
#include <fstream>
#include <cctype>
#include "word.h"
using namespace std;

template <typename T>
class AVLTree
{
private:
    template<class U>
    class AVLNode
    {
    public:
        T element;
        AVLNode<T> *left;
        AVLNode<T> *right;
        int height;

        AVLNode(const T& theElement, AVLNode *lt,
                AVLNode *rt, int h = 0):
            element(theElement), left(lt), right(rt),
            height(h){}
    };

    AVLNode<T> *root;

public:
    AVLTree():root(nullptr){}
    AVLTree(const AVLTree& rhs):root(NULL){*this = rhs;}
    ~AVLTree(){makeEmpty();}

    AVLNode<T>*& getRoot(){return root;}
    /// Find the smallest item in the tree.
    /// Throw underflow error if empty.
    AVLNode<T>* findMin(AVLNode<T>* t) const{
        if(t == NULL)
            return NULL;
        if(t->left == NULL)
            return t;
        return findMin(t->left);
    }
    const T& findMin() const{
        if(isEmpty())
            throw underflow_error("");
        return findMin(root)->element;
    }

    /// Find the largest item in the tree.
    /// Throw underflow error if empty.
    AVLNode<T>* findMax(AVLNode<T>* t) const{
        if(t != NULL)
            while(t->right != NULL)
                t = t->right;
        return t;
    }
    T& findMax() const{
        if(isEmpty())
            throw underflow_error("");
        return findMax(root)->element;
    }

    /// Returns true if x is found in the tree.
    bool contains(T x){return contains(x, root);}
    bool contains(T x, AVLNode<T>* t) const{
        if(t == NULL)
            return false;
        else if(x < t->element)
            return contains(x, t->left);
        else if(t->element < x)
            return contains(x, t->right);
        else
            return true; ///Match
    }

    /// If x is found in tree, return pointer to its node.
    T& find(T x){return find(x, root)->element;}
    AVLNode<T>* find(T x, AVLNode<T>* t) const{
        if(t == NULL)
            return nullptr;
        else if(x < t->element)
            return find(x, t->left);
        else if(t->element < x)
            return find(x, t->right);
        else
            return t;
    }

    /// Test if the tree is logically empty.
    /// Return true if empty, false otherwise.
    bool isEmpty() const{return root == NULL;}


    /// Make the tree logically empty.
    void makeEmpty(){makeEmpty(root);}
    void makeEmpty(AVLNode<T>* &t){
        if(t != NULL){
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        t = NULL;
    }

    /// Insert x into the tree; duplicates
    /// are ignored.
    void insert(T x){insert(x, root);}
    void insert(T x, AVLNode<T>* &t){
        if(t == NULL)
            t = new AVLNode<T>(x, NULL, NULL);
        else if(x < t->element){
            insert(x, t->left);
            if(height(t->left) - height(t->right) == 2){
                if(x < t->left->element)
                    rotateWithLeftChild(t);
                else
                    doubleWithLeftChild(t);
            }
        }else if(t->element < x){
            insert(x, t->right);
            if(height(t->right) - height(t->left) == 2){
                if(t->right->element < x)
                    rotateWithRightChild(t);
                else
                    doubleWithRightChild(t);
            }
            else
                ;   ///Duplicates do nothing
            t->height = max(height(t->left), height(t->right)) + 1;
        }
    }

    /// Return the height of node t or -1 if NULL.
    int height(AVLNode<T>* t) const{
        //return t = NULL ? -1 : t->height;
        if(t == NULL)
            return -1;
        else
            return t->height;
    }

    /// Rotate binary tree node with left child.
    /// For AVL trees, this is a single rotation for case 1.
    /// Update heights, then set new root.
    void rotateWithLeftChild(AVLNode<T>* &k2){
        AVLNode<T>* k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max(height(k2->left), height(k2->right)) + 1;
        k1->height = max(height(k1->left), k2->height) + 1;
        k2 = k1;
    }

    /// Rotate binary tree node with right child.
    /// For AVL trees, this is a single rotation for case 4.
    /// Update heights, then set new root.
    void rotateWithRightChild(AVLNode<T>* &k1){
        AVLNode<T>* k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max(height(k1->left), height(k1->right)) + 1;
        k2->height = max(height(k2->right), k1->height) + 1;
        k1 = k2;
    }

    /// Double rotate binary tree node: first left child
    /// with its right child; then node k3 with new left child.
    /// For AVL trees, this is a double rotation for case 2.
    /// Update heights, then set new root.
    void doubleWithLeftChild(AVLNode<T>* &k3){
        rotateWithRightChild(k3->left);
        rotateWithLeftChild(k3);
    }

    /// Double rotate binary tree node: first right child
    /// with its left child; then node k1 with new right child.
    /// For AVL trees, this is a double rotation for case 3.
    /// Update heights, then set new root.
    void doubleWithRightChild(AVLNode<T>* &k1){
        rotateWithLeftChild(k1->right);
        rotateWithRightChild(k1);
    }

    /// Prints the entire AVL tree graphically.
    void print(){printSetup(root, 0);}
    void printSetup(AVLNode<T>* curr, int space){
        int count = 10;
        if(curr == NULL)
            return;
        space += count;
        printSetup(curr->right, space);
        for(int i = count; i < space; i++)
            cout << " ";
        cout << curr->element << endl << endl;
        printSetup(curr->left, space);
    }

    /// Prints the entire tree inorder to index file
    void inOrder(){
        ofstream out("index.txt");
        inOrder(root, out); out << endl;
        out.close();
    }
    void inOrder(AVLNode<T>* t, ofstream& out){
        if(t == NULL)
            return;
        inOrder(t->left, out);
        out << t->element << endl;
        inOrder(t->right, out);
    }
    void read(){
        ifstream in("index.txt");
        string s;
        int numFiles = 0;
        while(in >> s){
            if(s[0] == '['){// New word
                string a = s.substr(1, s.size()-1);
                Word w(a);
                in >> s;
                while(s[0] == '('){
                    string b = s.substr(1, s.size()-1);
                    int temp = stoi(b);
                    w.pushDocFreq(temp);
                    in >> s;
                }while(s[0] == '{'){
                    string b = s.substr(1, s.size()-1);
                    w.pushDoc(b);
                    in >> s;
                }if(s[0] == '<'){
                    string b = s.substr(1, s.size()-1);
                    int temp = stoi(b);
                    w.setTotWordFreq(temp);
                }
                insert(w);
                numFiles++;
            }
        }
        in.close();
        cout << numFiles << " words loaded into index" << endl;
    }
};

#endif // AVLTREE_H
