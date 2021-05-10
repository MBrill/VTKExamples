# Beispiel für die Erzeugung eines unstructured grids in VTK für
# den Abschnitt über Datenstrukturen für die visualisierung.
# 
# Unstructured grids require explicit point and cell representations,
# so every point and cell must be created, and then added to the
# vtkUnstructuredGrid instance.
#
# Erzeugt wird ein Hexaeder, ein Tetraeder auf dem Hexaeder, ein Dreieck
# und eine Kante. Damit soll gezeigt werden, dass ein solcher Datensatz
# ganz verschieden-dimensionale Objekte enthalten kann, der die gleiche
# Punkte enthält.
# Hier werden mehrere unstructured grids erzeugt. Dann können die einzelnen
# Elemente davon verschiedenen gefärbt werden.


package require vtk
package require vtkinteraction

vtkProperty wire
  wire SetRepresentationToWireframe
  wire SetDiffuseColor 0 0 0
  wire SetColor 0 0 0
  wire SetLineWidth 3.0

# Zuerst die Punkte erzeugen, die die Geometrie erzeugen.

vtkPoints tetraPoints
  tetraPoints SetNumberOfPoints 4
  tetraPoints InsertPoint 0 0 1 0
  tetraPoints InsertPoint 1 1 1 0
  tetraPoints InsertPoint 2 .5 2 0
  tetraPoints InsertPoint 3 .5 1.5 1
vtkTetra aTetra
  [aTetra GetPointIds] SetId 0 0
  [aTetra GetPointIds] SetId 1 1
  [aTetra GetPointIds] SetId 2 2
  [aTetra GetPointIds] SetId 3 3
vtkUnstructuredGrid aTetraGrid
  aTetraGrid Allocate 1 1
  aTetraGrid InsertNextCell [aTetra GetCellType] [aTetra GetPointIds]
  aTetraGrid SetPoints tetraPoints
vtkDataSetMapper aTetraMapper
  aTetraMapper SetInput aTetraGrid
# Das Tetraeder auf das Hexaeder draussetzen, mit einer Translation 0,1,0.
vtkActor aTetraActor
  aTetraActor SetMapper aTetraMapper
  aTetraActor SetProperty wire

vtkPoints pyramidPoints
  pyramidPoints SetNumberOfPoints 5
  pyramidPoints InsertPoint 0 0 0 0
  pyramidPoints InsertPoint 1 1 0 0
  pyramidPoints InsertPoint 2 1 1 0
  pyramidPoints InsertPoint 3 0 1 0
  pyramidPoints InsertPoint 4 .5 .5 1
vtkPyramid aPyramid
  [aPyramid GetPointIds] SetId 0 0
  [aPyramid GetPointIds] SetId 1 1
  [aPyramid GetPointIds] SetId 2 2
  [aPyramid GetPointIds] SetId 3 3
  [aPyramid GetPointIds] SetId 4 4
vtkUnstructuredGrid aPyramidGrid
  aPyramidGrid Allocate 1 1
  aPyramidGrid InsertNextCell [aPyramid GetCellType] [aPyramid GetPointIds]
  aPyramidGrid SetPoints pyramidPoints
vtkDataSetMapper aPyramidMapper
  aPyramidMapper SetInput aPyramidGrid
vtkActor aPyramidActor
  aPyramidActor SetMapper aPyramidMapper
  aPyramidActor AddPosition 1.5 0 0
  aPyramidActor SetProperty wire

vtkPoints wedgePoints
  wedgePoints SetNumberOfPoints 6
  wedgePoints InsertPoint 0 0 1 0
  wedgePoints InsertPoint 1 0 0 0
  wedgePoints InsertPoint 2 0 .5 .5
  wedgePoints InsertPoint 3 1 1 0
  wedgePoints InsertPoint 4 1 0 0
  wedgePoints InsertPoint 5 1 .5 .5
vtkWedge aWedge
  [aWedge GetPointIds] SetId 0 0
  [aWedge GetPointIds] SetId 1 1
  [aWedge GetPointIds] SetId 2 2
  [aWedge GetPointIds] SetId 3 3
  [aWedge GetPointIds] SetId 4 4
  [aWedge GetPointIds] SetId 5 5
vtkUnstructuredGrid aWedgeGrid
  aWedgeGrid Allocate 1 1
  aWedgeGrid InsertNextCell [aWedge GetCellType] [aWedge GetPointIds]
  aWedgeGrid SetPoints wedgePoints
vtkDataSetMapper aWedgeMapper
  aWedgeMapper SetInput aWedgeGrid
vtkActor aWedgeActor
  aWedgeActor SetMapper aWedgeMapper
  aWedgeActor AddPosition 3 1 0
  aWedgeActor SetProperty wire

vtkRenderer ren
  ren SetBackground 1 1 1
  ren AddActor aTetraActor
  ren AddActor aPyramidActor
  ren AddActor aWedgeActor

vtkRenderWindow renWin
  renWin AddRenderer ren
  renWin SetSize 1400 500
  renWin Render

# render the image
#
vtkRenderWindowInteractor iren
  iren SetRenderWindow renWin
  iren AddObserver UserEvent {wm deiconify .vtkInteract}
  iren Initialize
wm withdraw .
