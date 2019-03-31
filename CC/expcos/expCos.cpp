// Visualisierung eines skalaren Felds mit Hilfe von vtkWarp
#include <vtkSmartPointer.h>
#include "vtkActor.h"
#include "vtkCamera.h"
#include "vtkDataSetMapper.h"
#include "vtkFloatArray.h"
#include "vtkPlaneSource.h"
#include "vtkPoints.h"
#include "vtkPolyData.h"
#include "vtkPointData.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkInteractorStyleTrackballCamera.h"
#include "vtkRenderer.h"
#include "vtkTransform.h"
#include "vtkTransformPolyDataFilter.h"
#include "vtkWarpScalar.h"

int main( int argc, char *argv[] )
{
  int i, numPts;
  double x[3];
  double r, deriv;

  // Ebene, die wir verformen k�nnen mit einer gro�en Aufl�sung
  vtkSmartPointer<vtkPlaneSource> plane = vtkSmartPointer<vtkPlaneSource>::New();
         plane->SetResolution (300,300);

  // Skalierung f�r die Gr��e der Ebene
  vtkSmartPointer<vtkTransform> transform = vtkSmartPointer<vtkTransform>::New();
         transform->Scale(10.0,10.0,1.0);

  // Skalierung auf die Ebene anwenden
  vtkSmartPointer<vtkTransformPolyDataFilter> transF = vtkSmartPointer<vtkTransformPolyDataFilter>::New();
       transF->SetInputConnection(plane->GetOutputPort());
       transF->SetTransform(transform);
       transF->Update();
  
  // Bessel-Funktion in ein polygonales Netz speichern
  vtkSmartPointer<vtkPolyData> input = transF->GetOutput();
       numPts = input->GetNumberOfPoints();
  
  vtkSmartPointer<vtkPoints> newPts = vtkSmartPointer<vtkPoints>::New();
       newPts->SetNumberOfPoints(numPts);

  vtkSmartPointer<vtkFloatArray> derivs = vtkSmartPointer<vtkFloatArray>::New();
       derivs->SetNumberOfTuples(numPts);

  for (i = 0; i<numPts; i++)
  {
		   input->GetPoint(i, x);
		   r = sqrt(x[0] * x[0] + x[1] * x[1]);
		   x[2] = exp(-r) * cos(10.0*r);
		   newPts->SetPoint(i, x);
		   deriv = -exp(-r) * (cos(10.0*r) + 10.0*sin(10.0*r));
		   derivs->SetValue(i, deriv);
  }

  vtkSmartPointer<vtkPolyData> bessel = vtkSmartPointer<vtkPolyData>::New();
       bessel->CopyStructure(input);
       bessel->SetPoints(newPts);
       bessel->GetPointData()->SetScalars(derivs);


  // Punkte und Ableitungswerte schonmal l�schen
  // VTK macht reference counting - da kann nichts passieren :-)
  newPts->Delete(); 
  derivs->Delete();
  
  // Ebene verformen
  vtkSmartPointer<vtkWarpScalar> warp = vtkSmartPointer<vtkWarpScalar>::New();
         warp->SetInputData(bessel);
         warp->XYPlaneOn();
         warp->SetScaleFactor(0.5);
  
  // Mapper, Actor, Renderer
  vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();
       mapper->SetInputConnection(warp->GetOutputPort());
       mapper->SetScalarRange(bessel->GetScalarRange());
  
  vtkSmartPointer<vtkActor> carpet = vtkSmartPointer<vtkActor>::New();
       carpet->SetMapper(mapper);

  vtkSmartPointer<vtkRenderer> ren = vtkSmartPointer<vtkRenderer>::New();
       ren->AddActor(carpet);
       ren->SetBackground(1.0, 1.0, 1.0);
       ren->ResetCamera();
       ren->GetActiveCamera()->Zoom(1.5);
  vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
       renWin->AddRenderer(ren);
	   renWin->SetSize(1280, 768);
	   renWin->SetPosition(100, 100);
	   renWin->Render();
	   // Wir w�hlen einen Stil aus und verwenden nicht den Default
	   vtkSmartPointer<vtkInteractorStyleTrackballCamera> style =
		   vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();

  vtkSmartPointer<vtkRenderWindowInteractor> iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);
  iren->SetInteractorStyle(style);

  iren->Initialize();
  iren->Start();

  // Clean up
  ren->Delete();
  renWin->Delete();
  style->Delete();
  iren->Delete();
  plane->Delete();
  transform->Delete();
  transF->Delete();
  bessel->Delete();
  warp->Delete();
  mapper->Delete();
  carpet->Delete();

  return EXIT_SUCCESS;
}
