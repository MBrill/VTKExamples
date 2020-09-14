# VTK Python Examples
This repository contains examples for VTK using Python.

## Coding Guidelines
We use the guidelines to be found in the VTK Examples repo, maintained 
by Bill Lorensen.

Here you find the essentials of the guidelines we use.
- every example starts with the shebang line # !/usr/bin/env python
- we use doc-strings at the beginning of every python-example.
- this doc-string is followed by the line import vtk
- we add a description and an image for the VTK Examples repo.
- we document the main function using a doc-string.
- we document every Python function using doc-string.
- we always use a function get_program_parameters to make sure the nightly 
builds on the vtk-site will run after the pull request
- we do not use white backgrounds for the OpenGL windows, but we 
use, like suggested by Bill Loresen, the named colors to found in 
vtkNamedColors.
- we use 4 blank chars, no tabs!
- every line contains no more than 79 characters
- we use lower caps for function names. Underscores only in case
this character enhances readability. The same rule for variable names.
- 

## Anaconda
We use the Anaconda distribution and Spyder. 
Make sure you use the linter and code analysis to ensure pep8. 
for german users you find this option in *Vervollständigung und Lint*
in *Code-Stil*. Just activate *Linten des Codestils aktivieren*.

Anaconda contains a repository with a VTK package (version 9.01).
Add vtk to a installed Anaconda distribution using the Python console
and


conda install -c conda-forge vtk

You find more on this at the Kitware site.