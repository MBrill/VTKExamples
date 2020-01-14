#!/usr/bin/env python

import vtk


def get_program_parameters():
    import argparse
    description = 'Required parameters: .xyz_filename.bin QFileName.bin'
    epilogue = '''
   '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue)
    parser.add_argument('xyz_filename', help='xyz_filename.bin')
    parser.add_argument('g_filename', help='g_filename.bin')
    args = parser.parse_args()
    return args.xyz_filename, args.g_filename


def main():
    xyz_filename, g_filename = get_program_parameters()
    colors = vtk.vtkNamedColors()

    reader = vtk.vtkMultiBlockPLOT3DReader()
    reader.SetXYZFileName(xyz_filename)
    reader.SetQFileName(g_filename)
    reader.SetScalarFunctionNumber(100)
    reader.SetVectorFunctionNumber(202)
    reader.Update()

    geometry_filter = vtk.vtkStructuredGridGeometryFilter()
    geometry_filter.SetInputData(reader.GetOutput().GetBlock(0))
    geometry_filter.Update()

    # Visualize
    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputConnection(geometry_filter.GetOutputPort())
    mapper.ScalarVisibilityOff()

    actor = vtk.vtkActor()
    actor.SetMapper(mapper)

    renderer = vtk.vtkRenderer()
    render_window = vtk.vtkRenderWindow()
    render_window.AddRenderer(renderer)
    render_window_interactor = vtk.vtkRenderWindowInteractor()
    render_window_interactor.SetRenderWindow(render_window)

    renderer.AddActor(actor)
    renderer.SetBackground(colors.GetColor3d("LimeGreen"))

    render_window.Render()
    render_window_interactor.Start()


if __name__ == '__main__':
    main()
