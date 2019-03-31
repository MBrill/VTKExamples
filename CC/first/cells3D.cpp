#include "vtkPoints.h"
#include "vtkSphereSource.h"
#include "vtkVoxel.h"
#include "vtkTetra.h"
#include <vtkSmartPointer.h>
#include "vtkPyramid.h"
#include "vtkWedge.h"
#include "vtkUnstructuredGrid.h"
#include "vtkDataSetMapper.h"
#include "vtkProperty.h"
#include "vtkActor.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkPolyData.h"
#include "vtkPolyDataMapper.h"

// -----
// Voraussetzungen f�r dieses Projekt
//
// Damit dieses Beispiel gebaut werden kann auf Win10
// setzen wir zwei Umgbungsvariablen:
// VTK_DIR: Verzeichnis, in das VTK installiert wurde
// VTK_ROOT: das Verzeichnis ${VTK_DIR}/bin, in dem insbesondere die dll-Dateien liegen!
// Wir f�gen VTK_ROOT dem Suchpfad hinzu!
// -----
int main( int argc, char *argv[] )
{   
    // Zuerst die Geometrie der Zellen festlegen
    // Dies geschieht in einer Instanz von vtkPoints mit insgesamt
    // 23 Punkten.
	vtkSmartPointer <vtkPoints> points = vtkSmartPointer <vtkPoints>::New();

   vtkSmartPointer<vtkSphereSource> red = vtkSmartPointer<vtkSphereSource>::New();
   red->SetCenter(0.0,0.0,0.0);
   red->SetRadius(0.5);


   vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
   mapper->SetInputConnection(red->GetOutputPort());

   vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
   actor->SetMapper(mapper);

   vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderer->AddActor(actor);
  renderer->SetBackground(.3, .6, .3); // Background color green

  renderWindow->Render();
  renderWindowInteractor->Start();


    // // Die Gitterpunktkoordinaten setzen.
    // points->SetNumberOfPoints(23);
    // points->InsertPoint(0,0,0,0);
    // points->InsertPoint(1,1,0,0);
    // points->InsertPoint(2,0,1,0);
    // points->InsertPoint(3,1,1,0);
    // points->InsertPoint(4,0,0,1);
    // points->InsertPoint(5,1,0,1);
    // points->InsertPoint(6,0,1,1);
    // points->InsertPoint(7,1,1,1);
    // // Die Punkte f�r den Tetraeder.
    // points->InsertPoint(8,1.5,0,0);
    // points->InsertPoint(9,2.5,0,0);
    // points->InsertPoint(10,2.0,1,0);
    // points->InsertPoint(11,2.0, 0.5, 1);
    // // Die Punkte f�r das Prisma.
    // points->InsertPoint(12, 3,1,0);
    // points->InsertPoint(13, 3,0,0);
    // points->InsertPoint(14, 3,0.5, 0.5);
    // points->InsertPoint(15, 4,1,0);
    // points->InsertPoint(16, 4,0,0);
    // points->InsertPoint(17, 4,0.5,0.5);
    // // Die Punkte f�r die Pyramide.
    // points->InsertPoint(18, 5,0,0);
    // points->InsertPoint(19, 6,0,0);
    // points->InsertPoint(20, 6,1,0);
    // points->InsertPoint(21, 5,1,0);
    // points->InsertPoint(22, 5.5,0.5,1);

    // // Eine Voxel-Zelle 
	// vtkSmartPointer<vtkVoxel> aVoxel = vtkSmartPointer <vtkVoxel>::New();
    // for (int i=0; i<8; i++) 
	// 	aVoxel->GetPointIds()->SetId(i,i);
    // // Eine Tetraeder-Zelle
	// vtkSmartPointer<vtkTetra> aTetra = vtkSmartPointer<vtkTetra>::New();
    //    aTetra->GetPointIds()->SetId(0,8);
    //    aTetra->GetPointIds()->SetId(1,9);
    //    aTetra->GetPointIds()->SetId(2,10);
    //    aTetra->GetPointIds()->SetId(3,11);
    // // Eine Prisma-Zelle
	// vtkSmartPointer<vtkWedge> aWedge = vtkSmartPointer<vtkWedge>::New();
    //    aWedge->GetPointIds()->SetId(0,12);
    //    aWedge->GetPointIds()->SetId(1,13);
    //    aWedge->GetPointIds()->SetId(2,14);
    //    aWedge->GetPointIds()->SetId(3,15);
    //    aWedge->GetPointIds()->SetId(4,16);
    //    aWedge->GetPointIds()->SetId(5,17);
    // vtkSmartPointer<vtkPyramid> aPyramid = vtkSmartPointer<vtkPyramid>::New();
    //    aPyramid->GetPointIds()->SetId(0,18);
    //    aPyramid->GetPointIds()->SetId(1,19);
    //    aPyramid->GetPointIds()->SetId(2,20);
    //    aPyramid->GetPointIds()->SetId(3,21);
    //    aPyramid->GetPointIds()->SetId(4,22);
       
    // Die Zellen in den Datensatz ablegen.
    // Instanz eines unstrukturierten Gitters;
    // die Instanz points wird als Gitterpunkte verwendet.
    // vtkSmartPointer<vtkUnstructuredGrid> theGrid = vtkSmartPointer<vtkUnstructuredGrid>::New();
    //    theGrid->Allocate(1,1);
    //    theGrid->SetPoints(points);
    //    theGrid->InsertNextCell(aVoxel->GetCellType(),aVoxel->GetPointIds());
    //    theGrid->InsertNextCell(aTetra->GetCellType(),aTetra->GetPointIds());
    //    theGrid->InsertNextCell(aWedge->GetCellType(),aWedge->GetPointIds());
    //    theGrid->InsertNextCell(aPyramid->GetCellType(),aPyramid->GetPointIds());
       
    // // Die Daten abbilden auf ein polygonales Netz mit einer Instanz
    // // von vtkDataSetMapper.
    // vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();
    //     mapper->SetInputData(theGrid);
    
    // // Grafische Attribute f�r die Darstellung als 
    // // Instanz der Klasse vtkProperty    
    // vtkSmartPointer<vtkProperty> property = vtkSmartPointer<vtkProperty>::New();
    //     property->SetDiffuseColor(0.8,0.0,0.0);
        
    // // Ein grafisches Objekt, als Attribute wird
    // // die Instanz property verwendet.
    // vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    //     actor->SetMapper(mapper);
    //     actor->SetProperty(property);
        
    // // Einen Renderer f�r die interaktive Darstellung instanzieren,
    // // die Hintergrundfarbe setzen und Einstellungen an der aktiven
    // // Kamera.
    // vtkSmartPointer<vtkRenderer> render = vtkSmartPointer<vtkRenderer>::New();
    //  	render->AddActor(actor);
    //     render->SetBackground(1,1,1);
    //     // Die Kamera des Renderers einstellen.
    //     //render->GetActiveCamera()->Elevation(20.0);
        
    // // Als letzten Schritt ben�tigen wir ein Fenster, in das der Renderer
    // // ausgibt.
    // vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
    //     renWin->SetSize(640,480);
	//     renWin->AddRenderer(render);
	//     renWin->Render();
	    
    // // Mit den Daten interagieren.
    // // Typische Keyboard-Shortcuts in VTK:
    // //    q oder e: beenden des Programms
    // //           r: Reset der Ansicht
    // vtkRenderWindowInteractor *interact = vtkRenderWindowInteractor::New();
    
	// interact->SetRenderWindow(renWin);
    // renWin->Render();
    // interact->Start();

    // // Aufr�umen; die Konstruktoren in VTK werden als Memberfunktion
    // // Delete() aufgerufen.
    // interact->Delete();
    // renWin->Delete();
    // render->Delete();
    // property->Delete();
    // actor->Delete();
    // mapper->Delete();
    // theGrid->Delete();
    // points->Delete();    
   
	return EXIT_SUCCESS;
}
