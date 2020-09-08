#!/usr/bin/env python

import vtk


def get_program_parameters():
    import argparse
    description = 'Read any type of legacy .vtk file.'
    epilogue = '''
   '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue)
    parser.add_argument('filename', help='')
    args = parser.parse_args()
    return args.filename


def main():
    filename = get_program_parameters()

    # Get all data from the file
    reader = vtk.vtkGenericDataObjectReader()
    reader.SetFileName(filename)
    reader.Update()

    # All of the standard data types can be checked and obtained like this:
    if reader.IsFilePolyData():
        print("output is a polydata")
        output = reader.GetPolyDataOutput()
        print("output has", output.GetNumberOfPoints(), "points.")


if __name__ == '__main__':
    main()
