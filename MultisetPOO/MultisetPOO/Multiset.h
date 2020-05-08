#pragma once
#include <iostream>
#include "Comparator.h"
using namespace std;

template < typename T, typename P = Comparator<T> >
class Multiset
{
public:
	int a[2];
	void numbersAreEqual();
};


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
