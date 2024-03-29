# --------------------------------------------------------------------------
# Einf�hrendes Beispiel f�r die Verwendung von  
# CTest (Unit-Tests) f�r 
# plattform-unabh�ngige Builds.
# --------------------------------------------------------------------------
# CMake-Version
cmake_minimum_required (VERSION 3.20)

# Wie heisst das Projekt?
project (UnitTest)

# Wir konfigurieren unser Build-System

# Wir f�gen einen Ordner hinzu, in dem Header gesucht werden
# Das Verzeichnis, in dem sich die Quellen des Projekts helloCMake
# befinden ist als CMake-Variable verf�gbar.
include_directories(${helloCMake_SOURCE_DIR})

# Falls Visual Studio besondere Definitionen ben�tigt
# definieren wir f�r g++ unter Cygwin die Opion -mwin32.
# Dann setzt g++ wie Microsoft Visual Studio die
# Pr�prozessorvariable _WIN32.
# Abh�ngig von der verwendeten Build-Umgebung k�nnen wir
# Optionen ver�ndern.
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
add_executable (mainTest mainTest.cpp Compute.cpp Compute.h) 

#   Unit-Tests mit CTest

# Test-Support aktivieren
enable_testing()

# F�r jeden Test f�gen wir ein Build-Target, im Beispiel ist das mainTest hinzu.
# Hat das durchgef�hrte Hauptprogramm den Return-Code Null, dann
# war der Test erfolgreich. Es ist auch m�glich, im Testtreiber
# Ausgaben auf stdout zu machen und innerhalb von ctest diese Ausgaben
# auch regular expressions zu �berpr�fen. Mehr dazu finden Sie im
# CMake-Wiki auf www.cmake.org.
add_test(test1 mainTest)