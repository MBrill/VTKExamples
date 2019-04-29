Schritt 1: vtkEventData.h muss manuell aus den Sourcedateien in den VTK Installationsordner zu den anderen Header kopiert werden.
Schritt 2: Folgende Klassen ersetzen die StandardRenderer Klassen:

#include <vtkOpenVRRenderWindow.h>
#include <vtkOpenVRRenderer.h>
#include <vtkOpenVRRenderWindowInteractor.h>
#include <vtkOpenVRCamera.h>

Schritt 3: SteamVR (Runtime) muss laufen, damit das auszuführende Programm funktioniert