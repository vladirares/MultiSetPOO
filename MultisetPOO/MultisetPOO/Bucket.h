#pragma once
#include"Element.h"
#include"Comparator.h"
#include <iostream>
#include<string>
using namespace std;

template<typename T>
class Bucket
{

	//bool stop = false;
	unsigned distincts;
	void remove(T, bool);
//public:
	Element<T>* root;
public:
	Bucket<T>();
	void insert(T);
    void remove(T);
    bool isEmpty();
	unsigned numberOf(T);
	unsigned numberOfDistinct();
	bool contains(T);
    friend ostream& operator << (ostream& out, const Bucket& bucket) {
		bucket.SRD(bucket.root, out);
		return out;
	}
    void SRD(Element<T>*, ostream&)const;

};

template<typename T>
Bucket<T>::Bucket<T>() {
	this->root = NULL;
	this->distincts = 0;
	
}

template<typename T>
bool Bucket<T>::isEmpty() {
    return root ? false : true;
}

template<typename T>
void Bucket<T>::insert(T val) {
	if (!this->contains(val)) {
		this->distincts++;
	}
    if (root == NULL) {
        root = new Element<T>(val);
    }
    else {
        Element<T>* y = NULL;
        Element<T>* x = root;
        while (x != NULL) {
            y = x;
            if (Comparator<T>::lesser(val,x->getInfo()) || Comparator<T>::equals(val, x->getInfo())) {
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
	if (!this->contains(val)) {
		throw invalid_argument("not found");
	}
	if (this->numberOf(val) == 1) {
		this->distincts--;
	}
	remove(val, true);
}

template<typename T>
void Bucket<T>::remove(T val, bool stop) {
	
    Element<T>* aux = root;
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
					remove(temp->getInfo(),true);
					aux->setInfo(value);
				}
				//this->stop = false;
				return;
			}
		}
		//this->stop = false;
		return;
	}

}

template<typename T>
unsigned Bucket<T>::numberOf(T val) {
	Element<T>* x = root;
	unsigned number = 0;
	while (x != NULL) {
		if (val == x->getInfo()) {
			number++;
		}
		if (val <= x->getInfo()) {
			x = x->getLeft();
		}
		else{
			x = x->getRight();
		}
	}
	return number;
}

template<typename T>
unsigned Bucket<T>::numberOfDistinct() {
	return this->distincts;
}

template<typename T>
bool Bucket<T>::contains(T val) {
	Element<T>* x = root;
	while (x != NULL) {
		if (val == x->getInfo()) {
			return true;
		}
		if (val <= x->getInfo()) {
			x = x->getLeft();
		}
		else {
			x = x->getRight();
		}
	}
	return false;
}

template<typename T>
void Bucket<T>::SRD(Element<T>* x , ostream& out)const {
    if (x != NULL) {
        SRD(x->getLeft(),out);
        out << x->getInfo() << " ";
        SRD(x->getRight(),out);
    }
}

//template<typename T>
//ostream& operator << (ostream& out, const Bucket<T>& bucket) 