# ----------------------------------------------------------------------
#  CMake-File für die Marching-Cubes Demo mit dem
#  Übergang zwischen zwei Quadern
# ----------------------------------------------------------------------
PROJECT(MarchingCubesCases)
cmake_minimum_required(VERSION 2.8)

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
set (VTK_DIR "c:/Program Files/VTK/" CACHE STRING "VTK Verzeichnis")
FIND_PACKAGE(VTK REQUIRED)

# Falls VTK gefunden wurde Variablen schicken
IF(VTK_FOUND)
  message(STATUS "VTK gefunden. Version: " ${VTK_VERSION} " " VTK_DIR: ${VTK_DIR})
  include(${VTK_USE_FILE})

  # Die  Build-Targets festlegen
  ADD_EXECUTABLE(mccases1 mccases1.cpp)
  TARGET_LINK_LIBRARIES(mccases1 ${VTK_LIBRARIES})
  ADD_EXECUTABLE(mccases2 mccases2.cpp)
  TARGET_LINK_LIBRARIES(mccases2 ${VTK_LIBRARIES})
ELSE(VTK_FOUND)
	message(FATAL_ERROR "Binary kann ohne VTK nicht gebaut werden! Setzen Sie die Variable VTK_DIR als Umgebungsvariable oder in der CMake-Eingabe!")
ENDIF(VTK_FOUND)
