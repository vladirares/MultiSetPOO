#pragma once
#include"Element.h"
#include"Comparator.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

template<typename T, typename P>
class Bucket
{
	vector<T> elements;
	unsigned distincts;
	void remove(T, bool);
//public:
	Element<T>* root;
	void SRD(Element<T>*, ostream&)const;
	void SRD(Element<T>* );
	void deleteSRD(Element<T>*);
public:
	Bucket<T,P>();
	void insert(T);
    void remove(T);
    bool isEmpty();
	unsigned numberOf(T);
	unsigned numberOfDistinct();
	vector<T> getElements();
	bool contains(T);
    friend ostream& operator << (ostream& out, const Bucket& bucket) {
		bucket.SRD(bucket.root, out);
		return out;
	}
	void deleteBucket() {
		deleteSRD(root);
		root = NULL;
		this->distincts = 0;
	}
};


template<typename T, typename P>
vector<T> Bucket<T,P>::getElements() {
	elements.clear();
	SRD(root);
	return elements;
}

template<typename T, typename P>
Bucket<T,P>::Bucket() {
	this->root = NULL;
	this->distincts = 0;
	
}

template<typename T, typename P>
bool Bucket<T,P>::isEmpty() {
    return root ? false : true;
}

template<typename T, typename P>
void Bucket<T,P>::insert(T val) {
	this->elements.push_back(val);
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
            if (P::less(val,x->getInfo()) || P::equals(val, x->getInfo())) {
                x = x->getLeft();
            }
            else {
                x = x->getRight();
            }
        }
        Element<T>* nodNou = new Element<T>(val);
        nodNou->setLeft(NULL);
        nodNou->setRight(NULL);
        if (P::less(y->getInfo(),val)) {
            y->setRight(nodNou);
        }
        else {
            y->setLeft(nodNou);
        }
    }
}

template<typename T, typename P>
void Bucket<T,P>::remove(T val) {
	if (!this->contains(val)) {
		throw invalid_argument("not found");
	}
	if (this->numberOf(val) == 1) {
		this->distincts--;
	}
	remove(val, true);
}

template<typename T, typename P>
void Bucket<T,P>::remove(T val, bool stop) {
	
    Element<T>* aux = root;
    Element<T>* parent = root;
    while (aux != NULL) {							//cautam
        if (P::less(val, aux->getInfo())) {			//elementul
			aux = aux->getLeft();					//in
        }											//arbore
        if (P::greater(val, aux->getInfo())) {
			aux = aux->getRight();
        }
        if (P::equals(val, aux->getInfo())) {
            break;
        }
    }                           
    if (aux == NULL) {								//inseamna ca nu l-am gasit
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
			if (P::greater(aux->getInfo(),val) )
			{
				parent = aux;
				aux = aux->getLeft();
			}
			else if (P::less(aux->getInfo(),val))
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
				return;
			}
		}
		return;
	}

}

template<typename T, typename P>
unsigned Bucket<T,P>::numberOf(T val) {
	Element<T>* x = root;
	unsigned number = 0;
	while (x != NULL) {
		if (P::equals(val, x->getInfo())) {
			number++;
		}
		if (P::equals(val, x->getInfo()) || P::less(val, x->getInfo() ) ) {
			x = x->getLeft();
		}
		else{
			x = x->getRight();
		}
	}
	return number;
}

template<typename T, typename P>
unsigned Bucket<T,P>::numberOfDistinct() {
	return this->distincts;
}

template<typename T, typename P>
bool Bucket<T,P>::contains(T val) {
	Element<T>* x = root;
	while (x != NULL) {
		if (P::equals(val, x->getInfo())) {
			return true;
		}
		if (P::equals(val, x->getInfo()) || P::less(val, x->getInfo() ) ) {
			x = x->getLeft();
		}
		else {
			x = x->getRight();
		}
	}
	return false;
}

template<typename T, typename P>
void Bucket<T,P>::SRD(Element<T>* x , ostream& out)const {
    if (x != NULL) {
        SRD(x->getLeft(),out);
        out << x->getInfo() << " ";
        SRD(x->getRight(),out);
    }
}

template<typename T, typename P>
void Bucket<T,P>::SRD(Element<T>* x) {
	if (x != NULL) {
		SRD(x->getLeft());
		elements.push_back( x->getInfo() );
		SRD(x->getRight());
	}
}

template<typename T, typename P>
void Bucket<T,P>::deleteSRD(Element<T>* x) {
	if (x != NULL) {
		deleteSRD(x->getLeft());
		deleteSRD(x->getRight());
		delete x;
	}
}

