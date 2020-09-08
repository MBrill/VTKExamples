#!/usr/bin/env python

import vtk


def get_program_parameters():
    import argparse
    description = 'Read a .vtu file'
    epilogue = '''
   '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue)
    parser.add_argument('filename', help='ex-blow_5_0_0.vtu')
    args = parser.parse_args()
    return args.filename


def main():
    filename = get_program_parameters()
    colors = vtk.vtkNamedColors()

    points = vtk.vtkPoints()

    points.InsertNextPoint(0, 0, 0)
    points.InsertNextPoint(1, 0, 0)
    points.InsertNextPoint(1, 1, 0)
    points.InsertNextPoint(0, 1, 1)

    tetra = vtk.vtkTetra()

    tetra.GetPointIds().SetId(0, 0)
    tetra.GetPointIds().SetId(1, 1)
    tetra.GetPointIds().SetId(2, 2)
    tetra.GetPointIds().SetId(3, 3)

    cell_array = vtk.vtkCellArray()
    cell_array.InsertNextCell(tetra)

    unstructured_grid = vtk.vtkUnstructuredGrid()
    unstructured_grid.SetPoints(points)
    unstructured_grid.SetCells(vtk.VTK_TETRA, cell_array)

    # Write file
    writer = vtk.vtkXMLUnstructuredGridWriter()
    writer.SetFileName(filename)
    writer.SetInputData(unstructured_grid)
    writer.Write()

    # Read and display file for verification that it was written correclty
    reader = vtk.vtkXMLUnstructuredGridReader()
    reader.SetFileName(filename)
    reader.Update()

    mapper = vtk.vtkDataSetMapper()
    mapper.SetInputConnection(reader.GetOutputPort())

    actor = vtk.vtkActor()
    actor.SetMapper(mapper)

    renderer = vtk.vtkRenderer()
    render_window = vtk.vtkRenderWindow()
    render_window.AddRenderer(renderer)
    render_window_interactor = vtk.vtkRenderWindowInteractor()
    render_window_interactor.SetRenderWindow(render_window)

    renderer.AddActor(actor)
    renderer.SetBackground(colors.GetColor3d("Green"))

    render_window.Render()
    render_window_interactor.Start()


if __name__ == '__main__':
    main()
