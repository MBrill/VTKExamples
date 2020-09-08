#!/usr/bin/env python

import vtk


def main():
    # Create 10 points.
    points = vtk.vtkPoints()

    for i in range(0, 20):
        points.InsertNextPoint(i, i, i)

    # Create a polydata object and add the points to it.
    polydata = vtk.vtkPolyData()
    polydata.SetPoints(points)

    # Write the file
    writer = vtk.vtkXMLPolyDataWriter()
    writer.SetFileName("test.vtp")
    writer.SetInputData(polydata)

    # Optional - set the mode.The default is binary.
    # writer.SetDataModeToBinary()
    # writer.SetDataModeToAscii()

    writer.Write()


if __name__ == '__main__':
    main()
