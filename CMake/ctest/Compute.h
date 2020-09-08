// --------------------------------------------------------------------
//  (C) Copyright Manfred Brill 2019.
// --------------------------------------------------------------------
//  Klasse als Beispiel für den Einsatz von CMake.
//  Diese Klasse berechnet die Summe von zwei long-Zahlen.
// --------------------------------------------------------------------
#ifndef COMPUTE_H
#define COMPUTE_H


//! Klasse für die Berechnung der Summe von zwei ganzen Zahlen
class Compute 
{
//
// public
//
public:
    //! Konstruktor
    /*!
     * Defaultwerte:
     *    erste Zahl a=1,
     *    zweite Zahl b=1.
     */
    Compute(void);
    //! Kopierkonstruktor
    Compute(Compute &copy);
    //! Konstruktor mit zwei ganzen Zahlen
    /*!
     * @param first   erster Summand
     * @param second  zweiter Summand     
     */
    Compute(long first, long second);
    //! Die Berechnung durchführen
    long compute();
    //! Den ersten Summanden setzen
    void setA(long);
    //! Den zweiten Summanden setzen
    void setB(long);
    //! Den ersten Summanden abfragen
    long getA() const;
    //! Den zweiten Summanden abfragen
    long getB() const;

//
// private
//
protected:
    //! Der erste Summand
    long a;
    //! Der zweite Summand
    long b;
};

// ------------------- Inline Sektion -----------------------------
inline long Compute::getA() const { return a;}

inline long Compute::getB() const  { return b;}
#endif /* FIBO_H */
