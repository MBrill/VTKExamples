# Starten in der Anaconda-Shell mit
#    python isolines.py
import vtk

# Ebene, Auflösung 100x100
plane = vtk.vtkPlaneSource()
plane.SetXResolution(100)
plane.SetYResolution(100)

transform = vtk.vtkTransform()
transform.Scale(3.0, 3.0, 1.0)

transF = vtk.vtkTransformPolyDataFilter()
transF.SetInputData(plane.GetOutputPort())
transF.SetTransform(transform)

bananaF = vtk.vtkProgrammableFilter()
bananaF.SetInputConnection(transf.GetOutPort())
bananaF.SetExecuteMethod(banana)

def rosenbrock(x, y) :
    """Die Rosenbrock-Banane """
    return 100.0*(y - x**2)**2 + (1.0-x)*(1.0-x)
#
# Die SetExecuteMethod nimmt eine Tcl-Funktion als Argument!
# Hier werden die Funktionswerte berechnet!
#
def banana () :
    """Die Rosenbrock-Banane """
    input = bananaF.GetPolyDataInput()
    numPts = input.GetNumberOfPoints()
    newPts = vtk.vtkPoints()
    values = vtk.vtkFloatArray()
    
    for (i=0)
   # Frequenz
   for {set i 0} {$i < $numPts} {incr i} {
	set x [$input GetPoint $i]
	set x0 [lindex $x 0]
	set x1 [lindex $x 1]

	set y [expr 100.0*($x1-$x0*$x0)*($x1-$x0*$x0) + (1.0-$x0)*(1-$x0)]
        #set y [expr exp($x0)*(4*$x0*$x0 + 2*$x1*$x1 + 4*$x0*$x1 + 2*$x1 + 1)]

	newPts InsertPoint $i $x0 $x1 $y

	eval values InsertValue $i $y
    }

    [bananaF GetPolyDataOutput] CopyStructure $input
    #[bananaF GetPolyDataOutput] SetPoints newPts
    [[bananaF GetPolyDataOutput] GetPointData] SetScalars values

    values Delete
}
   
# Mapper und Actor erzeugen und verbinden
mapper = vtk.vtkPolyDataMapper()
mapper.SetInputConnection(plane.GetOutputPort())
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
