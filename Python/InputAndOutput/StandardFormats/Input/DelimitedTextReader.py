#!/usr/bin/env python

import vtk


def get_program_parameters():
    import argparse
    description = 'Read a .txt file'
    epilogue = '''
    '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue)
    parser.add_argument('filename', help='filename.txt')
    args = parser.parse_args()
    return args.filename


def main():
    input_filename = get_program_parameters()

    reader = vtk.vtkDelimitedTextReader()
    reader.SetFileName(input_filename)
    reader.DetectNumericColumnsOn()
    reader.SetFieldDelimiterCharacters(" ")
    reader.Update()

    table = reader.GetOutput()

    points = vtk.vtkPoints()

    normals = vtk.vtkDoubleArray()

    normals.SetNumberOfComponents(3)  # 3 d normals(ie x, y, z)

    print("Table has", table.GetNumberOfRows(), "rows.")
    print("Table has", table.GetNumberOfColumns(), "columns.")

    for i in range(0, table.GetNumberOfRows()):
        print(
            "x:", table.GetValue(
                i, 0).ToDouble(), "y:", (table.GetValue(
                    i, 1)).ToDouble(), "z:", (table.GetValue(
                        i, 2)).ToDouble())


        points.InsertNextPoint(table.GetValue(i, 0).ToDouble(),table.GetValue(i, 1).ToDouble(),table.GetValue(i, 2).ToDouble())

        n = [0.0, 0.0, 0.0]
        n[0] = (table.GetValue(i, 3)).ToDouble()
        n[1] = (table.GetValue(i, 4)).ToDouble()
        n[2] = (table.GetValue(i, 5)).ToDouble()

        print("n:", n[0], n[1], n[2])
        normals.InsertNextTuple(n)

    print("There are", points.GetNumberOfPoints(), "points.")

    polydata = vtk.vtkPolyData()
    polydata.SetPoints(points)
    polydata.GetPointData().SetNormals(normals)

    glyph_filter = vtk.vtkVertexGlyphFilter()
    glyph_filter.SetInputData(polydata)
    glyph_filter.Update()

    # Visualize
    colors = vtk.vtkNamedColors()

    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputConnection(glyph_filter.GetOutputPort())

    actor = vtk.vtkActor()
    actor.SetMapper(mapper)
    actor.GetProperty().SetPointSize(30)
    actor.GetProperty().SetColor(colors.GetColor3d("Tomato"))

    renderer = vtk.vtkRenderer()
    render_window = vtk.vtkRenderWindow()
    render_window.AddRenderer(renderer)
    render_window_interactor = vtk.vtkRenderWindowInteractor()
    render_window_interactor.SetRenderWindow(render_window)

    renderer.AddActor(actor)
    renderer.SetBackground(colors.GetColor3d("Mint"))

    render_window.Render()
    render_window_interactor.Start()


if __name__ == '__main__':
    main()
