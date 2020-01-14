#!/usr/bin/env python

import vtk


def get_program_parameters():
    import argparse
    description = 'Read a structured points (.vtk) file.'
    epilogue = '''
   '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue)
    parser.add_argument('filename', help='ironProt.vtk')
    args = parser.parse_args()
    return args.filename


def main():
    filename = get_program_parameters()

    # Read the file
    reader = vtk.vtkStructuredPointsReader()

    reader.SetFileName(filename)
    reader.Update()

    geometry_filter = vtk.vtkImageDataGeometryFilter()
    geometry_filter.SetInputConnection(reader.GetOutputPort())
    geometry_filter.Update()

    # Visualize
    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputConnection(geometry_filter.GetOutputPort())

    actor = vtk.vtkActor()
    actor.SetMapper(mapper)

    renderer = vtk.vtkRenderer()
    render_window = vtk.vtkRenderWindow()
    render_window.AddRenderer(renderer)
    render_window_interactor = vtk.vtkRenderWindowInteractor()
    render_window_interactor.SetRenderWindow(render_window)

    renderer.AddActor(actor)

    named_colors = vtk.vtkNamedColors()
    renderer.SetBackground(named_colors.GetColor3d("Green"))

    render_window.Render()
    render_window_interactor.Start()


if __name__ == '__main__':
    main()
