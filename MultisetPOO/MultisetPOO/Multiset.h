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
	vector <Bucket<T,P> > Buckets;
	unsigned capacity;
	float loadFactor = 0.75;
	unsigned numberOfElements;

public:
	//int a[2];
	//void numbersAreEqual();

	Multiset();
	Multiset(const Multiset&);
	void rehash();
	void insert(T);
	void remove(T);
	unsigned numberOf(T);
	unsigned numberOfDistincts();
	bool contains(T);
	void removeAll(T);
	void operator = (Multiset<T, P>&);
	template<typename T, typename P>
	friend ostream& operator << (ostream&, const Multiset<T,P>&);
	~Multiset();
};

//de pus P in loc de COMPARATOR te rog sa nu uiti !

template <typename T,typename P>
Multiset<T,P>::Multiset() {
	Buckets.resize(16);
	this->capacity = 16;
	this->loadFactor = 0.75;
	this->numberOfElements = 0;
}

template <typename T, typename P>
Multiset<T, P>::Multiset(const Multiset & multiset) : Multiset(){
	vector<T> data;
	for (Bucket<T, P> bucket : multiset.Buckets) {
		for (T el : bucket.getElements()) {
			data.push_back(el);
		}
	}
	for (T el : data) {
		this->insert(el);
	}
}

template <typename T, typename P>
void Multiset<T, P>::rehash() {
	vector<T> data;
	for (Bucket<T,P> bucket : Buckets) {
		for (T el : bucket.getElements()) {
			data.push_back(el);
		}
	}
	for (Bucket<T,P> &bucket : Buckets) {
		if(!bucket.isEmpty())
		bucket.deleteBucket();
	}
	numberOfElements = 0;

	capacity *= 2;
	Buckets.resize(capacity);


	for (T el : data) {
		insert(el);
	}
}

template<typename T, typename P>
void Multiset<T, P>::insert(T val) {
	Buckets[Hash(val) % capacity].insert(val);
	numberOfElements++;

	if (numberOfElements >= loadFactor * capacity) {
		this->rehash();
	}
}

template<typename T, typename P>
ostream& operator << (ostream& out, const Multiset<T, P>& multiset) {
	for (Bucket<T,P> bucket : multiset.Buckets) {
		if(!bucket.isEmpty())
		out << bucket << " "<<endl;
	}
		return out;
}

template<typename T, typename P>
void Multiset<T, P>::remove(T element) {
	Buckets[Hash(element) % capacity].remove(element);
	if (this->contains(element)) {
		numberOfElements--;
	}
}

template<typename T, typename P>
unsigned Multiset<T, P>::numberOf(T val) {
	return Buckets[Hash(val) % capacity].numberOf(val);
}

template<typename T, typename P>
unsigned Multiset<T, P>::numberOfDistincts() {
	unsigned total = 0;
	for (Bucket<T,P> bucket : Buckets) {
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
	Bucket<T,P>* bucket = &Buckets[Hash(val) % capacity];
	while (bucket->contains(val)) {
		bucket->remove(val);
	}
}

template<typename T, typename P>
void Multiset<T, P>::operator = (Multiset<T, P>& multiset) {
	vector<T> data;
	for (Bucket<T, P> bucket : multiset.Buckets) {
		for (T el : bucket.getElements()) {
			data.push_back(el);
		}
	}
	for (T el : data) {
		this->insert(el);
	}
}

template<typename T, typename P>
Multiset<T, P>::~Multiset() {
	for (Bucket<T, P>& bucket : Buckets) {
		if (!bucket.isEmpty()) {
			bucket.deleteBucket();
		}
	}

	//cout << "s-a distrus";
}