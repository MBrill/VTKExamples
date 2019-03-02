# Starten in der Anaconda-Shell mit
#    python cone.py
import vtk


coneSource = vtk.vtkConeSource()
# coneSource.SetResolution(60)
# coneSource.SetCenter(-2,0,0)

# Mapper und Actor erzeugen und verbinden
mapper = vtk.vtkPolyDataMapper()
mapper.SetInputConnection(coneSource.GetOutputPort())
actor = vtk.vtkActor()
actor.SetMapper(mapper)

# Hintergrundfarbe des Fensters mischen
colors = vtk.vtkNamedColors()
colors.SetColor("BkgColor", [26, 51, 77, 255])

# Renderer, Fenster und Interactor
renderer = vtk.vtkRenderer()
renderer.AddActor(actor)
renderer.SetBackground(colors.GetColor3d("BkgColor"))  # Background color dark red

renderWindow = vtk.vtkRenderWindow()
renderWindow.SetPosition(100,100)
renderWindow.SetSize(500,500)
renderWindow.AddRenderer(renderer)

renderWindowInteractor = vtk.vtkRenderWindowInteractor()
renderWindowInteractor.SetRenderWindow(renderWindow)

renderWindow.Render()
renderWindowInteractor.Start()
