# -*- coding: utf-8 -*-
"""
Visualisierung archimedischer Körper

War archimedesviz.tcl
"""
import vtk


def main():
    """
    Display the content of a vtk file containing archimedian bodies
    """
    # Colors, Window Size and more
    colors = vtk.vtkNamedColors()
    background_color = colors.GetColor3d("SlateGray")
    net_color = colors.GetColor3d("orange")
    size_x = 800
    size_y = 800

    reader = vtk.vtkPolyDataReader()
    filename = 'data/hexecut.vtk'
    # filename = 'data/buckyball.vtk'
    reader.SetFileName(filename)

    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputConnection(reader.GetOutputPort())

    actor = vtk.vtkActor()
    actor.SetMapper(mapper)
    actor.GetProperty().SetDiffuseColor(net_color)

    # Renderer, Window and Interactor
    renderer = vtk.vtkRenderer()
    renderer.AddActor(actor)
    renderer.SetBackground(background_color)

    renderWindow = vtk.vtkRenderWindow()
    renderWindow.SetSize(size_x, size_y)
    renderWindow.AddRenderer(renderer)

    renderWindowInteractor = vtk.vtkRenderWindowInteractor()
    renderWindowInteractor.SetRenderWindow(renderWindow)

    renderWindow.Render()
    renderWindowInteractor.Start()


if __name__ == '__main__':
    main()
