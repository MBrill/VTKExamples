#!/usr/bin/env python

import vtk


def get_program_parameters():
    import argparse
    description = 'Read a .gml file'
    epilogue = '''
   '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue)
    parser.add_argument('filename', help='fsm.gml')
    args = parser.parse_args()
    return args.filename


def main():
    filename = get_program_parameters()

    reader = vtk.vtkXGMLReader()
    reader.SetFileName(filename)
    reader.Update()

    g = reader.GetOutput()

    graph_layout_view = vtk.vtkGraphLayoutView()
    graph_layout_view.AddRepresentationFromInput(g)
    graph_layout_view.SetLayoutStrategy("Simple 2D")
    graph_layout_view.ResetCamera()
    graph_layout_view.Render()

    graph_layout_view.GetInteractor().Start()


if __name__ == '__main__':
    main()
