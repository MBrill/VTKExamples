#!/usr/bin/env python
"""
VTK Python example DistancePointToLine.

Damit der linter zufrieden ist noch eine Zeile.
"""

import vtk


def main():
    """
    main-function for the DistancePointOfLine example.

    Returns
    -------
    None.
    """
    # Definition of the line
    line_p0 = (0.0, 0.0, 0.0)
    line_p1 = (2.0, 0.0, 0.0)
    # points for the computation
    p0 = (1.0, 0, 0)
    p1 = (1.0, 2.0, 0)

    dist0 = vtk.vtkLine.DistanceToLine(p0, line_p0, line_p1)
    print("Dist0:", dist0)

    dist1 = vtk.vtkLine.DistanceToLine(p1, line_p0, line_p1)
    print("Dist1:", dist1)

    t = vtk.reference(0.0)
    closest = [0.0, 0.0, 0.0]
    dist0 = vtk.vtkLine.DistanceToLine(p0, line_p0, line_p1, t, closest)
    print(
        "Dist0:",
        dist0,
        "closest point:",
        closest[0],
        closest[1],
        closest[2])

    dist1 = vtk.vtkLine.DistanceToLine(p1, line_p0, line_p1, t, closest)
    print("Dist1:",
          dist1,
          "closest point:",
          closest[0],
          closest[1],
          closest[2])


if __name__ == '__main__':
    main()
