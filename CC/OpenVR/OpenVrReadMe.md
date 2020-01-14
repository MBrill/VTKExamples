Schritt 1: vtkEventData.h muss manuell aus den Sourcedateien in den VTK Installationsordner zu den anderen Header kopiert werden.
Schritt 2: Folgende Klassen ersetzen die StandardRenderer Klassen:

#include <vtkOpenVRRenderWindow.h>
#include <vtkOpenVRRenderer.h>
#include <vtkOpenVRRenderWindowInteractor.h>
#include <vtkOpenVRCamera.h>

Schritt 3: SteamVR (Runtime) muss laufen, damit das auszuführende Programm funktioniert

Notizen:

Fehler: .dll-8.2 not found: Dlls werden möglicherweise von anderem Benutzer genutzt. 

-> Lösung: anderen Benutzer abmelden oder Computer neustarten.

Fehler: Programme schließen sich direkt wieder nach dem Start

->Lösung 1: OpenVRCamera wurde nicht oder nicht richtig verwendet

->Lösung 2: Fehlende Datei. Ein Programm benötigt möglicherweise eine Datei, die als Argument übergeben wird.