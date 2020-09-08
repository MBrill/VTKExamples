#!/usr/bin/env python

import vtk


def get_program_parameters():
    import argparse
    description = 'Read a .obj file'
    epilogue = '''
   '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue)
    parser.add_argument('filename', help='filename.obj')
    args = parser.parse_args()
    return args.filename


def main():
    filename = get_program_parameters()

    reader = vtk.vtkOBJReader()
    reader.SetFileName(filename)
    reader.Update()

    # Visualize
    colors = vtk.vtkNamedColors()
    background_color = colors.GetColor3d("SpringGreen")
    actor_color = colors.GetColor3d("HoneyDew")

    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputConnection(reader.GetOutputPort())

    actor = vtk.vtkActor()
    actor.SetMapper(mapper)
    actor.GetProperty().SetDiffuseColor(actor_color)

    renderer = vtk.vtkRenderer()
    renderer.AddActor(actor)
    renderer.SetBackground(background_color)
    renderer.ResetCamera()
    renderer.GetActiveCamera().Azimuth(30)
    renderer.GetActiveCamera().Elevation(30)
    renderer.GetActiveCamera().Dolly(1.5)
    renderer.ResetCameraClippingRange()
    renderer.SetBackground(colors.GetColor3d("Azure"))

    render_window = vtk.vtkRenderWindow()
    render_window.AddRenderer(renderer)

    render_window_interactor = vtk.vtkRenderWindowInteractor()
    render_window_interactor.SetRenderWindow(render_window)

    render_window.SetSize(640, 480)
    render_window.Render()

    render_window_interactor.Start()


if __name__ == '__main__':
    main()
