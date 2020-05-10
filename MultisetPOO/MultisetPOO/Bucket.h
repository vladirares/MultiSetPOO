#pragma once
#include"Element.h"
#include <iostream>
#include<string>
using namespace std;

template<typename T>
class Bucket
{
public:
	Element<T>* root;
public:
	void insert(T);
    void remove(T);
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
            if (val <= x->getInfo()) {
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
void Bucket<T>::remove(T val) {
    Element<T>* aux = root;
    //Element<T>* elemToRemove;
    Element<T>* parent = root;
    while (aux != NULL) {                     //cautam
        if (val < aux->getInfo() ) {      //elementul
			aux = aux->getLeft();               //in
        }                                   //arbore
        if (val > aux->getInfo()) {
			aux = aux->getRight();
        }
        if (val == aux->getInfo()) {
            break;
        }
    }                           
    if (aux == NULL) {                        //inseamna ca nu l-am gasit
        throw invalid_argument("not found");
    }

	if (aux == root && !aux->getLeft() && !aux->getRight()) {
		root = NULL;
	}
	else if(aux == root && !aux->getRight()) {
		root = root->getLeft();
		delete aux;
	}
	else if (aux == root && !aux->getLeft()) {
		root = root->getRight();
		delete aux;
	}
	else {

		while (aux)
		{
			if (aux->getInfo() > val)
			{
				parent = aux;
				aux = aux->getLeft();
			}
			else if (aux->getInfo() < val)
			{
				parent = aux;
				aux = aux->getRight();
			}
			else
			{
				// daca sunt egale
				if (!aux->getRight() && !aux->getLeft())
				{
					// daca nodul este frunza
					if (parent->getLeft() == aux)
						parent->setLeft(NULL);
					else
						parent->setRight(NULL);
					delete aux;
				}
				else if (!aux->getLeft())
				{
					//daca are doar fiul drept
					if (parent->getLeft() == aux)
						parent->setLeft(aux->getRight());
					else
						parent->setRight(aux->getRight());
					delete aux;
				}
				else if (!aux->getRight())
				{
					//daca are doar fiul stang
					if (parent->getLeft() == aux)
						parent->setLeft(aux->getLeft());
					else
						parent->setRight(aux->getLeft());
					delete aux;
				}
				else
				{
					Element<T>* temp = aux;
					temp = aux->getRight();
					while (temp->getLeft())
					{
						temp = temp->getLeft();
					}
					T value = temp->getInfo();
					remove(temp->getInfo());
					aux->setInfo(value);
				}
				return;
			}
		}
		return;
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
    return out;
}