// --------------------------------------------------------------------------------------
//   VTK Beispiel mit Rot-Blau Anaglyphen Stereo
//
// Aus der Online-Doku von VTKRenderWindow
//
// Anaglyph mode is a superset of RedBlue mode, but the color output channels 
// can be configured using the AnaglyphColorMask and the color of the original image 
// can be (somewhat) maintained using AnaglyphColorSaturation; 
// the default colors for Anaglyph mode is red-cyan. 
// --------------------------------------------------------------------------------------
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkCubeSource.h"
#include "vtkProperty.h"
#include "vtkSmartPointer.h"

int main (void)
{
  // Renderer und Fenster erzeugen
  vtkSmartPointer<vtkRenderer> ren = vtkSmartPointer<vtkRenderer>::New();

  vtkSmartPointer<vtkRenderWindow> renWindow = vtkSmartPointer<vtkRenderWindow>::New();
    // Fenster-Attribute, falls wir fullscreen kommentieren
    renWindow->SetSize(800, 450);
    renWindow->SetPosition(200, 100);
    // Fullscreen starten, falls die nächste Zeile nicht kommentiert wird
    renWindow->SetFullScreen(true);
    // Stereo-Eigenschaften einstellen
	renWindow->StereoCapableWindowOn();
	renWindow->SetStereoTypeToAnaglyph();
	renWindow->SetStereoRender(true);
    renWindow->AddRenderer(ren);

   vtkSmartPointer<vtkRenderWindowInteractor> iren = 
	     vtkSmartPointer<vtkRenderWindowInteractor>::New();
    iren->SetRenderWindow(renWindow);

  // Einen Actor mit einem Würfel erzeugen
  vtkSmartPointer<vtkCubeSource> cube = vtkSmartPointer<vtkCubeSource>::New();
  vtkSmartPointer<vtkPolyDataMapper> cubeMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    cubeMapper->SetInputConnection(cube->GetOutputPort());
  vtkSmartPointer<vtkActor> cubeActor = vtkSmartPointer<vtkActor>::New();
    cubeActor->SetMapper(cubeMapper);
    cubeActor->GetProperty()->SetColor(1.0, 1.0, 1.0);

  // Die Actor-Instanzen an die Renderer übergeben und darstellen
  ren->AddActor(cubeActor);
  ren->SetBackground(0.9,0.9,0.9);
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
