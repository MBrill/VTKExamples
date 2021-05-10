// ---------------------------------------------------------------------------------------------
// Hauptprogramm für die Demonstration der Verwendung von
// Unit-Testing mit ctest
//
// Tests in VS starten: Target RUN_TESTS auswählen und "Erstellen" auswählen.
// Ausgabe der Test-Ergebnisse im Ausgabe-Fenster.
//
// ctest überprüft, ob ein Prozess einen exit-status != 0 besitzt. 
// In der CMakeLists.txt können auch regular expressions angegeben werden,
// die Ausgaben auf stdout überprüfen.
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
