#ifndef ALIST_H
#define ALIST_H
#include "dllist.h"
#include "stringy.h"
#include <iostream>
#include <iomanip>

using namespace std;

template<class T>
class ANode
{
    template <typename U> friend class AList;
private:
    Stringy name;
    T data;
    //DLList<T> subList;
    ANode<T>* next;
    ANode<T>* prev;
public:
    DLList<T> subList;
    ANode():data(nullptr),subList(DLList<T>()),next(nullptr),prev(nullptr),name(""){}
    ANode(T n):data(n),subList(DLList<T>()),next(nullptr),prev(nullptr),name(""){}
    ANode(const ANode<T>& in):data(in.data),subList(DLList<T>()),next(in.next),prev(in.prev),name(in.name){}

    void set_name(Stringy in){
        name = in;
    }
    ANode<T>* getNext(){return next;}

    Stringy get_name(){return name;}

    void set_data(T in){data = in;}

    T get_data(){return data;}

    DLList<T>& get_sub(){return subList;}

    bool operator==(Stringy in){if(this->data == in)return true; return false;}
};

template<class T>
class AList
{
private:
    ANode<T>* A_head;
    ANode<T>* A_tail;
    ANode<T>* A_iter;
    int size;
public:
    AList<T>(){
        A_head = A_tail = A_iter = nullptr;
        size = 0;
    }

    ~AList(){
        clear();
    }

    void clear(){
        if(A_head != nullptr){
            ANode<T>* curr = A_head;
            while(curr != nullptr){
                curr = curr->next;
                if(A_head != nullptr)
                    delete A_head;
                A_head = curr;
            }
        }
        size = 0;
        A_head = A_tail = A_iter = nullptr;
    }

    void updateTail(){
        ANode<T>* curr = A_head;
        while(curr->next != nullptr) curr = curr->next;
        A_tail = curr;
    }

    void insert_back(T in){
        ANode<T>* newANode = new ANode<T>(in);
        ANode<T>* last = A_head;
        newANode->set_data(in);
        newANode->next = nullptr;

        if(A_head == nullptr){
            newANode->prev = nullptr;
            A_head = newANode;
            A_iter = A_head;
            size++;
            return;
        }

        while(last->next != nullptr) last = last->next;
        last->next = newANode;
        newANode->prev = last;
        updateTail();
        size++;
        return;
    }

    void A_iter_step(){
        if(A_iter != A_tail)
            A_iter = A_iter->next;
    }

    void A_iter_stepback(){
        if(A_iter != A_head)
            A_iter = A_iter->prev;
    }

    ANode<T>* get_A_iter_ref(){
        return A_iter;
    }

    T get_A_iter(){
        return A_iter->get_data();
    }

    void A_iter_to_head(){
        A_iter = A_head;
    }

    void A_iter_to_tail(){
        A_iter = A_tail;
    }

    T A_iter_return(T key){
        bool keyFound = false;
        A_iter_to_head();
        while(A_iter != nullptr && keyFound == false){
            if(get_A_iter() == key){
                keyFound = true;
                break;
            }else A_iter_step();
        }
        return get_A_iter();
    }

    ANode<T>* A_iter_return_ref(T key){
        bool keyFound = false;
        A_iter_to_head();
        while(A_iter != nullptr && keyFound == false){
            if(get_A_iter() == key){
                keyFound = true;
                break;
            }else A_iter_step();
        }
        return A_iter;
    }

    //Finds ANode with data equal to key, stops A_iter there.
    //If such an ANode doesn't exist, returns to head.
    void A_iter_find(T key){
        bool keyFound = false;
        A_iter_to_head();
        while(A_iter != nullptr && keyFound == false){
            if(get_A_iter() == key){
                keyFound = true;
                break;
            }else A_iter_step();
        }
    }

    //Finds ANode with data equal to key, inserts node with
    //data equal to ins
    void ins_sub(T key, T ins){
        A_iter_find(key);
        A_iter->subList.insert_back(ins);
    }

    //Inserts node with data equal to ins at current A_iter
    //spot
    void ins_sub(T ins){
        A_iter->subList.insert_back(ins);
    }

    bool A_iter_isLast(){
        if(A_iter->next == nullptr)
            return true;
        return false;
    }

    void print_AList(){
        bool printRoots = true;
        bool printSubs = true;
        A_iter_to_head();
        if(A_iter == nullptr)
            printRoots = false;
        while(printRoots == true){
            cout << A_iter->get_data();
            A_iter->subList.iter_to_head();
            printSubs = true;
            if(A_iter->subList.get_iter_ref() == nullptr)
                printSubs = false;
            while(printSubs == true){
                cout << " ---> " << A_iter->subList.get_iter();
                if(A_iter->subList.iter_isLast() == true) printSubs = false;
                A_iter->subList.step_iter();
            }
            cout << endl;
            if(A_iter_isLast() == true) printRoots = false;
            A_iter_step();
        }
    }

    int getSize(){
        return size;
    }

    int getSubSize(){
        A_iter->subList.get_size();
    }
};
#endif // ALIST_H
