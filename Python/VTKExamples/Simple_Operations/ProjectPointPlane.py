#!/usr/bin/env python

import vtk


def main():
    plane = vtk.vtkPlane()
    plane.SetOrigin(0.0, 0.0, 0.0)
    plane.SetNormal(0.0, 0.0, 1.0)

    p = [23.1, 54.6, 9.2]
    origin = [0.0, 0.0, 0.0]
    normal = [0.0, 0.0, 1.0]
    projected = [0.0, 0.0, 0.0]

    plane.ProjectPoint(p, origin, normal, projected)

    print("Projected:", projected[0], projected[1], projected[2])


if __name__ == '__main__':
    main()
