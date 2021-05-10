# --------------------------------------------------------------------------
# Einführendes Beispiel für die Verwendung von  
# CTest (Unit-Tests) für 
# plattform-unabhängige Builds.
# --------------------------------------------------------------------------
# CMake-Version
cmake_minimum_required (VERSION 3.20)

# Wie heisst das Projekt?
project (UnitTest)

# Wir konfigurieren unser Build-System

# Wir fügen einen Ordner hinzu, in dem Header gesucht werden
# Das Verzeichnis, in dem sich die Quellen des Projekts helloCMake
# befinden ist als CMake-Variable verfügbar.
include_directories(${helloCMake_SOURCE_DIR})

# Falls Visual Studio besondere Definitionen benötigt
# definieren wir für g++ unter Cygwin die Opion -mwin32.
# Dann setzt g++ wie Microsoft Visual Studio die
# Präprozessorvariable _WIN32.
# Abhängig von der verwendeten Build-Umgebung können wir
# Optionen verändern.
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
add_executable (mainTest mainTest.cpp Compute.cpp Compute.h) 

#   Unit-Tests mit CTest

# Test-Support aktivieren
enable_testing()

# Für jeden Test fügen wir ein Build-Target, im Beispiel ist das mainTest hinzu.
# Hat das durchgeführte Hauptprogramm den Return-Code Null, dann
# war der Test erfolgreich. Es ist auch möglich, im Testtreiber
# Ausgaben auf stdout zu machen und innerhalb von ctest diese Ausgaben
# auch regular expressions zu überprüfen. Mehr dazu finden Sie im
# CMake-Wiki auf www.cmake.org.
add_test(test1 mainTest)