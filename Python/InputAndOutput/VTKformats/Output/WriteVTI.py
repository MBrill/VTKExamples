#!/usr/bin/env python

import vtk


def get_program_parameters():
    import argparse
    description = 'Read a .vti file'
    epilogue = '''
   '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue)
    parser.add_argument('filename', help='filename.vti')
    args = parser.parse_args()
    return args.filename


def main():
    filename = get_program_parameters()
    colors = vtk.vtkNamedColors()

    image_data = vtk.vtkImageData()

    image_data.SetDimensions(3, 4, 5)
    image_data.AllocateScalars(vtk.VTK_DOUBLE, 1)

    dims = image_data.GetDimensions()

    # Fill every entry of the image data with "2.0"
    for z in range(0, dims[2]):
        for y in range(0, dims[1]):
            for x in range(0, dims[0]):
                pixel = image_data.GetScalarPointer(x, y, z)

    writer = vtk.vtkXMLImageDataWriter()
    writer.SetFileName(filename)
    writer.SetInputData(image_data)
    writer.Write()

    # Read the file(to test that it was written correctly)
    reader = vtk.vtkXMLImageDataReader()
    reader.SetFileName(filename)
    reader.Update()

    # Convert the image to a polydata
    image_data_geometry_filter = vtk.vtkImageDataGeometryFilter()
    image_data_geometry_filter.SetInputConnection(reader.GetOutputPort())
    image_data_geometry_filter.Update()

    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputConnection(image_data_geometry_filter.GetOutputPort())

    actor = vtk.vtkActor()
    actor.SetMapper(mapper)
    actor.GetProperty().SetPointSize(3)

    # Setup rendering
    renderer = vtk.vtkRenderer()
    renderer.AddActor(actor)
    renderer.SetBackground(1, 1, 1)
    renderer.ResetCamera()

    render_window = vtk.vtkRenderWindow()
    render_window.AddRenderer(renderer)

    render_window_interactor = vtk.vtkRenderWindowInteractor()
    renderer.SetBackground(colors.GetColor3d("Azure"))

    render_window_interactor.SetRenderWindow(render_window)
    render_window.Render()
    render_window_interactor.Initialize()
    render_window_interactor.Start()


if __name__ == '__main__':
    main()
