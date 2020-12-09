#include "stringy.h"
#include <cstring>
#include <iostream>
using namespace std;

Stringy::Stringy(){
    data = nullptr;
}

Stringy::Stringy(const char* str){
    data = new char[strlen(str)+1];
    strcpy(data, str);
}

Stringy::Stringy(const Stringy& str){
    if(this==&str)
        return;
    data = new char[strlen(str.data)+1];
    strcpy(data, str.data);
}

Stringy::~Stringy(){
    if(data != nullptr)
        delete[] data;
}

Stringy& Stringy::operator=(const char * q){
    if(data != nullptr)
        delete[]data;
    if (q == nullptr) {
        data = nullptr;
        return *this;
    }
    if(strlen(q) == 0){
        data = nullptr;
        return *this;
    }
    data = new char[strlen(q)+1];
    strcpy(data, q);
    return *this;
}

Stringy& Stringy::operator=(const Stringy &str){
    if(this!=nullptr){
        if(data != nullptr)
            delete[] data;
        if(str.data != nullptr){
            data = new char[strlen(str.data)+1];
            strcpy(data, str.data);
        }
    }
    return *this;
}//end = operator

bool Stringy::exists(){
    if(data)
        return true;
    else
        return false;
}///end exists

Stringy Stringy::operator+(const Stringy& q){
    Stringy s;
    s.data = new char[strlen(data)+strlen(q.data)+1];
    strcpy(s.data, data);
    strcat(s.data, q.data);
    return s;
}//end + operator

char& Stringy::operator[] (const int j){
    if(j >= getLength()) throw 1;
    return data[j];
}//end [] operator

void Stringy::clearArrays(){
    delete[] data;
}//End clearArrays

ostream& operator<<(ostream& out, Stringy const& str){
    out << str.data;
}

Stringy Stringy::substring(int a, int b){
    if(data != nullptr){
        char* sub = new char[strlen(data)];
        int start = a;
        int stop = a+b;
        if(a > b){
            start = a+b;
            stop = a;
        }
        int j = 0;
        for(int i = start; i < stop; i++){
            sub[j] = data[i];
            j++;
        }
        Stringy s = sub;
        delete[]sub;
        return s;
    }
    Stringy nullReturn = "";
    return nullReturn;
}

int Stringy::getLength(){
    if(data != nullptr)
        return strlen(data);
    else {
        return 0;
    }
}

bool Stringy::operator==(const char *in){
    if((data != nullptr) && (in != nullptr)){
        if(strcmp(data, in) == 0)
            return true;
        else
            return false;
    }else if((data == nullptr) && (in == nullptr)){
        return true;
    }else if(in != nullptr){
        if((data == nullptr) && (strlen(in) == 0))
            return true;
    }else if(data != nullptr){
        if((strlen(data) == 0) && (in == nullptr))
            return true;
    }
    return false;
}

bool Stringy::operator==(const Stringy &in){
    if(data != nullptr){
        if(strcmp(data, in.data) == 0)
            return true;
        else
            return false;
    }else if(in.data == nullptr){
        return true;
    }
    return false;
}

bool Stringy::operator<(const char *in){
    if(data != nullptr){
        if(strcmp(data, in) < 0)
            return true;
        else
            return false;
    }else
        return false;
}

bool Stringy::operator>(const char *in){
    if(data != nullptr){
        if(strcmp(data, in) > 0)
            return true;
        else
            return false;
    }else
        return false;
}

bool Stringy::operator<(const Stringy &in){
    if(data != nullptr){
        if(strcmp(data, in.data) < 0)
            return true;
        else
            return false;
    }else
        return false;
}

bool Stringy::operator>(const Stringy &in){
    if(data != nullptr){
        if(strcmp(data, in.data) > 0)
            return true;
        else
            return false;
    }else
        return false;
}

char* Stringy::getString(){
    return data;
}///end getString

int Stringy::inty(){
    //Returns int of Stringy
    if(data != nullptr)
        return stoi(data);
    else
        return 0;
}

bool Stringy::operator!=(const char *in){
    if((data != nullptr) && (in != nullptr) && (in != "")){
        if(strcmp(data, in) != 0)
            return true;
        else
            return false;
    }else if((data == nullptr) && (in == nullptr)){
        return false;
    }
    char* c = "";
    if((strcmp(in, c) == 0) && (data == nullptr)){
        return false;
    }
    return true;
}///end operator!= char*

bool Stringy::operator!=(const Stringy &in){
    if((data != nullptr) && (in.data != nullptr)){
        if(strcmp(data, in.data) != 0)
            return true;
        else
            return false;
    }else if((in.data == nullptr) && (data == nullptr)){
        return false;
    }else
        return true;
}///end operator!= Stringy

char Stringy::getChar(int index){
    if(data != nullptr)
        return data[index];
    else {
        return ' ';
    }
}

void Stringy::setChar(int index, char &c){
    if(data != nullptr)
        data[index] = c;
}








