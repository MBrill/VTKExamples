#!/usr/bin/env python

import vtk


def main():
    sphere_source = vtk.vtkSphereSource()

    sphere_source.Update()

    delaunay = vtk.vtkDelaunay3D()
    delaunay.SetInputConnection(sphere_source.GetOutputPort())
    delaunay.Update()

    writer = vtk.vtkXMLPUnstructuredGridWriter()
    writer.SetInputConnection(delaunay.GetOutputPort())
    writer.SetFileName("Test.pvtu")
    writer.SetNumberOfPieces(4)
    writer.SetStartPiece(0)
    writer.SetEndPiece(3)
    writer.Update()


if __name__ == '__main__':
    main()
