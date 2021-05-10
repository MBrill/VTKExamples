# -*- coding: utf-8 -*-
"""
Einlesen und Darstellen eines einfachen Flugzeug-Modells

War plane.tcl
"""
import vtk


def main():
    reader = vtk.vtkPolyDataReader()
    reader.SetFileName('data/plane.vtk')

    prop = vtk.vtkProperty()
    prop.SetAmbient(0.05)
    prop.SetDiffuse(0.9)
    prop.SetSpecular(0.5)
    prop.SetSpecularPower(70.0)
    prop.SetAmbientColor(0.1, 0.1, 0.1)
    prop.SetDiffuseColor(0.6, 0.6, 0.6)
    prop.SetSpecularColor(1.0, 1.0, 1.0)

    normals = vtk.vtkPolyDataNormals()
    normals.SetInputConnection(reader.GetOutputPort())
    normals.SetFeatureAngle(60.0)
    normals.ConsistencyOn()

    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputConnection(normals.GetOutputPort())

    planeActor = vtk.vtkActor()
    planeActor.SetMapper(mapper)
    planeActor.SetProperty(prop)
    planeActor.SetOrientation(45.0, 67.5, 45.0)

    axes = vtk.vtkAxes()
    axes.SetOrigin(0.0, 0.0, 0.0)
    axes.SymmetricOn()
    axes.SetScaleFactor(10.0)

    axisProp = vtk.vtkProperty()
    axisProp.SetAmbient(0.05)
    axisProp.SetDiffuse(0.95)
    axisProp.SetSpecular(0.0)
    axisProp.SetAmbientColor(0.05, 0.05, 0.05)
    axisProp.SetDiffuseColor(0.05, 0.05, 0.05)

    aMap = vtk.vtkPolyDataMapper()
    aMap.SetInputConnection(axes.GetOutputPort())
    aMap.ScalarVisibilityOn()

    aAct = vtk.vtkActor()
    aAct.SetMapper(aMap)
    aAct.SetProperty(axisProp)

    # Text für die Achsen
    xText = vtk.vtkVectorText()
    xText.SetText('x')
    yText = vtk.vtkVectorText()
    yText.SetText('y')
    zText = vtk.vtkVectorText()
    zText.SetText('z')

    xMap = vtk.vtkPolyDataMapper()
    xMap.SetInputConnection(xText.GetOutputPort())
    yMap = vtk.vtkPolyDataMapper()
    yMap.SetInputConnection(yText.GetOutputPort())
    zMap = vtk.vtkPolyDataMapper()
    zMap.SetInputConnection(zText.GetOutputPort())

    xActor = vtk.vtkFollower()
    xActor.SetMapper(xMap)
    xActor.SetScale(0.6, 0.6, 0.6)
    xActor.AddPosition(9.0, 0.5, 0.0)
    xActor.SetProperty(axisProp)

    yActor = vtk.vtkFollower()
    yActor.SetMapper(yMap)
    yActor.SetScale(0.6, 0.6, 0.6)
    yActor.AddPosition(-1.0, 9.0, 0.0)
    yActor.SetProperty(axisProp)

    zActor = vtk.vtkFollower()
    zActor.SetMapper(zMap)
    zActor.SetScale(0.6, 0.6, 0.6)
    zActor.AddPosition(-1.0, 0.0, 9.0)
    zActor.SetOrientation(-45.0, 0.0, 0.0)
    zActor.SetProperty(axisProp)


    ren = vtk.vtkRenderer()
    ren.SetBackground(1.0, 1.0, 1.0)
    ren.AddActor(planeActor)
    ren.AddActor(aAct)
    ren.AddActor(xActor)
    ren.AddActor(yActor)
    ren.AddActor(zActor)
    ren.ResetCameraClippingRange()

    renderWindow = vtk.vtkRenderWindow()
    renderWindow.AddRenderer(ren)
    renderWindow.SetSize(800, 600)

    renderWindowInteractor = vtk.vtkRenderWindowInteractor()
    renderWindowInteractor.SetRenderWindow(renderWindow)

    renderWindow.Render()
    renderWindowInteractor.Start()


if __name__ == '__main__':
    main()
