#include <iostream>
#include "Multiset.h"

int main()
{
    Multiset<int> m;

    m.a[0] = 3;
    m.a[1] = 3;

    m.numbersAreEqual();
}

