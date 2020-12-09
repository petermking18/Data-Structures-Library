#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "word.h"
#include <functional>
#include <fstream>
#include <index.h>

using namespace std;

template <typename K, typename V>
class HashNode{
    template <class U> friend class HashTable;
private:
    K key;
    V value;
    HashNode* next;
    bool nodeFull;
public:
    HashNode(): key(0),next(nullptr), nodeFull(false){}
    HashNode(const K &key, const V &value): key(key), value(value), next(nullptr), nodeFull(false){}
    ~HashNode(){if (next != nullptr) delete next;}
    K getKey() const{return key;}
    V& getValue() {return value;}
    bool getBool() const{return nodeFull;}
    void setKey(int yo){key=yo;}
    void setBool(bool b) {nodeFull = b;}
    void setValue(V value){this->value = value;}
    HashNode<K, V>* getNext() const{return next;}
    void setNext(HashNode<K, V>* next){this->next = next;}
};

template <typename T>
class HashTable{
private:
    int tableSize;
    //HashNode<int, Word> nodes[250000];
    HashNode<int, Word>** nodes;

public:

    HashTable():tableSize(250000){
        nodes = new HashNode<int, Word>* [250000];
        for(int i = 0; i < 250000; i++)
            nodes[i] = new HashNode<int, Word>();
    }


    HashTable(const HashTable<T>& h){
        nodes = new HashNode<int, Word>* [h.tableSize];
        for(int i = 0; i < h.tableSize; i++)
            nodes[i] = h[i];
        this->tableSize = h.tableSize;
    }


    ~HashTable(){makeEmpty();}

    int getTableSize(){return tableSize;}
    HashNode<int, Word>** getNodes(){return nodes;}

    void makeEmpty(){
        for(int i = 0; i < tableSize; i++){
            HashNode<int, Word>* curr = nodes[i];
            while(curr != nullptr){
                HashNode<int, Word>* prev = curr;
                curr = curr->getNext();
                delete prev;
            }
            nodes[i] = nullptr;
        }
        delete[] nodes;
        tableSize = 0;
    }

    void insert(Word w){
        hash<string> str_hash;
        int input = (str_hash(w.getWord()) % tableSize);
       // HashNode<int, Word>* entry = nodes[input];
        if(nodes[input]->getBool() == false){
            nodes[input]->setKey(input);
            nodes[input]->setValue(w);
            nodes[input]->setBool(true);
            nodes[input]->setNext(new HashNode<int,Word>());
        }
        else{
            nodes[input]->getNext()->setValue(w);}
    }

    bool contains(Word w){
        hash<string> str_h;
        int input = (str_h(w.getWord()) % tableSize);
        HashNode<int, Word>* curr = nodes[input];
        if(curr->getBool() == false)
            return false;
        else{
            while(curr != nullptr){
                if(curr->getValue().getWord() == w.getWord())
                    return true;
                else{curr = curr->getNext();}
            }
            return false;
        }
    }

    Word& find(Word w){
        hash<string> str_h;
        int input = (str_h(w.getWord()) % tableSize);
        HashNode<int, Word>* curr = nodes[input];
        if(curr->getValue().getWord() == w.getWord()){
            //Word w = curr->getValue();
            return curr->getValue();
        }
        else{
            while(curr != nullptr){
                if(curr->getValue().getWord() == w.getWord()){
                    //Word w = curr->getValue();
                    return curr->getValue();
                }
                else{curr = curr->getNext();}
            }
        }
    }

    void inOrder(){
        ofstream out("index.txt");
        for(int i = 0; i < tableSize; i++){
            HashNode<int, Word>* curr = nodes[i];
            if(curr->getBool() == true){
                HashNode<int, Word>* itr = curr;
                while(itr != nullptr){
                    out << itr->getValue() << endl;
                    itr = itr->getNext();
                }
            }
        }
        out.close();
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
//            while(s[0] == "~"){

//            }
        }
        in.close();
        cout << numFiles << " words loaded into index" << endl;
    }
};

#endif // HASHTABLE_H
