#!/usr/bin/env python

import vtk


def get_program_parameters():
    import argparse
    description = 'Read a .mha file'
    epilogue = '''
   '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue)
    parser.add_argument('filename', help='Gourds.mha')
    args = parser.parse_args()
    return args.filename


def main():
    filename = get_program_parameters()

    reader = vtk.vtkMetaImageReader()
    reader.SetFileName(filename)
    reader.Update()

    # Visualize
    actor = vtk.vtkImageActor()
    actor.GetMapper().SetInputConnection(reader.GetOutputPort())

    renderer = vtk.vtkRenderer()
    renderer.AddActor(actor)
    renderer.ResetCamera()

    render_window = vtk.vtkRenderWindow()
    render_window.AddRenderer(renderer)

    render_window_interactor = vtk.vtkRenderWindowInteractor()
    style = vtk.vtkInteractorStyleImage()

    render_window_interactor.SetInteractorStyle(style)

    render_window_interactor.SetRenderWindow(render_window)
    render_window.Render()
    render_window_interactor.Initialize()

    render_window_interactor.Start()


if __name__ == '__main__':
    main()
