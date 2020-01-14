# Ursprüngliche Datei expcos.tcl. Dort wurde ein warp und die
# Ableitungen der Bessel/Sombrero-Funktion verwendet. Hier werden
# nur die Funktionswerte berechnet, und verschiedene Lookup-Tables. 
# Damit die Isolinien interessanter liegen wird die Rosenbrock-Banane
#  f(x,y) = 100(y-x^2)^2 + (1-x)^2
# verwendet.
#
# Für die screen captures die Fenstergröße auf 250x250 setzen!
#
# Es gibt ganz verschiedene Lookup-Tables; auch eine mit
# grün-Tönen (green), die mit einem großen Capture eingefangen wurde.

# first we load in the standard vtk packages into tcl
package require vtk
package require vtkinteraction
# 
# We create a 100 by 100 point plane to sample 
#
vtkPlaneSource plane
    plane SetXResolution 100
    plane SetYResolution 100

#
#  Skalieren der Ebene um den Faktor 5 in x und y
#  Für die Banane nur mit Faktor
vtkTransform transform
   transform Scale 3 3 1
vtkTransformPolyDataFilter transF
   transF SetInput [plane GetOutput]
   transF SetTransform transform
# 
#
vtkProgrammableFilter bananaF
   bananaF SetInput [transF GetOutput]
   bananaF SetExecuteMethod banana

#
# Die SetExecuteMethod nimmt eine Tcl-Funktion als Argument!
# Hier werden die Funktionswerte berechnet!
#
proc banana {} {
   set input [bananaF GetPolyDataInput]
   set numPts [$input GetNumberOfPoints]
   vtkPoints newPts
   vtkFloatArray values

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

vtkContourFilter contour
    contour SetInput [bananaF GetPolyDataOutput]
    # Isowerte für die Banane
    eval contour GenerateValues 10 0 10
    # Die Isowerte für die e^x( ... ) Funktion aus Gill Murray, p. 46
    #contour SetValue 0 0.2
    #contour SetValue 1 0.4
    #contour SetValue 2 0.7
    #contour SetValue 3 1
    #contour SetValue 4 1.7
    #contour SetValue 5 1.8
    #contour SetValue 6 2
    #contour SetValue 7 3
    #contour SetValue 8 4
    #contour SetValue 9 5
    #contour SetValue 10 6
    #contour SetValue 11 20
 
vtkCleanPolyData clean
    clean SetInput [contour GetOutput]

#
# We create a mapper and actor as usual. In the case we adjust the 
# scalar range of the mapper to match that of the computed scalars
#
vtkLookupTable lut
    lut SetHueRange 0.667 0.0
    lut SetNumberOfColors 256
    lut Build

vtkPolyDataMapper mapper
    mapper SetInput [clean GetOutput]
    #eval mapper SetScalarRange 0 1
    #mapper SetLookupTable lut
    mapper ScalarVisibilityOff

vtkActor isolines
    isolines SetMapper mapper
    [isolines GetProperty] SetColor 0 0 0

#
# Create the RenderWindow, Renderer
#
vtkRenderer ren
    ren SetBackground 1 1 1
vtkRenderWindow renWin
    renWin AddRenderer ren
vtkRenderWindowInteractor iren
    iren SetRenderWindow renWin

ren AddActor isolines
#renWin SetSize 500 500
renWin SetSize 250 250

# render the image
#
iren AddObserver UserEvent {wm deiconify .vtkInteract}
[ren GetActiveCamera] Zoom 1.6
renWin Render
renWin MakeCurrent

# prevent the tk window from showing up then start the event loop
wm withdraw .

