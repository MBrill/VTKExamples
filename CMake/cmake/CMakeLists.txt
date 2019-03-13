# --------------------------------------------------------------------------
# Einführendes Beispiel für die Verwendung von CMake für 
# plattform-unabhängige Builds.
# --------------------------------------------------------------------------
# CMake-Version
cmake_minimum_required (VERSION 3.10)
# Wie heisst das Projekt?
project (helloCMake)

# Dokumentation mit doxygen erstellen
INCLUDE(CMakeDoxygen.txt)

# Wir konfigurieren unser Build-System

# Wir fügen einen Ordner hinzu, in dem Header gesucht werden
# Das Verzeichnis, in dem sich die Quellen des Projekts helloCMake
# befinden ist als CMake-Variable verfügbar.
include_directories(${helloCMake_SOURCE_DIR})


# Abhängig von der verwendeten Build-Umgebung können wir
# Optionen verändern.
#
# Hier wird eine Option für den Option für den GNU-Compiler
# in Cygwin gesetzt. Microsoft Visual Studio setzt das
# Symbol win32 als Default; mit der folgenden Definition
# können wir im Quelltext mit ifdef auf das Symbol zugreifen.
if(CYGWIN)
	    add_definitions(-mwin32)
endif()

# Falls wir Microsoft Visual Studio verwenden ist MSVC true.
# Auch die verwendete Version kann abgefragt werden, falls wir
# das benötigen.
# Microsoft Visual Studio dazu bringen cmath wie im Standard zu verwenden
# und die lästigen Warnings für Konsolen-Anwendungen sein zu lassen.
if(MSVC)
        add_definitions(-D_USE_MATH_DEFINES)
	    add_definitions(-D_CRT_SECURE_NO_WARNINGS)      
endif()

# Mit add_executable definieren wir ein neues Target, gefolgt
# von den Voraussetzungen.
#
# In unserem ersten Beispiel haben wir ein Hauptprogramm in der Datei
# main.cpp, und eine Klasse für die Berechnung der Summe zweier ganzer Zahlen
# in den Dateien Compute.h und Compute.cpp.
add_executable (main main.cpp Compute.cpp Compute.h) 
