# --------------------------------------------------------------------------
# Einf�hrendes Beispiel f�r die Verwendung von CMake f�r 
# plattform-unabh�ngige Builds.
# --------------------------------------------------------------------------
# CMake-Version
cmake_minimum_required (VERSION 3.10)
# Wie heisst das Projekt?
project (helloCMake)

# Dokumentation mit doxygen erstellen
INCLUDE(CMakeDoxygen.txt)

# Wir konfigurieren unser Build-System

# Wir f�gen einen Ordner hinzu, in dem Header gesucht werden
# Das Verzeichnis, in dem sich die Quellen des Projekts helloCMake
# befinden ist als CMake-Variable verf�gbar.
include_directories(${helloCMake_SOURCE_DIR})


# Abh�ngig von der verwendeten Build-Umgebung k�nnen wir
# Optionen ver�ndern.
#
# Hier wird eine Option f�r den Option f�r den GNU-Compiler
# in Cygwin gesetzt. Microsoft Visual Studio setzt das
# Symbol win32 als Default; mit der folgenden Definition
# k�nnen wir im Quelltext mit ifdef auf das Symbol zugreifen.
if(CYGWIN)
	    add_definitions(-mwin32)
endif()

# Falls wir Microsoft Visual Studio verwenden ist MSVC true.
# Auch die verwendete Version kann abgefragt werden, falls wir
# das ben�tigen.
# Microsoft Visual Studio dazu bringen cmath wie im Standard zu verwenden
# und die l�stigen Warnings f�r Konsolen-Anwendungen sein zu lassen.
if(MSVC)
        add_definitions(-D_USE_MATH_DEFINES)
	    add_definitions(-D_CRT_SECURE_NO_WARNINGS)      
endif()

# Mit add_executable definieren wir ein neues Target, gefolgt
# von den Voraussetzungen.
#
# In unserem ersten Beispiel haben wir ein Hauptprogramm in der Datei
# main.cpp, und eine Klasse f�r die Berechnung der Summe zweier ganzer Zahlen
# in den Dateien Compute.h und Compute.cpp.
add_executable (main main.cpp Compute.cpp Compute.h) 
