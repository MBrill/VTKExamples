// --------------------------------------------------------------------
//  (C) Copyright Manfred Brill 2019.
// --------------------------------------------------------------------
//  Implementierung
// --------------------------------------------------------------------
#include "Compute.h"


// Konstruktor
Compute::Compute(void) : a(1), b(1) {}

// Kopierkonstruktor
Compute::Compute(Compute &copy) : a(copy.a), b(copy.b) {}

// Konstruktor mit den beiden Zahlen
Compute::Compute(long first, long second) : a(first), b(second) {}

// Den ersten Summanden setzen
void Compute::setA(long i)
{
    a = i;
}

// Den zweiten Summanden setzen
void Compute::setB(long i)
{
    b = i;
}

// Die Berechnung durchführen
long Compute::compute()
{
    return a+b;
}

