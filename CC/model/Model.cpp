// --------------------------------------------------------------------------------------
//   VTK Beispiel mit drei Renderern, zwei Fenstern und zwei Viewports
// --------------------------------------------------------------------------------------
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkConeSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkCubeSource.h"
#include "vtkSphereSource.h"
#include "vtkProperty.h"
#include <vtkSmartPointer.h>

int main (void)
{
  // Zwei Renderer und zwei Fenster erzeugen
  vtkSmartPointer<vtkRenderer> ren1 = vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderer> ren2 = vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renWindow1 = vtkSmartPointer<vtkRenderWindow>::New();
    renWindow1->SetSize(800, 400);
	renWindow1->SetPosition(100, 100);
    renWindow1->AddRenderer(ren1);
    renWindow1->AddRenderer(ren2);
  vtkSmartPointer<vtkRenderWindowInteractor> iren1 = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    iren1->SetRenderWindow(renWindow1);

  // Noch ein Renderer, ein Fenster und ein Interactor
  vtkSmartPointer<vtkRenderer> ren3 = vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renWindow2 = vtkSmartPointer<vtkRenderWindow>::New();
    renWindow2->SetSize(400, 400);
	renWindow2->SetPosition(1100, 100);
    renWindow2->AddRenderer(ren3);
  vtkSmartPointer<vtkRenderWindowInteractor> iren2 = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    iren2->SetRenderWindow(renWindow2);

  // Einen Actor mit einem Kegel erzeugen
  vtkSmartPointer<vtkConeSource> cone = vtkSmartPointer<vtkConeSource>::New();
     cone->SetResolution(8);
  vtkSmartPointer<vtkPolyDataMapper> coneMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    coneMapper->SetInputConnection(cone->GetOutputPort());
  vtkSmartPointer<vtkActor> coneActor = vtkSmartPointer<vtkActor>::New();
    coneActor->SetMapper(coneMapper);
    coneActor->GetProperty()->SetColor(0.2000,0.6300,0.7900);

  // Einen Actor mit einem Würfel erzeugen
  vtkSmartPointer<vtkCubeSource> cube = vtkSmartPointer<vtkCubeSource>::New();
  vtkSmartPointer<vtkPolyDataMapper> cubeMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    cubeMapper->SetInputConnection(cube->GetOutputPort());
	vtkSmartPointer<vtkActor> cubeActor = vtkSmartPointer<vtkActor>::New();
    cubeActor->SetMapper(cubeMapper);
    cubeActor->GetProperty()->SetColor(0.9804,0.5020,0.4471);

  // Einen Actor erzeugen mit einer Kugel erzeugen
  vtkSmartPointer<vtkSphereSource> sphere = vtkSmartPointer<vtkSphereSource>::New();
    sphere->SetThetaResolution(16); 
	sphere->SetPhiResolution(16);
  vtkSmartPointer<vtkPolyDataMapper> sphereMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    sphereMapper->SetInputConnection(sphere->GetOutputPort());
  vtkSmartPointer<vtkActor> sphereActor = vtkSmartPointer<vtkActor>::New();
    sphereActor->SetMapper(sphereMapper);
    sphereActor->GetProperty()->SetColor(0.8900,0.6600,0.4100);

  // Die Actor-Instanzen an die Renderer übergeben
  ren1->AddActor(coneActor);
  ren2->AddActor(sphereActor);
  ren3->AddActor(cubeActor);

  // Fenster einstellen
  // Viewports und Hintergrundfarbe einstellen
  ren1->SetViewport(0,0,0.5,1);
  ren1->SetBackground(0.9,0.9,0.9);
  ren2->SetViewport(0.5,0,1,1);
  ren2->SetBackground(1,1,1);
  ren3->SetBackground(1,1,1);

  // Szene ausgeben
  renWindow1->Render();
  renWindow2->Render();

  // Interactor starten
  iren1->Start();
  iren2->Start();

  // Clean 
  ren1->Delete();
  ren2->Delete();
  renWindow1->Delete();
  iren1->Delete();
  ren3->Delete();
  renWindow2->Delete();
  iren2->Delete();
  cone->Delete();
  coneMapper->Delete();
  coneActor->Delete();
  cube->Delete();
  cubeMapper->Delete();
  cubeActor->Delete();
  sphere->Delete();
  sphereMapper->Delete();
  sphereActor->Delete();

  return 0;
}
