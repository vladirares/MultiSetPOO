#pragma once
#include<functional>
#include<iostream>
using namespace std;

template < typename T >
class Comparator		//functor
{
	hash<T> hashing;

public:
	size_t operator ()(const T item) const {
		return hashing(item);
	};	//std::size_t can store the maximum size of a theoretically possible object of any type(including array). In cazul de mai sus reprezinta hash value-ul parametrului.
	static bool equals(T item1, T item2){
		return item1 == item2;
	};
	static bool greater(T item1, T item2){
		return item1 > item2;
	};
	static bool less(T item1, T item2){
		return item1 < item2;
	};
};


size_t Comparator<double>::operator()(const double item)const {
	return hashing(  ceil((item-(int)item) * 100000000) );
}

bool Comparator<double>::equals(double item1, double item2) {
	if ( abs((int)((item1 - floor(item1))*100000000) - (int)((item2 - floor(item2))*100000000))<2 ) {
		return true;
	}
	return false;
}


bool Comparator<double>::less(double item1, double item2) {
	if (!Comparator<double>::equals(item1,item2)) {
		return item1<item2;
	}
	return false;
}

bool Comparator<double>::greater(double item1, double item2) {
	if (!Comparator<double>::equals(item1, item2)) {
		return item1 > item2;
	}
	return false;
}
