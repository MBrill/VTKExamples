#!/usr/bin/env python

import vtk


def get_program_parameters():
    import argparse
    description = 'Read a .ply file'
    epilogue = '''
   '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue)
    parser.add_argument('filename', help='filename.ply')
    args = parser.parse_args()
    return args.filename


def main():
    filename = get_program_parameters()
    colors = vtk.vtkNamedColors()

    reader = vtk.vtkPLYReader()
    reader.SetFileName(filename)

    # Visualize
    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputConnection(reader.GetOutputPort())

    actor = vtk.vtkActor()
    actor.SetMapper(mapper)

    renderer = vtk.vtkRenderer()
    render_window = vtk.vtkRenderWindow()
    render_window.AddRenderer(renderer)
    render_window_interactor = vtk.vtkRenderWindowInteractor()
    render_window_interactor.SetRenderWindow(render_window)

    renderer.AddActor(actor)
    renderer.SetBackground(colors.GetColor3d("SeaGreen"))

    render_window.Render()
    render_window_interactor.Start()


if __name__ == '__main__':
    main()
