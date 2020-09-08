#!/usr/bin/env python

# This example reads ascii files where each line consists of points with its position (x,y,z)
# and (optionally) one scalar or binary files in RAW 3d file format.

import vtk


def get_program_parameters():
    import argparse
    description = 'Read a .raw file'
    epilogue = '''
    '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue)
    parser.add_argument('filename', help='Particles.raw')
    args = parser.parse_args()
    return args.filename


def main():
    filename = get_program_parameters()

    # Particles.raw supplied by VTK is big endian encoded
    # Read the file
    reader = vtk.vtkParticleReader()

    reader.SetFileName(filename)
    # if nothing gets displayed or totally wrong, swap the endianness
    reader.SetDataByteOrderToBigEndian()
    reader.Update()

    # Visualize
    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputConnection(reader.GetOutputPort())
    print("number of pieces:", mapper.GetNumberOfPieces())
    mapper.SetScalarRange(4, 9)

    actor = vtk.vtkActor()

    actor.SetMapper(mapper)
    actor.GetProperty().SetPointSize(4)

    renderer = vtk.vtkRenderer()
    render_window = vtk.vtkRenderWindow()
    render_window.AddRenderer(renderer)
    render_window_interactor = vtk.vtkRenderWindowInteractor()
    render_window_interactor.SetRenderWindow(render_window)
    renderer.AddActor(actor)

    named_colors = vtk.vtkNamedColors()
    renderer.SetBackground(named_colors.GetColor3d("Azure"))

    render_window.Render()
    render_window_interactor.Start()


if __name__ == '__main__':
    main()
