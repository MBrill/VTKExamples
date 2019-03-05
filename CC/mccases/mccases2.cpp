 // --------------------------------------------------------------------------------
//   Visualisierung zweier benachbarter Voxel 
//   und Darstellung von Fällen für Marching Cubes 
// --------------------------------------------------------------------------------
#include <vtkSmartPointer.h>
#include <vtkFloatArray.h>
#include <vtkPointData.h>
#include <vtkPoints.h>
#include <vtkVoxel.h>
#include <vtkUnstructuredGrid.h>
#include <vtkSphereSource.h>
#include <vtkCubeSource.h>
#include <vtkExtractEdges.h>
#include <vtkContourGrid.h>
#include <vtkPolyDataMapper.h>
#include <vtkDataSetMapper.h>
#include <vtkProperty.h>
#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

int main(void)
{
///////
// Der Einheitswürfel in einem unstrukturierten Gitter
// Zuerst die Skalare, dann die Punkte, Voxel und
// als letzten Schritt ein vtkUnstructuredGrid instanzieren.
///////
vtkSmartPointer<vtkFloatArray> daten = vtkSmartPointer<vtkFloatArray>::New();
    // Die Daten für den ersten Voxel
	daten->InsertNextValue(1.0);
	daten->InsertNextValue(1.0);
	daten->InsertNextValue(0.0);
	daten->InsertNextValue(0.0);
	daten->InsertNextValue(0.0);
	daten->InsertNextValue(0.0);
	daten->InsertNextValue(0.0);
	daten->InsertNextValue(1.0);
	// Die Daten für die nächste Zelle
	daten->InsertNextValue(1.0);
	daten->InsertNextValue(1.0);
	daten->InsertNextValue(1.0);
	daten->InsertNextValue(1.0);

////
// Geometrie erzeugen
////
vtkSmartPointer<vtkPoints> punkte = vtkSmartPointer<vtkPoints>::New();
    // Das erste Voxel
    punkte->InsertNextPoint(0,0,0);
	punkte->InsertNextPoint(1,0,0);
	punkte->InsertNextPoint(0,1,0);
    punkte->InsertNextPoint(1,1,0);
	punkte->InsertNextPoint(0,0,1);
	punkte->InsertNextPoint(1,0,1);
    punkte->InsertNextPoint(0,1,1);
	punkte->InsertNextPoint(1,1,1);    
	// Die vier Punkte für die nächste Zelle
	punkte->InsertNextPoint(2,0,0);    
	punkte->InsertNextPoint(2,1,0);    
	punkte->InsertNextPoint(2,0,1);    
	punkte->InsertNextPoint(2,1,1);    
		        
////
// Topologie erzeugen
////
	vtkSmartPointer<vtkVoxel> voxel1 = vtkSmartPointer<vtkVoxel>::New();
    for (int i=0; i<8; i++) voxel1->GetPointIds()->SetId(i,i);
	vtkSmartPointer<vtkVoxel> voxel2 = vtkSmartPointer<vtkVoxel>::New();
    voxel2->GetPointIds()->SetId(0,1);
    voxel2->GetPointIds()->SetId(1,8);
    voxel2->GetPointIds()->SetId(2,3);
    voxel2->GetPointIds()->SetId(3,9);
    voxel2->GetPointIds()->SetId(4,5);
    voxel2->GetPointIds()->SetId(5,10);
    voxel2->GetPointIds()->SetId(6,7);
    voxel2->GetPointIds()->SetId(7,11);

////
// Das Unstructured Grid erzeugen und die Daten einbauen
////
vtkSmartPointer<vtkUnstructuredGrid> twocubes = vtkSmartPointer<vtkUnstructuredGrid>::New();
       twocubes->Allocate(12,12);
       twocubes->SetPoints(punkte);
       twocubes->GetPointData()->SetScalars(daten); 
       twocubes->InsertNextCell(voxel1->GetCellType(), voxel1->GetPointIds());
       twocubes->InsertNextCell(voxel2->GetCellType(), voxel2->GetPointIds());

///////
// Mit dem Marching Cubes (in vtkContourGrid) die Iso-Fläche zu C=0.5 berechnen, die Dreiecke
// an einen vtkActor übergeben und entsprechendes Material definieren.
///////
double contourValue;
contourValue = 0.5;

vtkSmartPointer<vtkContourGrid> marching = vtkSmartPointer<vtkContourGrid>::New();
       marching->SetInputData(twocubes);
       marching->SetValue(0, contourValue);

///////
// Mapper aufrufen
///////
vtkSmartPointer<vtkPolyDataMapper> dreiecke = vtkSmartPointer<vtkPolyDataMapper>::New();
       dreiecke->SetInputConnection(marching->GetOutputPort());
       dreiecke->ScalarVisibilityOff();

///////
// Material und Actor für die Konturflächen
///////
vtkSmartPointer<vtkProperty> konturMaterial = vtkSmartPointer<vtkProperty>::New();
    konturMaterial->SetDiffuseColor(0.5, 0.5, 0.4);
	konturMaterial->SetSpecular(0.4);
	konturMaterial->SetSpecularPower(10);
	konturMaterial->SetOpacity(0.8);

vtkSmartPointer<vtkActor> kontur = vtkSmartPointer<vtkActor>::New();
       kontur->SetMapper(dreiecke);
       kontur->SetProperty(konturMaterial);

///////
// Den Würfel als Drahtmodell ausgeben; dazu zusätzlich die Ecken mit
// Funktionswert 1.0 durch kleine Kugeln markieren.
///////
vtkSmartPointer<vtkProperty> modellMaterial = vtkSmartPointer<vtkProperty>::New();
    modellMaterial->SetRepresentationToWireframe ();
	modellMaterial->SetLineWidth(3.0);
	modellMaterial->SetDiffuseColor(0.25, 0.25, 0.25);
	modellMaterial->SetSpecular(0.4);
	modellMaterial->SetSpecularPower(10);

vtkSmartPointer<vtkDataSetMapper> modellMapper = vtkSmartPointer<vtkDataSetMapper>::New();
    modellMapper->SetInputData(twocubes);
	modellMapper->ScalarVisibilityOff();

vtkSmartPointer<vtkActor> modellKanten = vtkSmartPointer<vtkActor>::New();
    modellKanten->SetMapper(modellMapper);
  	modellKanten->SetProperty(modellMaterial);

///////
// Kugeln für die Ecken erzeugen, an denen der Wert 1 angenommen wird
///////
double radius = 0.04;

vtkSmartPointer<vtkSphereSource> ecke = vtkSmartPointer<vtkSphereSource>::New();
    ecke->SetRadius(radius);

	vtkSmartPointer<vtkPolyDataMapper> eckenMapper = vtkPolyDataMapper::New();
    eckenMapper->SetInputConnection(ecke->GetOutputPort());
	eckenMapper->ScalarVisibilityOff();

	vtkSmartPointer<vtkProperty> eckenMaterial = vtkSmartPointer<vtkProperty>::New();
   eckenMaterial->SetDiffuseColor(0.89, 0.81, 0.34);

///////
//  Je nach ausgewähltem Fall Kugeln ausgeben. Dafür werden
//  maximal 4 Ecken benötigt für die Fälle 3, 5 und 12.
///////
vtkSmartPointer<vtkActor> ecke1 = vtkSmartPointer<vtkActor>::New();
    ecke1->SetMapper(eckenMapper);
    ecke1->SetProperty(eckenMaterial);
vtkSmartPointer<vtkActor> ecke2 = vtkSmartPointer<vtkActor>::New();
    ecke2->SetMapper(eckenMapper);
    ecke2->SetProperty(eckenMaterial);
vtkSmartPointer<vtkActor> ecke3 = vtkSmartPointer<vtkActor>::New();
    ecke3->SetMapper(eckenMapper);
    ecke3->SetProperty(eckenMaterial);
vtkSmartPointer<vtkActor> ecke4 = vtkSmartPointer<vtkActor>::New();
    ecke4->SetMapper(eckenMapper);
    ecke4->SetProperty(eckenMaterial);
vtkSmartPointer<vtkActor> ecke5 = vtkSmartPointer<vtkActor>::New();
    ecke5->SetMapper(eckenMapper);
    ecke5->SetProperty(eckenMaterial);
vtkSmartPointer<vtkActor> ecke6 = vtkSmartPointer<vtkActor>::New();
    ecke6->SetMapper(eckenMapper);
    ecke6->SetProperty(eckenMaterial);
vtkSmartPointer<vtkActor> ecke7 = vtkSmartPointer<vtkActor>::New();
    ecke7->SetMapper(eckenMapper);
    ecke7->SetProperty(eckenMaterial);

ecke1->SetPosition(0.0, 0.0, 0.0);
ecke2->SetPosition(1.0, 0.0, 0.0);
ecke3->SetPosition(1.0, 1.0, 1.0);
ecke4->SetPosition(2.0, 0.0, 0.0);
ecke5->SetPosition(2.0, 1.0, 0.0);
ecke6->SetPosition(2.0, 0.0, 1.0);
ecke7->SetPosition(2.0, 1.0, 1.0);
                
//
// Eine Basisfläche für unser Modell
//
vtkSmartPointer<vtkCubeSource> basisQuader = vtkSmartPointer<vtkCubeSource>::New();
    basisQuader->SetXLength(3.1);
    basisQuader->SetYLength(0.01);
    basisQuader->SetZLength(1.5);

vtkSmartPointer<vtkPolyDataMapper> basisMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    basisMapper->SetInputConnection(basisQuader->GetOutputPort());
    basisMapper->ScalarVisibilityOff();
	
	// Bodenplatte
vtkSmartPointer<vtkActor> basis = vtkSmartPointer<vtkActor>::New();
    basis->SetMapper(basisMapper);
    basis->SetPosition(1.0, -0.09, 0.5);

///////
// Sicht, Renderer, Fenster und Interaktionen ...
///////
vtkSmartPointer<vtkCamera> camera = vtkSmartPointer<vtkCamera>::New();
     camera->Dolly(1.2);
     camera->Azimuth(20);
     camera->Elevation(15);

vtkSmartPointer<vtkRenderer> ren = vtkSmartPointer<vtkRenderer>::New();
     ren->MakeLight();
     ren->SetBackground(1.0, 1.0, 1.0);
     ren->AddActor(ecke1);
     ren->AddActor(ecke2);
     ren->AddActor(ecke3);
     ren->AddActor(ecke4);
     ren->AddActor(ecke5);
     ren->AddActor(ecke6);
     ren->AddActor(ecke7);
     ren->AddActor(modellKanten);
     ren->AddActor(kontur);
     ren->AddActor(basis);
     ren->SetActiveCamera(camera);
     ren->LightFollowCameraOn();
     ren->ResetCamera();	 
     camera->Zoom(1.25);
	 
	 vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
	 renWin->AddRenderer(ren);
	 renWin->SetSize(1280, 720);
	 renWin->SetPosition(100, 50);

	 vtkSmartPointer<vtkRenderWindowInteractor> iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    iren->SetRenderWindow(renWin);

renWin->Render();
iren->Start();

return EXIT_SUCCESS;
}

