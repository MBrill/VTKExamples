#!/usr/bin/env python

import vtk
import math


def get_program_parameters():
    import argparse
    description = 'Read a .pdb Protein Data Bank file'
    epilogue = '''
   '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue)
    parser.add_argument('filename', help='filename.pdb')
    args = parser.parse_args()
    return args.filename


def main():
    filename = get_program_parameters()
    colors = vtk.vtkNamedColors()

    renderer = vtk.vtkRenderer()
    renderer.SetBackground(colors.GetColor3d("SlateGray"))
    render_window = vtk.vtkRenderWindow()
    render_window.AddRenderer(renderer)
    render_window.SetSize(640, 480)

    interactor = vtk.vtkRenderWindowInteractor()
    interactor.SetRenderWindow(render_window)

    pdb = vtk.vtkPDBReader()
    pdb.SetFileName(filename)
    pdb.SetHBScale(1.0)
    pdb.SetBScale(1.0)
    pdb.Update()
    print("# of atoms is:", pdb.GetNumberOfAtoms())

    resolution = math.sqrt(300000.0 / pdb.GetNumberOfAtoms())
    if resolution > 20:
        resolution = 20
    if resolution < 4:
        resolution = 4

    print("Resolution is:", resolution)
    sphere = vtk.vtkSphereSource()
    sphere.SetCenter(0, 0, 0)
    sphere.SetRadius(1)
    sphere.SetThetaResolution(int(resolution))
    sphere.SetPhiResolution(int(resolution))

    glyph = vtk.vtkGlyph3D()
    glyph.SetInputConnection(pdb.GetOutputPort())
    glyph.SetOrient(1)
    glyph.SetColorMode(1)
    # glyph.ScalingOn();
    glyph.SetScaleMode(2)
    glyph.SetScaleFactor(.25)
    glyph.SetSourceConnection(sphere.GetOutputPort())

    atom_mapper = vtk.vtkPolyDataMapper()
    atom_mapper.SetInputConnection(glyph.GetOutputPort())
    atom_mapper.UseLookupTableScalarRangeOff()
    atom_mapper.ScalarVisibilityOn()
    atom_mapper.SetScalarModeToDefault()

    atom = vtk.vtkLODActor()
    atom.SetMapper(atom_mapper)
    atom.GetProperty().SetRepresentationToSurface()
    atom.GetProperty().SetInterpolationToGouraud()
    atom.GetProperty().SetAmbient(0.1)
    atom.GetProperty().SetDiffuse(0.7)
    atom.GetProperty().SetSpecular(0.5)
    atom.GetProperty().SetSpecularPower(80)
    atom.GetProperty().SetSpecularColor(colors.GetColor3d("White"))
    atom.SetNumberOfCloudPoints(30000)

    renderer.AddActor(atom)

    tube = vtk.vtkTubeFilter()
    tube.SetInputConnection(pdb.GetOutputPort())
    tube.SetNumberOfSides(int(resolution))
    tube.CappingOff()
    tube.SetRadius(0.2)
    tube.SetVaryRadius(0)
    tube.SetRadiusFactor(10)

    bond_mapper = vtk.vtkPolyDataMapper()

    bond_mapper.SetInputConnection(tube.GetOutputPort())
    bond_mapper.UseLookupTableScalarRangeOff()
    bond_mapper.ScalarVisibilityOff()
    bond_mapper.SetScalarModeToDefault()

    bond = vtk.vtkLODActor()
    bond.SetMapper(bond_mapper)
    bond.GetProperty().SetRepresentationToSurface()
    bond.GetProperty().SetInterpolationToGouraud()
    bond.GetProperty().SetAmbient(0.1)
    bond.GetProperty().SetDiffuse(0.7)
    bond.GetProperty().SetSpecular(0.5)
    bond.GetProperty().SetSpecularPower(80)
    bond.GetProperty().SetSpecularColor(colors.GetColor3d("White"))

    renderer.AddActor(bond)
    renderer.SetBackground(colors.GetColor3d("Green"))

    render_window.Render()
    interactor.Initialize()
    interactor.Start()


if __name__ == '__main__':
    main()
