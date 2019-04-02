#include <vtkSphereSource.h>
#include <vtkCubeSource.h>
#include <vtkQuad.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkProperty.h>
#include <array>
#include <cstdlib>
#include <string>
#include <vector>
#include <vtkCellArray.h>
#include <vtkPoints.h>
#include <vtkQuad.h>
 
int main(int, char *[])
{
	//Ebene
	// Create four points (must be in counter clockwise order)
	double p0[3] = { -5.0, 0.0, 5.0 };
	double p1[3] = { -5.0, 0.0, -5.0 };
	double p2[3] = { 5.0, 0.0, -5.0 };
	double p3[3] = { 5.0, 0.0, 5.0 };

	// Add the points to a vtkPoints object
	vtkSmartPointer<vtkPoints> points =
		vtkSmartPointer<vtkPoints>::New();
	points->InsertNextPoint(p0);
	points->InsertNextPoint(p1);
	points->InsertNextPoint(p2);
	points->InsertNextPoint(p3);

	// Create a quad on the four points
	vtkSmartPointer<vtkQuad> quad =
		vtkSmartPointer<vtkQuad>::New();
	quad->GetPointIds()->SetId(0, 0);
	quad->GetPointIds()->SetId(1, 1);
	quad->GetPointIds()->SetId(2, 2);
	quad->GetPointIds()->SetId(3, 3);

	// Create a cell array to store the quad in
	vtkSmartPointer<vtkCellArray> quads =
		vtkSmartPointer<vtkCellArray>::New();
	quads->InsertNextCell(quad);

	// Create a polydata to store everything in
	vtkSmartPointer<vtkPolyData> polydata =
		vtkSmartPointer<vtkPolyData>::New();

	// Add the points and quads to the dataset
	polydata->SetPoints(points);
	polydata->SetPolys(quads);

	//Ursprung
	vtkSmartPointer<vtkCubeSource> Ursprung =
		vtkSmartPointer<vtkCubeSource>::New();
	Ursprung->SetXLength(0.1);
	Ursprung->SetYLength(0.1);
	Ursprung->SetZLength(0.1);
	Ursprung->SetCenter(0.0, 0.0, 0.0);

	//xAchse
	vtkSmartPointer<vtkCubeSource> xAchse =
		vtkSmartPointer<vtkCubeSource>::New();
	xAchse->SetXLength(0.1);
	xAchse->SetYLength(0.1);
	xAchse->SetZLength(0.1);
	xAchse->SetCenter(1.0, 0.0, 0.0);

	//yAchse
	vtkSmartPointer<vtkCubeSource> yAchse =
		vtkSmartPointer<vtkCubeSource>::New();
	yAchse->SetXLength(0.1);
	yAchse->SetYLength(0.1);
	yAchse->SetZLength(0.1);
	yAchse->SetCenter(0.0, 1.0, 0.0);

	//yAchse
	vtkSmartPointer<vtkCubeSource> zAchse =
		vtkSmartPointer<vtkCubeSource>::New();
	zAchse->SetXLength(0.1);
	zAchse->SetYLength(0.1);
	zAchse->SetZLength(0.1);
	zAchse->SetCenter(0.0, 0.0, 1.0);

	//KugelVorne
  vtkSmartPointer<vtkSphereSource> KugelVorne = 
    vtkSmartPointer<vtkSphereSource>::New();
  KugelVorne->SetRadius(0.5);
  KugelVorne->SetCenter(2.0,1.0,0.0);
  KugelVorne->SetPhiResolution(64);
  KugelVorne->SetThetaResolution(64);

  //KugelHinten
  vtkSmartPointer<vtkSphereSource> KugelHinten =
	  vtkSmartPointer<vtkSphereSource>::New();
  KugelHinten->SetRadius(0.5);
  KugelHinten->SetCenter(-2.0, 1.0, 0.0);
  KugelHinten->SetPhiResolution(64);
  KugelHinten->SetThetaResolution(64);

  //KugelRechts
  vtkSmartPointer<vtkSphereSource> KugelRechts =
	  vtkSmartPointer<vtkSphereSource>::New();
  KugelRechts->SetRadius(0.5);
  KugelRechts->SetCenter(0.0, 1.0, 2.0);
  KugelRechts->SetPhiResolution(64);
  KugelRechts->SetThetaResolution(64);

  //KugelLinks
  vtkSmartPointer<vtkSphereSource> KugelLinks =
	  vtkSmartPointer<vtkSphereSource>::New();
  KugelLinks->SetRadius(0.5);
  KugelLinks->SetCenter(0.0, 1.0, -2.0);
  KugelLinks->SetPhiResolution(64);
  KugelLinks->SetThetaResolution(64);
  
  //Create a mapper and actor
  std::vector<vtkSmartPointer<vtkPolyDataMapper>> mappers;
  mappers.push_back(vtkSmartPointer<vtkPolyDataMapper>::New());
  mappers[0]->SetInputConnection(KugelVorne->GetOutputPort());
  mappers.push_back(vtkSmartPointer<vtkPolyDataMapper>::New());
  mappers[1]->SetInputConnection(KugelHinten->GetOutputPort());
  mappers.push_back(vtkSmartPointer<vtkPolyDataMapper>::New());
  mappers[2]->SetInputConnection(KugelRechts->GetOutputPort());
  mappers.push_back(vtkSmartPointer<vtkPolyDataMapper>::New());
  mappers[3]->SetInputConnection(KugelLinks->GetOutputPort());
  mappers.push_back(vtkSmartPointer<vtkPolyDataMapper>::New());
  mappers[4]->SetInputConnection(Ursprung->GetOutputPort());
  mappers.push_back(vtkSmartPointer<vtkPolyDataMapper>::New());
  mappers[5]->SetInputConnection(xAchse->GetOutputPort());
  mappers.push_back(vtkSmartPointer<vtkPolyDataMapper>::New());
  mappers[6]->SetInputConnection(yAchse->GetOutputPort());
  mappers.push_back(vtkSmartPointer<vtkPolyDataMapper>::New());
  mappers[7]->SetInputConnection(zAchse->GetOutputPort());
  mappers.push_back(vtkSmartPointer<vtkPolyDataMapper>::New());
  mappers[8]->SetInputData(polydata);

  vtkSmartPointer<vtkActor> KugelVorneActor =
	  vtkSmartPointer<vtkActor>::New();
  KugelVorneActor->SetMapper(mappers[0]);
  KugelVorneActor->GetProperty()->SetColor(1.0, 0.0, 0.0);
  vtkSmartPointer<vtkActor> KugelHintenActor =
	  vtkSmartPointer<vtkActor>::New();
  KugelHintenActor->SetMapper(mappers[1]);
  KugelHintenActor->GetProperty()->SetColor(1.0, 0.0, 0.0);
  vtkSmartPointer<vtkActor> KugelRechtsActor =
	  vtkSmartPointer<vtkActor>::New();
  KugelRechtsActor->SetMapper(mappers[2]);
  KugelRechtsActor->GetProperty()->SetColor(0.0, 0.0, 1.0);
  vtkSmartPointer<vtkActor> KugelLinksActor =
	  vtkSmartPointer<vtkActor>::New();
  KugelLinksActor->SetMapper(mappers[3]);
  KugelLinksActor->GetProperty()->SetColor(0.0, 0.0, 1.0);
  vtkSmartPointer<vtkActor> UrsprungActor =
	  vtkSmartPointer<vtkActor>::New();
  UrsprungActor->SetMapper(mappers[4]);
  UrsprungActor->GetProperty()->SetColor(200.0, 200.0, 200.0);
  vtkSmartPointer<vtkActor> xAchseActor =
	  vtkSmartPointer<vtkActor>::New();
  xAchseActor->SetMapper(mappers[5]);
  xAchseActor->GetProperty()->SetColor(1.0, 0.0, 0.0);
  vtkSmartPointer<vtkActor> yAchseActor =
	  vtkSmartPointer<vtkActor>::New();
  yAchseActor->SetMapper(mappers[6]);
  yAchseActor->GetProperty()->SetColor(0.0, 1.0, 0.0);
  vtkSmartPointer<vtkActor> zAchseActor =
	  vtkSmartPointer<vtkActor>::New();
  zAchseActor->SetMapper(mappers[7]);
  zAchseActor->GetProperty()->SetColor(0.0, 0.0, 1.0);
  vtkSmartPointer<vtkActor> quadsActor =
	  vtkSmartPointer<vtkActor>::New();
  quadsActor->SetMapper(mappers[8]);
  quadsActor->GetProperty()->SetColor(100.0, 100.0, 100.0);

  //Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();

  //Add the actor to the scene
  renderer->AddActor(KugelVorneActor);
  renderer->AddActor(KugelHintenActor);
  renderer->AddActor(KugelRechtsActor);
  renderer->AddActor(KugelLinksActor);
  renderer->AddActor(UrsprungActor);
  renderer->AddActor(xAchseActor);
  renderer->AddActor(yAchseActor);
  renderer->AddActor(zAchseActor);
  renderer->AddActor(quadsActor);
  renderer->SetBackground(1, 1, 1);
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  renderWindow->SetWindowName("TEST");
  renderWindow->SetSize(800,640);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
 
  //Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();
 
  return EXIT_SUCCESS;
}
