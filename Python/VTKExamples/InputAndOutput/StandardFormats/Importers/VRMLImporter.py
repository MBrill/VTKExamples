#!/usr/bin/env python

import vtk


def get_program_parameters():
    import argparse
    description = 'Read a .wrl file'
    epilogue = '''
   '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue)
    parser.add_argument('filename', help='sextant.wrl')
    args = parser.parse_args()
    return args.filename


def main():
    filename = get_program_parameters()

    colors = vtk.vtkNamedColors()

    renderer = vtk.vtkRenderer()
    render_window = vtk.vtkRenderWindow()
    render_window.AddRenderer(renderer)

    render_window_interactor = vtk.vtkRenderWindowInteractor()
    render_window_interactor.SetRenderWindow(render_window)

    # VRML Import
    importer = vtk.vtkVRMLImporter()
    importer.SetFileName(filename)
    importer.SetRenderWindow(render_window)
    importer.Update()

    actors = vtk.vtkActorCollection()
    actors = renderer.GetActors()
    print("There are", actors.GetNumberOfItems(), "actors")

    renderer.SetBackground(colors.GetColor3d("Burlywood"))
    render_window.SetSize(512, 512)
    render_window.Render()
    render_window_interactor.Start()


if __name__ == '__main__':
    main()
