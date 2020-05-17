#include <iostream>
#include <string>
#include <cassert>
#include <time.h>  
#include "Multiset.h"
using namespace std;

void testerAssert();
void testerAfisat();

int main()
{   
    //testerAfisat();
    testerAssert();

    return 0;
}


void testerAssert() {
    Multiset<int> inturi;

    inturi.insert(23);
    assert(inturi.contains(23));  //test inserare si continere

    inturi.remove(23);
    assert(!inturi.contains(23));   //test remove

    for (int i = 0; i < 5; i++) {
        inturi.insert(12);
    }
    assert(inturi.numberOf(12) == 5); //test numberOf

    inturi.removeAll(12);
    assert((inturi.contains(12) == inturi.numberOf(12)) && inturi.contains(12) == false); // test contains & numberOf

    try {
        inturi.remove(25);
    }
    catch (invalid_argument) {      //test element invalid
        assert(true);
    }

    for (int i = 0; i < 11; i++) {
        inturi.insert(i);
    }

    assert(inturi.numberOfDistincts() == 11);   //test numberOfDistincts

    for (int i = 11; i < 100; i++) {
        inturi.insert(i);
    }

    for (int i = 0; i < 100; i++) {
        assert(inturi.numberOf(i) == 1);           //test rehashing
    }

    Multiset<double> doubles;

    doubles.insert(3.14);
    assert(doubles.contains(20.14));       //test comparator specializat 

}

void testerAfisat() {
    Multiset<int> inturi;
    int numere[] = { 24,27,89,56,123,76,98,98,23,67,125 }; // adaugam 11 elemente

    for (int i : numere) {
        inturi.insert(i);
    }
    cout << endl << "multiset cu 11 elemente inainte de rehash:"<<endl;
    cout << inturi;

    inturi.insert(1023); // la al 12-lea se face rehash deoarece numarul elementelor depaseste loadFactor * capacity
    cout << endl << "multiset cu 12 elemente dupa rehash:";
    cout << endl;
    cout << inturi;

    srand(time(NULL));

    for (int i = 0; i < 100; i++) {
        inturi.insert(rand() % 10000);
    }
    cout << endl << "multiset cu 112 elemente random :";
    cout << endl;
    cout << inturi;
}
