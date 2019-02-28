// ----------------------------------------------------------------------------
//   Ein Beispiel, das einen unstructured grid erstellt und darstellt.
// ----------------------------------------------------------------------------
#include "vtkPoints.h"
#include "vtkVoxel.h"
#include "vtkTetra.h"
#include "vtkPyramid.h"
#include "vtkWedge.h"
#include "vtkUnstructuredGrid.h"
#include "vtkDataSetMapper.h"
#include "vtkWindow.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkProperty.h"
#include "vtkActor.h"
#include "vtkCamera.h"

int main( int argc, char *argv[] )
{
    int i;
    
    // Zuerst die Geometrie der Zellen festlegen
    // Dies geschieht in einer Instanz von vtkPoints mit insgesamt
    // 23 Punkten.
    vtkPoints *points = vtkPoints::New();
    // Die Gitterpunktkoordinaten setzen.
    points->SetNumberOfPoints(23);
    points->InsertPoint(0,0,0,0);
    points->InsertPoint(1,1,0,0);
    points->InsertPoint(2,0,1,0);
    points->InsertPoint(3,1,1,0);
    points->InsertPoint(4,0,0,1);
    points->InsertPoint(5,1,0,1);
    points->InsertPoint(6,0,1,1);
    points->InsertPoint(7,1,1,1);
    // Die Punkte f�r den Tetraeder.
    points->InsertPoint(8,1.5,0,0);
    points->InsertPoint(9,2.5,0,0);
    points->InsertPoint(10,2.0,1,0);
    points->InsertPoint(11,2.0, 0.5, 1);
    // Die Punkte f�r das Prisma.
    points->InsertPoint(12, 3,1,0);
    points->InsertPoint(13, 3,0,0);
    points->InsertPoint(14, 3,0.5, 0.5);
    points->InsertPoint(15, 4,1,0);
    points->InsertPoint(16, 4,0,0);
    points->InsertPoint(17, 4,0.5,0.5);
    // Die Punkte f�r die Pyramide.
    points->InsertPoint(18, 5,0,0);
    points->InsertPoint(19, 6,0,0);
    points->InsertPoint(20, 6,1,0);
    points->InsertPoint(21, 5,1,0);
    points->InsertPoint(22, 5.5,0.5,1);
    // Eine Voxel-Zelle 
    vtkVoxel *aVoxel = vtkVoxel::New();
       for (i=0; i<8; i++) aVoxel->GetPointIds()->SetId(i,i);
    // Eine Tetraeder-Zelle
    vtkTetra *aTetra = vtkTetra::New();
       aTetra->GetPointIds()->SetId(0,8);
       aTetra->GetPointIds()->SetId(1,9);
       aTetra->GetPointIds()->SetId(2,10);
       aTetra->GetPointIds()->SetId(3,11);
    // Eine Prisma-Zelle
    vtkWedge *aWedge = vtkWedge::New();
       aWedge->GetPointIds()->SetId(0,12);
       aWedge->GetPointIds()->SetId(1,13);
       aWedge->GetPointIds()->SetId(2,14);
       aWedge->GetPointIds()->SetId(3,15);
       aWedge->GetPointIds()->SetId(4,16);
       aWedge->GetPointIds()->SetId(5,17);
    vtkPyramid *aPyramid = vtkPyramid::New();
       aPyramid->GetPointIds()->SetId(0,18);
       aPyramid->GetPointIds()->SetId(1,19);
       aPyramid->GetPointIds()->SetId(2,20);
       aPyramid->GetPointIds()->SetId(3,21);
       aPyramid->GetPointIds()->SetId(4,22);
       
    // Die Zellen in den Datensatz ablegen.
    // Instanz eines unstrukturierten Gitters;
    // die Instanz points wird als Gitterpunkte verwendet.
    vtkUnstructuredGrid *theGrid = vtkUnstructuredGrid::New();
       theGrid->Allocate(1,1);
       theGrid->SetPoints(points);
       theGrid->InsertNextCell(aVoxel->GetCellType(),aVoxel->GetPointIds());
       theGrid->InsertNextCell(aTetra->GetCellType(),aTetra->GetPointIds());
       theGrid->InsertNextCell(aWedge->GetCellType(),aWedge->GetPointIds());
       theGrid->InsertNextCell(aPyramid->GetCellType(),aPyramid->GetPointIds());
       
    // Die Daten abbilden auf ein polygonales Netz mit einer Instanz
    // von vtkDataSetMapper.
    vtkDataSetMapper *mapper = vtkDataSetMapper::New();
        mapper->SetInputData(theGrid);
    
    // Grafische Attribute f�r die Darstellung als 
    // Instanz der Klasse vtkProperty    
    vtkProperty *property = vtkProperty::New();
        property->SetDiffuseColor(0.8,0.0,0.0);
        
    // Ein grafisches Objekt, als Attribute wird
    // die Instanz property verwendet.
    vtkActor *actor = vtkActor::New();
        actor->SetMapper(mapper);
        actor->SetProperty(property);
        
    // Einen Renderer f�r die interaktive Darstellung instanzieren,
    // die Hintergrundfarbe setzen und Einstellungen an der aktiven
    // Kamera.
    vtkRenderer *render = vtkRenderer::New();
     	render->AddActor(actor);
        render->SetBackground(1,1,1);
        // Die Kamera des Renderers einstellen.
        //render->GetActiveCamera()->Elevation(20.0);
        
    // Als letzten Schritt ben�tigen wir ein Fenster, in das der Renderer
    // ausgibt.
    vtkRenderWindow *renWin = vtkRenderWindow::New();
        renWin->SetSize(640,480);
	    renWin->AddRenderer(render);
	    renWin->Render();
	    
    // Mit den Daten interagieren.
    // Typische Keyboard-Shortcuts in VTK:
    //    q oder e: beenden des Programms
    //           r: Reset der Ansicht
    vtkRenderWindowInteractor *interact = vtkRenderWindowInteractor::New();
        interact->SetRenderWindow(renWin);
        renWin->Render();
        interact->Start();

    // Aufr�umen; die Konstruktoren in VTK werden als Memberfunktion
    // Delete() aufgerufen.
    interact->Delete();
    renWin->Delete();
    render->Delete();
    property->Delete();
    actor->Delete();
    mapper->Delete();
    theGrid->Delete();
    points->Delete();    
   
    return 0;
}
