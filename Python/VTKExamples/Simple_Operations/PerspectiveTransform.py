#!/usr/bin/env python

import vtk


def main():
    m = vtk.vtkMatrix4x4()
    m.SetElement(0, 0, 1)
    m.SetElement(0, 1, 2)
    m.SetElement(0, 2, 3)
    m.SetElement(0, 3, 4)
    m.SetElement(1, 0, 2)
    m.SetElement(1, 1, 2)
    m.SetElement(1, 2, 3)
    m.SetElement(1, 3, 4)
    m.SetElement(2, 0, 3)
    m.SetElement(2, 1, 2)
    m.SetElement(2, 2, 3)
    m.SetElement(2, 3, 4)
    m.SetElement(3, 0, 4)
    m.SetElement(3, 1, 2)
    m.SetElement(3, 2, 3)
    m.SetElement(3, 3, 4)

    perspective_transform = vtk.vtkPerspectiveTransform()
    perspective_transform.SetMatrix(m)

    transform = vtk.vtkTransform()
    transform.SetMatrix(m)

    p = [1.0, 2.0, 3.0]

    normal_projection = [0.0, 0.0, 0.0]
    transform.TransformPoint(p, normal_projection)

    print(
        "Standard projection:",
        normal_projection[0],
        normal_projection[1],
        normal_projection[2])

    perspective_projection = [0.0, 0.0, 0.0]
    perspective_transform.TransformPoint(p, perspective_projection)
    print(
        "Perspective projection:",
        perspective_projection[0],
        perspective_projection[1],
        perspective_projection[2])


if __name__ == '__main__':
    main()
