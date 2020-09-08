#!/usr/bin/env python

import vtk


def main():
    # Create a grid
    structured_grid = vtk.vtkStructuredGrid()

    points = vtk.vtkPoints()

    points.InsertNextPoint(0, 0, 0)
    points.InsertNextPoint(1, 0, 0)
    points.InsertNextPoint(0, 1, 0)
    points.InsertNextPoint(1, 1, 0)
    points.InsertNextPoint(0, 2, 0)
    points.InsertNextPoint(1, 2, 1)

    # Specify the dimensions of the grid
    structured_grid.SetDimensions(2, 3, 1)
    structured_grid.SetPoints(points)

    # Write file
    writer = vtk.vtkXMLStructuredGridWriter()
    writer.SetFileName("output.vts")
    writer.SetInputData(structured_grid)
    writer.Write()


if __name__ == '__main__':
    main()
