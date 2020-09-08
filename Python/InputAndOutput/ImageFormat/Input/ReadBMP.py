#!/usr/bin/env python

import vtk


def get_program_parameters():
    import argparse
    description = 'Read a .bmp image file'
    epilogue = '''
   '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue)
    parser.add_argument('filename', help='masonry.bmp')
    args = parser.parse_args()
    return args.filename


def main():
    filename = get_program_parameters()

    # Read the image
    bmp_reader = vtk.vtkBMPReader()

    bmp_reader.SetFileName(filename)

    # Visualize
    image_viewer = vtk.vtkImageViewer2()
    image_viewer.SetInputConnection(bmp_reader.GetOutputPort())
    render_window_interactor = vtk.vtkRenderWindowInteractor()
    
    image_viewer.SetupInteractor(render_window_interactor)
    image_viewer.Render()
    image_viewer.GetRenderer().ResetCamera()
    image_viewer.Render()

    render_window_interactor.Start()


if __name__ == '__main__':
    main()
