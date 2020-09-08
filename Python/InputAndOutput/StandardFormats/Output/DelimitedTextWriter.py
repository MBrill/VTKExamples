#!/usr/bin/env python

import vtk


def get_program_parameters():
    import argparse
    description = 'Write into a file'
    epilogue = '''
   '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue)
    parser.add_argument('output_filename', help='output_filename.txt')
    args = parser.parse_args()
    return args.output_filename


def main():
    # Use the specified filename
    output_filename = get_program_parameters()

    # Construct an empty table
    table = vtk.vtkTable()

    for i in range(0, 3):
        col = vtk.vtkVariantArray()
        col_name = "column-" + str(i)
        col.SetName(col_name)

        col.InsertNextValue(vtk.vtkVariant(0.0))
        col.InsertNextValue(vtk.vtkVariant(0.0))
        col.InsertNextValue(vtk.vtkVariant(0.0))
        table.AddColumn(col)

    # Fill the table with values
    counter = 0
    for r in range(0, table.GetNumberOfRows()):
        for c in range(table.GetNumberOfColumns()):
            table.SetValue(r, c, vtk.vtkVariant(counter))
            counter += 1

    writer = vtk.vtkDelimitedTextWriter()
    writer.SetFileName(output_filename)
    writer.SetInputData(table)
    writer.Write()


if __name__ == '__main__':
    main()
