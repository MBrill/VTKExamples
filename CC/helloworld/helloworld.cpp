#include <vtkSphereSource.h>
#include <vtkCubeSource.h>
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
 
int main(int, char *[])
{
	//Ursprung
	vtkSmartPointer<vtkCubeSource> Ursprung =
		vtkSmartPointer<vtkCubeSource>::New();
	Ursprung->SetXLength(0.1);
	Ursprung->SetYLength(0.1);
	Ursprung->SetZLength(0.1);
	Ursprung->SetCenter(0.0, 0.0, 0.0);

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
  UrsprungActor->GetProperty()->SetColor(2.0, 2.0, 2.0);

  //Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();

  //Add the actor to the scene
  renderer->AddActor(KugelVorneActor);
  renderer->AddActor(KugelHintenActor);
  renderer->AddActor(KugelRechtsActor);
  renderer->AddActor(KugelLinksActor);
  renderer->AddActor(UrsprungActor);
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
