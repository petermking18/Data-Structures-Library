#ifndef STACK_H
#define STACK_H
#include "dllist.h"
#include <iostream>

using namespace std;

template<typename T>
class Stack
{
private:
    DLList<T> list;
public:
    Stack(){list = DLList<T>();}///end constructor

    Stack(const Stack& in){list = in.list;}

    Stack(const DLList<T>& in){list = in;}

//    ~Stack(){
//        //        if(!isEmpty())
//        //            list.clear();
//    }///end destructor

    void push(const T& in){list.insert_back(in);}

    void push(const Node<T>& in){list.insert_back(in);}

    void print(){list.print();}

    T peek(){
        list.updateTail();
        //        if(list.get_size() == 1)
        //            return list.get_head();
        return list.get_tail();
    }

    T pop(){
        T temp;
        if(!isEmpty()){
            temp = list.get_tail();
            list.delete_tail();
            return temp;
        }
        return temp;
    }

    bool isEmpty(){
        if(list.get_size() == 0)
            return true;
        return false;
    }

    int getListSize(){return list.get_size();}

    bool contains(T key){
        list.iter_to_head();
        for(int i = 0; i < list.get_size(); i++){
            if(list.get_iter() == key)
                return true;
        }
        return false;
    }

    friend ostream& operator<<(ostream& out, Stack<T> in){
        in.print();
    }

};

#endif // STACK_H
