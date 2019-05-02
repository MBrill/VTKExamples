#!/usr/bin/env python

import vtk


def get_program_parameters():
    import argparse
    description = 'Read a .vtu file or .vtp file'
    epilogue = '''
   '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue)
    parser.add_argument('filename', help='')
    args = parser.parse_args()
    return args.filename


def main():
    filename = get_program_parameters()

    # Get all data from the file
    reader = vtk.vtkXMLGenericDataObjectReader()
    reader.SetFileName(filename)
    reader.Update()

    # All of the standard data types can be checked and obtained like this:
    if isinstance(reader.GetOutput(), vtk.vtkPolyData):
        print("File is a polydata")

    elif isinstance(reader.GetOutput(), vtk.vtkUnstructuredGrid):
        print("File is an unstructured grid")

    # Visualize
    colors = vtk.vtkNamedColors()
    mapper = vtk.vtkDataSetMapper()
    mapper.SetInputConnection(reader.GetOutputPort())

    actor = vtk.vtkActor()
    actor.SetMapper(mapper)
    actor.GetProperty().SetColor(colors.GetColor3d("Moccasin"))

    renderer = vtk.vtkRenderer()
    render_window = vtk.vtkRenderWindow()
    render_window.AddRenderer(renderer)
    render_window_interactor = vtk.vtkRenderWindowInteractor()
    render_window_interactor.SetRenderWindow(render_window)

    renderer.AddActor(actor)
    renderer.SetBackground(colors.GetColor3d("SlateGray"))

    render_window.SetSize(640, 480)
    render_window.Render()
    render_window_interactor.Start()


if __name__ == '__main__':
    main()
