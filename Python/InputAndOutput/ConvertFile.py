#!/usr/bin/env python

import vtk


def get_program_parameters():
    import argparse
    description = 'Read a .vtp file and .ply file'
    epilogue = '''
   '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue)
    parser.add_argument('filename_input', help='input.vtp')
    parser.add_argument('filename_output', help='output.ply')
    args = parser.parse_args()
    return args.filename_input, args.filename_output


def main():
    filename_input, filename_output = get_program_parameters()

    reader = vtk.vtkXMLPolyDataReader()
    reader.SetFileName(filename_input)
    reader.Update()

    writer = vtk.vtkPLYWriter()
    writer.SetFileName(filename_output)
    writer.SetInputConnection(reader.GetOutputPort())
    writer.Update()


if __name__ == '__main__':
    main()
