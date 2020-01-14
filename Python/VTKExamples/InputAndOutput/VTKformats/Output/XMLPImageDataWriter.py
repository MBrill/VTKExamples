#!/usr/bin/env python

import vtk


def main():
    drawing = vtk.vtkImageCanvasSource2D()

    drawing.SetNumberOfScalarComponents(3)
    drawing.SetScalarTypeToUnsignedChar()
    drawing.SetExtent(0, 20, 0, 50, 0, 1)
    drawing.SetDrawColor(255.0, 255.0, 255.0)
    drawing.DrawCircle(5, 5, 3)

    number_of_pieces = 4

    writer = vtk.vtkXMLPImageDataWriter()
    writer.SetInputConnection(drawing.GetOutputPort())
    writer.SetFileName("Test.pvti")
    writer.SetNumberOfPieces(number_of_pieces)
    writer.SetEndPiece(number_of_pieces - 1)
    writer.SetStartPiece(0)
    writer.Update()


if __name__ == '__main__':
    main()
