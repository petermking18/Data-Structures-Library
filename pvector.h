#ifndef PVECTOR_H
#define PVECTOR_H
#include <iostream>

using namespace std;

template <typename T>
class PVector
{
private:
    T* data;
    int capacity;
    int size;
public:
    PVector<T>(){
        size = 0;
        capacity = 10;
        data = new T[capacity];
    }

    PVector<T>(const T& in){
        capacity = in;
        data = new T[capacity];
        size = 0;
    }

    PVector<T>(const PVector<T>& in){
        capacity = in.capacity;
        size = in.size;
        delete[]data;
        data = new T[capacity];
        for(int i = 0; i < size; i++)
            data[i] = in.data[i];
    }

    PVector<T>& operator=(const PVector<T>& in){
        if(this != &in){
            size = in.size;
            capacity = in.capacity;
            delete[]data;
            data = new T[capacity];
            for(int i = 0; i < size; i++)
                data[i] = in.data[i];
        }
        return *this;
    }

    ~PVector<T>(){
        if(data)
            delete[]data;
    }

    //overloaded operators
    T& operator[](int index) const{
        if(data != nullptr)
            return data[index];
    }
    const PVector& operator++();
    const PVector& operator--();
    const bool operator==(PVector&) const;
    PVector& operator=(PVector&);
    PVector& operator+=(PVector&);
    const PVector operator+(const PVector&);
    const PVector& operator+(int);

    friend ostream& operator<<(ostream& out, T const& in){
        out << in;
    }


    void setSize(int s){
        size = s;
    }///end setSize

    void setCapacity(int c){
        capacity = c;
    }///end setCapacity

    int getSize() const {
        return size;
    }///end getSize

    void printVector(){
        for(int i = 0; i < size; i++){
            printElement(i);
        }
    }///end printVector

    void printElement(int index){
        cout << data[index] << endl;
    }

    void add(T input){
        if(size == capacity){
            resize();
        }
        size++;
        data[size-1] = input;
    }///end add

    void resize(){
        capacity *= 2;
        T* temp = new T[capacity];
        for(int i = 0; i < size; i++)
            temp[i] = data[i];
        delete[]data;
        data = temp;
    }///end resize

    void clearArrays(){
        delete[]data;
        size = 0;
        capacity = 10;
    }

    void minusSize(){
        size--;
    }
};

#endif // PVECTOR_H
