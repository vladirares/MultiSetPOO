#include <iostream>
#include <string>
#include "Multiset.h"
using namespace std;

int main()
{
    Multiset<int> m;
    Multiset<string>p;

    m.insert(4);
    m.insert(5);
    m.insert(4);
    m.insert(20);
    m.insert(21);
    m.insert(22);
    m.insert(38);
    
    p.insert("mama");
    p.insert("kiksd");
    p.insert("ma-ta");
    p.insert("ta-ta");
    p.insert("trrta");
    p.insert("trrrr");
    p.insert("rttrtra-ta");

    cout << p;
    
    return 0;
}

