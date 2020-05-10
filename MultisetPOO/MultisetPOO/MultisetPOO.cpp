#include <iostream>
#include <string>
#include "Multiset.h"
using namespace std;

int main()
{
    Multiset<float> m;
    Multiset<string>p;

    m.insert(4.2f);
    m.insert(4);
    m.insert(4);
    m.insert(5);
    m.insert(4);
    m.insert(20);
    m.insert(22);
    m.insert(38);
    m.insert(34);
    
    p.insert("mama");
    p.insert("mama");
    p.insert("mama");
    p.insert("kiksd");
    p.insert("ma-ta");
    p.insert("ta-ta");
    p.insert("trrta");
    p.insert("trrrr");
    p.insert("rttrtra-ta");

    p.remove("mama");
    //m.remove(38);
    cout << p;
    
    return 0;
}

