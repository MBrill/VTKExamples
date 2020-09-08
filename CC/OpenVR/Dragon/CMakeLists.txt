# ----------------------------------------------------------------------
#  Erstes Beispiel einer VTK-Anwendung mit OpenVR-Support
# ----------------------------------------------------------------------
PROJECT(DragonVR)
cmake_minimum_required(VERSION 3.13)

# Mehr Ausgaben ...
if(NOT CMAKE_VERBOSE_MAKEFILE)
   set(CMAKE_VERBOSE_MAKEFILE TRUE CACHE STRING "Mehr Ausgaben")
ENDIF(NOT CMAKE_VERBOSE_MAKEFILE)

SET(CMAKE_BUILD_TYPE Release CACHE STRING
      "Nur Release"
      FORCE)

# Für Visual Studio (ein "multi-target IDE" muss die folgende Variable verändert werden
set(CMAKE_CONFIGURATION_TYPES "Release" CACHE STRING "Nur Release" FORCE)

# Compiler-Einstellungen für Microsoft Visual Studio
if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    add_definitions(-D_USE_MATH_DEFINES -DGLUT_BUILDING_LIB)
endif()

# XCode arbeitet scheinbar nicht mit relativen Pfadangaben
if(NOT APPLE) 
    # Use relative paths
    set(CMAKE_USE_RELATIVE_PATHS TRUE CACHE STRING "Relative Pfade")
endif(NOT APPLE)

# Option für Gcc unter Cygwin
if(CYGWIN)
    add_definitions(-mwin32)
endif()

# -----------------------------------------------------------------------
# Falls VTKRoot nicht gefunden wird, manuell angeben
# -----------------------------------------------------------------------
set (VTK_DIR "D:/Program Files/VTK/" CACHE STRING "VTK Verzeichnis")
FIND_PACKAGE(VTK REQUIRED)

# OpenVR mit CMake finden
# Wert setzen für OPENVR_ROOT_DIR für duke und armstrong
set (OPENVR_ROOT_DIR "D:/Program Files/openvr-master/" CACHE STRING "OpenVR Verzeichnis")

FIND_PACKAGE(OpenVR REQUIRED)
IF(OPENVR_FOUND)
	message(STATUS "OpenVR-Installation gefunden in ${OPENVR_ROOT_DIR}")
	# Kommentar in vtkOpenVRRenderWindow.h - VTK_OPENVR_OBJECT_FACTORY anschalten
    set(VTK_OPENVR_OBJECT_FACTORY TRUE CACHE STRING "Kommentar in vtkOpenVRRenderWindow.h")
ENDIF(OPENVR_FOUND)

# Falls VTK gefunden wurde Variablen schicken
IF(VTK_FOUND)
  message(STATUS "VTK gefunden. Version: " ${VTK_VERSION} " " VTK_DIR: ${VTK_DIR})
  include(${VTK_USE_FILE})

  # Geometriedatei in bin-Verzeichnis kopieren
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/dragon.ply ${CMAKE_CURRENT_BINARY_DIR}/dragon.ply COPYONLY)

  # Das Build-Target festlegen
  ADD_EXECUTABLE(TestDragon TestDragon.cxx)
  TARGET_LINK_LIBRARIES(TestDragon ${VTK_LIBRARIES})
ELSE(VTK_FOUND)
	message(FATAL_ERROR "Binary kann ohne VTK nicht gebaut werden! Setzen Sie die Variable VTK_DIR als Umgebungsvariable oder in der CMake-Eingabe!")
ENDIF(VTK_FOUND)
