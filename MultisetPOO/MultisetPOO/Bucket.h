#pragma once
#include"Element.h"
#include <iostream>
using namespace std;

template<typename T>
class Bucket
{
public:
	Element<T>* root;
public:
	void insert(T);
    bool isEmpty();
    template<typename T>
    friend ostream& operator << (ostream&, const Bucket&);
    void SRD(Element<T>*, ostream&)const;

};

template<typename T>
bool Bucket<T>::isEmpty() {
    return root ? false : true;
}

template<typename T>
void Bucket<T>::insert(T val) {
    if (root == NULL) {
        root = new Element<T>(val);
    }
    else {
        Element<T>* y = NULL;
        Element<T>* x = root;
        while (x != NULL) {
            y = x;
            if (val < x->getInfo()) {
                x = x->getLeft();
            }
            else {
                x = x->getRight();
            }
        }
        Element<T>* nodNou = new Element<T>(val);
        nodNou->setLeft(NULL);
        nodNou->setRight(NULL);
        if (y->getInfo() < val) {
            y->setRight(nodNou);
        }
        else {
            y->setLeft(nodNou);
        }
    }
}

template<typename T>
void Bucket<T>::SRD(Element<T>* x , ostream& out)const {
    if (x != NULL) {
        SRD(x->getLeft(),out);
        out << x->getInfo() << " ";
        SRD(x->getRight(),out);
    }
}

template<typename T>
ostream& operator << (ostream& out, const Bucket<T>& bucket) {
    bucket.SRD(bucket.root,out);
    //out << "pula";
    return out;
}