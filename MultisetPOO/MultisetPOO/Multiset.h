#pragma once
#include <iostream>
#include <vector>
#include "Comparator.h"
#include "Bucket.h"
using namespace std;

template < typename T, typename P = Comparator<T> >
class Multiset
{
	P Hash;
	vector <Bucket<T> > Buckets;
	unsigned capacity;
	float loadFactor = 0.75;

public:
	//int a[2];
	//void numbersAreEqual();

	Multiset();
	void insert(T);
	void remove(T);
	unsigned numberOf(T);
	unsigned numberOfDistincts();
	bool contains(T);
	void removeAll(T);
	template<typename T, typename P>
	friend ostream& operator << (ostream&, const Multiset<T,P>&);
};

template <typename T,typename P>
Multiset<T,P>::Multiset() {
	Buckets.resize(16);
	this->capacity = 16;
	this->loadFactor = 0.75;
}

template<typename T, typename P>
void Multiset<T, P>::insert(T val) {
	//cout << Hash(val) << " ";
	Buckets[Hash(val) % capacity].insert(val);
}

template<typename T, typename P>
ostream& operator << (ostream& out, const Multiset<T, P>& multiset) {
	for (Bucket<T> bucket : multiset.Buckets) {
		if(!bucket.isEmpty())
		out << bucket << " "<<endl;
		//out << "pula" << " ";
	}
		return out;
}

template<typename T, typename P>
void Multiset<T, P>::remove(T element) {
	Buckets[Hash(element) % capacity].remove(element);
}

template<typename T, typename P>
unsigned Multiset<T, P>::numberOf(T val) {
	return Buckets[Hash(val) % capacity].numberOf(val);
}

template<typename T, typename P>
unsigned Multiset<T, P>::numberOfDistincts() {
	unsigned total = 0;
	for (Bucket<T> bucket : Buckets) {
		total += bucket.numberOfDistinct();
	}
	return total;
}

template<typename T, typename P>
bool Multiset<T, P>::contains(T val) {
	return Buckets[Hash(val) % capacity].contains(val);
}

template<typename T, typename P>
void Multiset<T, P>::removeAll(T val) {
	Bucket<T>* bucket = &Buckets[Hash(val) % capacity];
	while (bucket->contains(val)) {
		bucket->remove(val);
	}
}

/*
template < typename T, typename P >
void Multiset<T, P>::numbersAreEqual() {
	P b;
	if ( b(a[0]) == b(a[1]) ) {
		cout << "yes";
	}
	else {
		cout << "no";
	}
	
}
*/