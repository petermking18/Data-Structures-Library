#ifndef STRINGY_H
#define STRINGY_H

#include <iostream>
#include <cstring>
using namespace std;

class Stringy{

private:
    char* data;
public:
    //char* data;
    Stringy();
    Stringy(const char* str);
    Stringy(const Stringy& str);
    ~Stringy();
    void clearArrays();
    char* getString();

    Stringy& operator=(const char*);
    Stringy& operator=(const Stringy&);
    Stringy operator+(const Stringy&);
    Stringy& operator+=(const Stringy&);
    bool exists();
    bool operator== (const char*);
    bool operator== (const Stringy&);
    bool operator!= (const char*);
    bool operator!= (const Stringy&);
    bool operator< (const char*);
    bool operator> (const char*);
    bool operator< (const Stringy&);
    bool operator> (const Stringy&);
    char& operator[] (const int);
    int getLength();
    int inty();
    char getChar(int index);
    void setChar(int index, char& c);

    //substring: parameter a represents the starting position
    //parameter b represents the number of characters to copy
    //into the substring that is returned. If b is positive,
    //count forward from position a. If b is negative, count
    //backward from position a.
    Stringy substring(int a, int b);

    //c_str returns a c-string representation of the Stringy obj.
    char* c_str();

    Stringy& del(const Stringy&);

    friend std::ostream& operator<< (std::ostream& out, Stringy const&);
};

#endif // STRINGY_H
