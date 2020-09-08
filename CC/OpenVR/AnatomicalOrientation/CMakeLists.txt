
# ----------------------------------------------------------------------
#  Erste eigene VTK-Anwendung
# ----------------------------------------------------------------------
PROJECT(AnatomicalOrientation)
cmake_minimum_required(VERSION 3.13)

# Mehr Ausgaben ...
if(NOT CMAKE_VERBOSE_MAKEFILE)
   set(CMAKE_VERBOSE_MAKEFILE TRUE CACHE STRING "Mehr Ausgaben")
ENDIF(NOT CMAKE_VERBOSE_MAKEFILE)

SET(CMAKE_BUILD_TYPE Release CACHE STRING
      "Nur Release"
      FORCE)

# Fr Visual Studio (ein "multi-target IDE" muss die folgende Variable verndert werden
set(CMAKE_CONFIGURATION_TYPES "Release" CACHE STRING "Nur Release" FORCE)

# Compiler-Einstellungen fr Microsoft Visual Studio
if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    add_definitions(-D_USE_MATH_DEFINES -DGLUT_BUILDING_LIB)
endif()

# XCode arbeitet scheinbar nicht mit relativen Pfadangaben
if(NOT APPLE) 
    # Use relative paths
    set(CMAKE_USE_RELATIVE_PATHS TRUE CACHE STRING "Relative Pfade")
endif(NOT APPLE)

# Option fr Gcc unter Cygwin
if(CYGWIN)
    add_definitions(-mwin32)
endif()

# -----------------------------------------------------------------------
# Falls VTK_DIR nicht gefunden wird, manuell angeben
# -----------------------------------------------------------------------
set (VTK_DIR "D:/Program Files/VTK/" CACHE STRING "VTK Verzeichnis")
FIND_PACKAGE(VTK REQUIRED)

# Falls VTK gefunden wurde Variablen schicken
IF(VTK_FOUND)
  message(STATUS "VTK gefunden. Version: " ${VTK_VERSION} " " VTK_DIR: ${VTK_DIR})
  include(${VTK_USE_FILE})

  # Das Build-Target festlegen
  ADD_EXECUTABLE(AnatomicalOrientation AnatomicalOrientation.cxx)
  TARGET_LINK_LIBRARIES(AnatomicalOrientation ${VTK_LIBRARIES})
ELSE(VTK_FOUND)
	message(FATAL_ERROR "Binary kann ohne VTK nicht gebaut werden! Setzen Sie die Variable VTK_DIR als Umgebungsvariable oder in der CMake-Eingabe!")
ENDIF(VTK_FOUND)
