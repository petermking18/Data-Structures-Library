#ifndef DLLIST_H
#define DLLIST_H
#include <iostream>

using namespace std;

template<class T>
class Node
{
    template <class U> friend class DLList;
private:
    T data;
    Node<T>* next;
    Node<T>* prev;
public:
    Node():next(nullptr),prev(nullptr){}
    Node(T val):next(nullptr),prev(nullptr),data(val){}
    Node(const Node<T>& d2):next(d2.next),prev(d2.prev),data(d2.data){}

    void setData(T in){
        data = in;
    }///end setData

    T getData(){
        if(this != nullptr)
            return data;
    }///end getData

    T get_prev(){
        if(prev != nullptr)
            return prev->getData();
    }

    T get_next(){
        if(next != nullptr)
            return next->getData();
    }

    bool operator==(T r){
        if(data == r)
            return true;
        return false;
    }

    bool operator==(Node<T> r){
        if(data == r.data)
            return true;
        return false;
    }

    bool operator!=(T r){
        if(data != r)
            return true;
        return false;
    }

    bool operator!=(Node<T> r){
        if(data != r.data)
            return true;
        return false;
    }

    friend ostream& operator<<(ostream& out, Node<T> in){
        out << in.data;
    }
};///end Node Class

template<class T>
class DLList
{
private:
    Node<T>* head;
    Node<T>* tail;
    Node<T>* iter;
    int size;
public:
    DLList<T>(){
        head = tail = iter = nullptr;
        size = 0;
    }///end Constructor

    ~DLList(){
        clear();
    }

        void clear(){
            if(head != nullptr){
                Node<T>* curr = head;
                while(curr != nullptr){
                    curr = curr->next;
    //                if(head != nullptr)
    //                    delete head;
                    head = curr;
                }
            }
            size = 0;
            head = tail = iter = nullptr;
        }

//    void clear(){
//        if(size == 1){
//            if(head != nullptr)
//                delete head;
//            head = tail = iter = nullptr;
//            size--;
//        }else if(size == 0){

//        }else{
//            Node<T>* prev = tail;
//            Node<T>* curr = tail->prev;
//            while(size>0){
//                if(size ==1){
//                    if(head != nullptr)
//                        delete head;
//                    head = tail = iter = nullptr;
//                }else{
//                    curr->next = nullptr;
//                    if(prev != nullptr)
//                        delete prev;
//                    prev = curr;
//                    curr = curr->prev;
//                }
//                size--;
//            }
//            head = nullptr;
//            tail = nullptr;
//            iter = nullptr;
//        }
//    }

    void insert_front(T in){
        Node<T>* newNode = new Node<T>();
        newNode->setData(in);
        newNode->next = head;
        newNode->prev = nullptr;
        if(head != nullptr)
            head->prev = newNode;
        head = newNode;
        updateTail();
    }

    void updateTail(){
        Node<T>* curr = head;
        while(curr->next != nullptr) curr = curr->next;
        tail = curr;
    }

    void insert_back(T in){
        Node<T>* newNode = new Node<T>();
        Node<T>* last = head;

        newNode->setData(in);

        newNode->next = nullptr;

        if(head == nullptr){
            newNode->prev = nullptr;
            head = newNode;
            iter = head;
            size++;
            return;
        }

        while(last->next != nullptr) last = last->next;

        last->next = newNode;

        newNode->prev = last;

        updateTail();

        size++;
        return;
    }


    T get_head(){
        return head->getData();
    }

    T get_tail(){
        updateTail();
        Node<T>* theTail = get_tail_ref();
        return theTail->getData();
    }

    Node<T>* get_tail_ref(){
        Node<T>* curr = head;
        while(curr->next != nullptr)
            curr = curr->next;
        return curr;
    }

    int get_size(){
        return size;
    }

    friend ostream& operator<<(ostream& out, DLList<T> const& in){
        out << in;
    }

    void print(){
        Node<T>* curr = head;
        while(curr != nullptr){
            cout << "<" << curr->getData() << "> ";
            curr = curr->next;
        }
        cout << endl;
    }///end print

    void step_iter(){
        //        if(iter->getData() != tail->getData())
        //            iter = iter->next;
        if(iter != nullptr)
            iter = iter->next;
    }

    void stepback_iter(){
        if(iter->getData() != head->getData())
            iter = iter->prev;
    }

    Node<T>* get_iter_ref(){
        return iter;
    }

    T get_iter(){
        return iter->getData();
    }

    void iter_to_head(){
        iter = head;
    }

    void iter_to_tail(){
        iter = tail;
    }

    bool iter_isLast(){
        if(iter->next == nullptr)
            return true;
        return false;
    }

    void delete_tail(){
        if(tail != nullptr){
            if(tail->next != nullptr){
                Node<T>* curr = head;
                while(curr->next != nullptr)
                    curr = curr->next;
                tail = curr;
            }
        }
        if(tail != nullptr){
            if(tail->prev != nullptr){
                tail= tail->prev;
                delete tail->next;
                tail->next = nullptr;
            }else{
                delete tail;
            }
        }
        size--;
        if(size == 0)
            head = tail = iter = nullptr;
    }///end delete_tail
};
#endif // DLLIST_H
