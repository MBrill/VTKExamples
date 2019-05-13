#!/usr/bin/env python

import vtk


def main():
    # Disabled by default with gcc or visual studio.
    # Enabled by default by Borland CC.
    vtk.vtkFloatingPointExceptions.Enable()

    x = 0.0
    y = 1.0 / x  # floating - point exception

    print("x:", x, "y:", y)


if __name__ == '__main__':
    main()
