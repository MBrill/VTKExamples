# ----------------------------------------------------------------------
#  Erste eigene VTK-Anwendung
# ----------------------------------------------------------------------
PROJECT(Anaglyph)
cmake_minimum_required(VERSION 3.13)

# Mehr Ausgaben ...
if(NOT CMAKE_VERBOSE_MAKEFILE)
   set(CMAKE_VERBOSE_MAKEFILE TRUE CACHE STRING "Mehr Ausgaben")
ENDIF(NOT CMAKE_VERBOSE_MAKEFILE)

SET(CMAKE_BUILD_TYPE Release CACHE STRING
      "Nur Release"
      FORCE)

# F�r Visual Studio (ein "multi-target IDE" muss die folgende Variable ver�ndert werden
set(CMAKE_CONFIGURATION_TYPES "Release" CACHE STRING "Nur Release" FORCE)

# Compiler-Einstellungen f�r Microsoft Visual Studio
if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    add_definitions(-D_USE_MATH_DEFINES -DGLUT_BUILDING_LIB)
endif()

# XCode arbeitet scheinbar nicht mit relativen Pfadangaben
if(NOT APPLE) 
    # Use relative paths
    set(CMAKE_USE_RELATIVE_PATHS TRUE CACHE STRING "Relative Pfade")
endif(NOT APPLE)

# Option f�r Gcc unter Cygwin
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
  ADD_EXECUTABLE(redblue redblue.cpp)
  TARGET_LINK_LIBRARIES(redblue ${VTK_LIBRARIES})
  ADD_EXECUTABLE(redcyan redcyan.cpp)
  TARGET_LINK_LIBRARIES(redcyan ${VTK_LIBRARIES})
  ADD_EXECUTABLE(colormask colormask.cpp)
  TARGET_LINK_LIBRARIES(colormask ${VTK_LIBRARIES})
ELSE(VTK_FOUND)
	message(FATAL_ERROR "Binary kann ohne VTK nicht gebaut werden! Setzen Sie die Variable VTK_DIR als Umgebungsvariable oder in der CMake-Eingabe!")
ENDIF(VTK_FOUND)
