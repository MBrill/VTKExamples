#!/usr/bin/env python

import vtk


def main():
    sphere_source = vtk.vtkSphereSource()
    sphere_source.Update()

    writer = vtk.vtkSimplePointsWriter()
    writer.SetFileName("test.txt")
    writer.SetInputConnection(sphere_source.GetOutputPort())
    writer.Write()


if __name__ == '__main__':
    main()
