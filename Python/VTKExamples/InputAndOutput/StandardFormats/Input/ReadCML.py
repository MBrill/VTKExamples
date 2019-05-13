#!/usr/bin/env python

import vtk


def get_program_parameters():
    import argparse
    description = 'Read a .xml Chemistry Markup Language file'
    epilogue = '''
   '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue)
    parser.add_argument('filename', help='filenmae.xml')
    args = parser.parse_args()
    return args.filename


def main():
    filename = get_program_parameters()

    cml_source = vtk.vtkCMLMoleculeReader()
    cml_source.SetFileName(filename)

    molmapper = vtk.vtkMoleculeMapper()
    molmapper.SetInputConnection(cml_source.GetOutputPort())

    molmapper.UseBallAndStickSettings()

    colors = vtk.vtkNamedColors()

    actor = vtk.vtkActor()
    actor.SetMapper(molmapper)
    actor.GetProperty().SetDiffuse(.7)
    actor.GetProperty().SetSpecular(.5)
    actor.GetProperty().SetSpecularPower(20.0)

    renderer = vtk.vtkRenderer()
    renderer.AddActor(actor)

    render_window = vtk.vtkRenderWindow()
    render_window.AddRenderer(renderer)
    render_window_interactor = vtk.vtkRenderWindowInteractor()
    render_window_interactor.SetRenderWindow(render_window)

    render_window.SetSize(640, 480)
    render_window.Render()
    renderer.GetActiveCamera().Zoom(2.0)
    renderer.SetBackground(colors.GetColor3d("Silver"))

    # Finally render the scene
    render_window.SetMultiSamples(0)
    render_window.GetInteractor().Initialize()
    render_window.GetInteractor().Start()


if __name__ == '__main__':
    main()
