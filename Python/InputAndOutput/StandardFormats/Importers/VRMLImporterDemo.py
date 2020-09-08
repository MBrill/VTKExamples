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

    print("Reading " + filename)

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
    actors.InitTraversal()

    for a in range(0, actors.GetNumberOfItems()):
        actor = actors.GetNextActor()

        # The importer shininess parameter is between 0 and 1. VTK specular power is usually 10 - 100.
        # Also, the default for the specular factor for VRML is 1, while VTK's
        # is 0
        specular_power = actor.GetProperty().GetSpecularPower()
        if specular_power <= 1.0:
            actor.GetProperty().SetSpecularPower(specular_power * 128.0)
        specular = actor.GetProperty().GetSpecular()
        if specular == 0.0:
            actor.GetProperty().SetSpecular(1.0)
            # if 0
            # The VRML default ambient intensity is .2
        ambient_intensity = actor.GetProperty().GetAmbient()
        if ambient_intensity == 0.0:
            actor.GetProperty().SetAmbient(.2)
            # endif
        mapper = actor.GetMapper()
        if (mapper):
            data_set = mapper.GetInput()
            if not data_set.GetPointData().GetNormals():
                normals = vtk.vtkPolyDataNormals()
                normals.SetInputData(data_set)
                normals.SplittingOff()
                normals.Update()
                mapper.SetInputData(normals.GetOutput())

                # If there is a lookup table, convert it to point data
                lut = mapper.GetLookupTable()
                if lut and mapper.GetScalarVisibility():
                    pc = vtk.vtkUnsignedCharArray()
                    pc.SetNumberOfComponents(4)
                    pc.SetNumberOfTuples(lut.GetNumberOfColors())
                    for t in range(0, lut.GetNumberOfColors()):
                        lutc = lut.GetTableValue(t)
                        lutuc = ['', '', '', '']
                        lut.GetColorAsUnsignedChars(lutc, lutuc)
                        pc.SetTypedTuple(t, lutuc)
                    mapper.SetLookupTable(None)
                    mapper.GetInput().GetPointData().SetScalars(pc)

        renderer.ResetCamera()
        renderer.GetActiveCamera().Azimuth(30)
        renderer.GetActiveCamera().Elevation(30)
        renderer.GetActiveCamera().Dolly(1.4)
        renderer.ResetCameraClippingRange()

        renderer.SetBackground(colors.GetColor3d("PaleGreen"))
        render_window.SetSize(640, 480)
        render_window.Render()
        render_window_interactor.Start()


if __name__ == '__main__':
    main()
