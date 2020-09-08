#!/usr/bin/env python

import vtk


def get_program_parameters():
    import argparse
    description = 'Read a .dem file'
    epilogue = '''
    '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue)
    parser.add_argument('filename', help='filename.dem')
    args = parser.parse_args()
    return args.filename


def main():
    filename = get_program_parameters()
    colors = vtk.vtkNamedColors()

    # Read the file
    reader = vtk.vtkDEMReader()
    reader.SetFileName(filename)
    reader.Update()

    lut = vtk.vtkLookupTable()
    lut.SetHueRange(0.6, 0)
    lut.SetSaturationRange(1.0, 0)
    lut.SetValueRange(0.5, 1.0)
    lut.SetTableRange(reader.GetOutput().GetScalarRange())

    # Visualize
    map_colors = vtk.vtkImageMapToColors()
    map_colors.SetLookupTable(lut)
    map_colors.SetInputConnection(reader.GetOutputPort())

    # Create an actor
    actor = vtk.vtkImageActor()
    actor.GetMapper().SetInputConnection(map_colors.GetOutputPort())

    # Setup renderer
    renderer = vtk.vtkRenderer()
    renderer.AddActor(actor)
    renderer.ResetCamera()
    renderer.SetBackground(colors.GetColor3d("Azure"))

    # Setup render window
    render_window = vtk.vtkRenderWindow()
    render_window.AddRenderer(renderer)

    # Setup render window interactor
    render_window_interactor = vtk.vtkRenderWindowInteractor()

    style = vtk.vtkInteractorStyleImage()

    render_window_interactor.SetInteractorStyle(style)

    # Render and start interaction
    render_window_interactor.SetRenderWindow(render_window)
    render_window.Render()
    render_window_interactor.Initialize()

    render_window_interactor.Start()


if __name__ == '__main__':
    main()
