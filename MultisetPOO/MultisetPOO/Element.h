#pragma once

template <typename T>
class Element
{
	T info;
	Element* left, * right;

public:
	Element() = delete;
	Element(T);
	void setInfo(T);
	T getInfo();
	Element* getLeft() const;
	Element* getRight() const;
	void setLeft(Element<T>*);
	void setRight(Element<T>*);
};

template<typename T>
void Element<T>::setInfo(T val) {
	this -> info = val;
}

template<typename T>
Element<T>::Element(T info) {
	this->info = info;
	left = right = nullptr;
}

template<typename T>
T Element<T>::getInfo()  {
	return this->info;
}

template<typename T>
Element<T>* Element<T>::getLeft()const {
	return this->left;
}

template<typename T>
Element<T>* Element<T>::getRight()const {
	return this->right;
}

template<typename T>
void Element<T>::setRight(Element<T>* right) {
	this->right = right;
}

template<typename T>
void Element<T>::setLeft(Element<T>* left) {
	this->left = left;
}


