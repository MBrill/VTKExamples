#!/usr/bin/env python

import vtk


def get_program_parameters():
    import argparse
    description = 'Read a .vts file'
    epilogue = '''
   '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue)
    parser.add_argument('filename', help='multicomb_0.vts')
    args = parser.parse_args()
    return args.filename


def main():
    filename = get_program_parameters()
    colors = vtk.vtkNamedColors()

    # Read the file
    reader = vtk.vtkXMLStructuredGridReader()
    reader.SetFileName(filename)
    reader.Update()

    geometry_filter = vtk.vtkStructuredGridGeometryFilter()
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
    renderer.SetBackground(colors.GetColor3d("Green"))

    render_window.Render()
    render_window_interactor.Start()


if __name__ == '__main__':
    main()
