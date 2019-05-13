#!/usr/bin/env python

import vtk


def main():
    time_source = vtk.vtkTimeSourceExample()

    exodus_writer = vtk.vtkExodusIIWriter()
    exodus_writer.SetFileName("output.exii")
    exodus_writer.SetInputConnection(time_source.GetOutputPort())
    exodus_writer.WriteAllTimeStepsOn()
    exodus_writer.Write()


if __name__ == '__main__':
    main()
