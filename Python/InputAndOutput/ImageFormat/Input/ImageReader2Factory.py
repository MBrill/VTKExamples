#!/usr/bin/env python

import vtk


def get_program_parameters():
    import argparse
    description = 'Read any of the supported vtk image formats'
    epilogue = '''
   '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue)
    parser.add_argument('filename', help='')
    args = parser.parse_args()
    return args.filename


def main():
    filename = get_program_parameters()

    # Read file
    reader_factory = vtk.vtkImageReader2Factory()

    image_reader = vtk.vtkImageReader2()
    image_reader.TakeReference(reader_factory.CreateImageReader2(filename))
    image_reader.SetFileName(filename)
    image_reader.Update()

    # Create an actor
    actor = vtk.vtkImageActor()
    actor.GetMapper().SetInputConnection(image_reader.GetOutputPort())

    # Setup renderer
    colors = vtk.vtkNamedColors()

    renderer = vtk.vtkRenderer()
    renderer.AddActor(actor)
    renderer.ResetCamera()
    renderer.SetBackground(colors.GetColor3d("Slate_grey"))

    # Setup render window
    reader_window = vtk.vtkRenderWindow()
    reader_window.AddRenderer(renderer)

    # Setup render window interactor
    reader_window_interactor = vtk.vtkRenderWindowInteractor()
    style = vtk.vtkInteractorStyleImage()

    reader_window_interactor.SetInteractorStyle(style)

    # Render and start interaction
    reader_window_interactor.SetRenderWindow(reader_window)
    reader_window.Render()
    reader_window_interactor.Initialize()

    reader_window_interactor.Start()


if __name__ == '__main__':
    main()
