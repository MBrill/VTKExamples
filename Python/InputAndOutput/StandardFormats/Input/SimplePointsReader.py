#!/usr/bin/env python

import vtk


def get_program_parameters():
    import argparse
    description = 'Read a .txt file'
    epilogue = '''
   '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue)
    parser.add_argument('filename', help='filename.txt')
    args = parser.parse_args()
    return args.filename


def main():
    # Get all data from the file
    filename = get_program_parameters()
    colors = vtk.vtkNamedColors()

    # Read the file
    reader = vtk.vtkSimplePointsReader()
    reader.SetFileName(filename)
    reader.Update()

    # Visualize
    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputConnection(reader.GetOutputPort())

    actor = vtk.vtkActor()
    actor.SetMapper(mapper)
    actor.GetProperty().SetPointSize(4)

    renderer = vtk.vtkRenderer()
    renderer.AddActor(actor)

    renderer.SetBackground(colors.GetColor3d("Azure"))

    render_window = vtk.vtkRenderWindow()
    render_window.AddRenderer(renderer)

    render_window_interactor = vtk.vtkRenderWindowInteractor()
    render_window_interactor.SetRenderWindow(render_window)

    render_window_interactor.Start()


if __name__ == '__main__':
    main()
