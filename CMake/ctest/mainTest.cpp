// ---------------------------------------------------------------------------------------------
// Hauptprogramm f�r die Demonstration der Verwendung von
// Unit-Testing mit ctest
//
// Tests in VS starten: Target RUN_TESTS ausw�hlen und "Erstellen" ausw�hlen.
// Ausgabe der Test-Ergebnisse im Ausgabe-Fenster.
//
// ctest �berpr�ft, ob ein Prozess einen exit-status != 0 besitzt. 
// In der CMakeLists.txt k�nnen auch regular expressions angegeben werden,
// die Ausgaben auf stdout �berpr�fen.
// ---------------------------------------------------------------------------------------------
#include <iostream>
#include "Compute.h"

int main(void)
{
  long a=40, b=2;
  Compute hitchHiker(a, b);
  // Korrektes Ergebnis ist 42
  if ( hitchHiker.compute() != 42)
     return 1;

  return 0;
}
