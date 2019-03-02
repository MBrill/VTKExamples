// --------------------------------------------------------------------------------------
//   VTK Beispiel mit Rot-Grün Anaglyphen Stereo
// --------------------------------------------------------------------------------------
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkCubeSource.h"
#include "vtkProperty.h"
#include <vtkSmartPointer.h>

int main (void)
{
  // Zwei Renderer und zwei Fenster erzeugen
  vtkSmartPointer<vtkRenderer> ren = vtkSmartPointer<vtkRenderer>::New();

  vtkSmartPointer<vtkRenderWindow> renWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renWindow->SetSize(400, 400);
	renWindow->SetPosition(1100, 100);
	renWindow->SetFullScreen(true);
	renWindow->StereoCapableWindowOn();
	renWindow->SetStereoTypeToRedBlue();
	renWindow->SetStereoRender(true);
    renWindow->AddRenderer(ren);
  vtkSmartPointer<vtkRenderWindowInteractor> iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    iren->SetRenderWindow(renWindow);

  // Einen Actor mit einem Würfel erzeugen
  vtkSmartPointer<vtkCubeSource> cube = vtkSmartPointer<vtkCubeSource>::New();
  vtkSmartPointer<vtkPolyDataMapper> cubeMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    cubeMapper->SetInputConnection(cube->GetOutputPort());
	vtkSmartPointer<vtkActor> cubeActor = vtkSmartPointer<vtkActor>::New();
    cubeActor->SetMapper(cubeMapper);
    cubeActor->GetProperty()->SetColor(0.9804,0.5020,0.4471);

  // Die Actor-Instanzen an die Renderer übergeben
  ren->AddActor(cubeActor);

  // Fenster einstellen


  // Viewports und Hintergrundfarbe einstellen
  ren->SetBackground(0.9,0.9,0.9);

  // Szene ausgeben
  renWindow->Render();

  // Interactor starten
  iren->Start();

  // Clean 
  ren->Delete();
  renWindow->Delete();
  iren->Delete();
  cube->Delete();
  cubeMapper->Delete();
  cubeActor->Delete();

  return 0;
}
