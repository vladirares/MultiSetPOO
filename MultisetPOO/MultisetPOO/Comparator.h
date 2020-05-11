#pragma once
#include<functional>
using namespace std;

template < typename T >
class Comparator		//functor
{
	hash<T> hashing;

public:
	size_t operator ()(const T) const;	//std::size_t can store the maximum size of a theoretically possible object of any type(including array). In cazul de mai sus reprezinta hash value-ul parametrului.
	static bool equals(T item1, T item2){
		return item1 == item2;
	};
	static bool greater(T item1, T item2){
		return item1 > item2;
	};
	static bool lesser(T item1, T item2){
		return item1 < item2;
	};
};


template<typename T>
size_t Comparator<T>::operator()(const T item)const {
	return hashing(item);
}
