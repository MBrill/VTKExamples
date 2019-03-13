#include "Compute.h"

// Konstruktor
Compute::Compute(void) : a(1), b(1) {}

// Kopierkonstruktor
Compute::Compute(Compute &copy) : a(copy.a), b(copy.b) {}

// Konstruktor mit den beiden Zahlen
Compute::Compute(long first, long second) : a(first), b(second) {}

// Den ersten Summanden setzen
void Compute::setA(long n)
{
    a = n;
}

// Den zweiten Summanden setzen
void Compute::setB(long n)
{
    b = n;
}

// Die Berechnung durchführen
long Compute::compute()
{
    return a+b;
}

