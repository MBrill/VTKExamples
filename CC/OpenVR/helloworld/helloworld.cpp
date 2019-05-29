#include <vtkSphereSource.h>
#include <vtkCubeSource.h>
#include <vtkPlaneSource.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkOpenVRRenderWindow.h>
#include <vtkOpenVRRenderer.h>
#include <vtkOpenVRRenderWindowInteractor.h>
#include <vtkOpenVRCamera.h>
#include <vtkProperty.h>
#include <array>
#include <cstdlib>
#include <string>
#include <vector>
#include <vtkCellArray.h>
#include <vtkPoints.h>
#include <vtkNamedColors.h>
#include <vtkColor.h>
#include "testInteractorStyle.h"
int main(int, char *[])
{
  //Farben
  vtkSmartPointer<vtkNamedColors> colors =
  vtkSmartPointer<vtkNamedColors>::New();

	//Ebene
  vtkSmartPointer<vtkPlaneSource> ebene =
    vtkSmartPointer<vtkPlaneSource>::New();
  ebene->SetOrigin(-5.0,0.0,-5.0);
  ebene->SetPoint1(-5.0,0.0,5.0);
  ebene->SetPoint2(5.0,0.0,-5.0);
  ebene->Update();

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
  mappers[8]->SetInputConnection(ebene->GetOutputPort());

  vtkSmartPointer<vtkActor> KugelVorneActor =
	  vtkSmartPointer<vtkActor>::New();
  KugelVorneActor->SetMapper(mappers[0]);
  KugelVorneActor->GetProperty()->SetColor(colors->GetColor3d("red").GetData());
  vtkSmartPointer<vtkActor> KugelHintenActor =
	  vtkSmartPointer<vtkActor>::New();
  KugelHintenActor->SetMapper(mappers[1]);
  KugelHintenActor->GetProperty()->SetColor(colors->GetColor3d("yellow").GetData());
  vtkSmartPointer<vtkActor> KugelRechtsActor =
	  vtkSmartPointer<vtkActor>::New();
  KugelRechtsActor->SetMapper(mappers[2]);
  KugelRechtsActor->GetProperty()->SetColor(colors->GetColor3d("blue").GetData());
  vtkSmartPointer<vtkActor> KugelLinksActor =
	  vtkSmartPointer<vtkActor>::New();
  KugelLinksActor->SetMapper(mappers[3]);
  KugelLinksActor->GetProperty()->SetColor(colors->GetColor3d("yellow").GetData());
  vtkSmartPointer<vtkActor> UrsprungActor =
	  vtkSmartPointer<vtkActor>::New();
  UrsprungActor->SetMapper(mappers[4]);
  UrsprungActor->GetProperty()->SetColor(colors->GetColor3d("white").GetData());
  vtkSmartPointer<vtkActor> xAchseActor =
	  vtkSmartPointer<vtkActor>::New();
  xAchseActor->SetMapper(mappers[5]);
  xAchseActor->GetProperty()->SetColor(colors->GetColor3d("red").GetData());
  vtkSmartPointer<vtkActor> yAchseActor =
	  vtkSmartPointer<vtkActor>::New();
  yAchseActor->SetMapper(mappers[6]);
  yAchseActor->GetProperty()->SetColor(colors->GetColor3d("green").GetData());
  vtkSmartPointer<vtkActor> zAchseActor =
	  vtkSmartPointer<vtkActor>::New();
  zAchseActor->SetMapper(mappers[7]);
  zAchseActor->GetProperty()->SetColor(colors->GetColor3d("blue").GetData());
  vtkSmartPointer<vtkActor> ebeneActor =
	  vtkSmartPointer<vtkActor>::New();
  ebeneActor->SetMapper(mappers[8]);
  ebeneActor->GetProperty()->SetColor(colors->GetColor3d("grey").GetData());

  //Create a renderer, render window, and interactor
  vtkSmartPointer<vtkOpenVRRenderer> renderer = vtkSmartPointer<vtkOpenVRRenderer>::New();

  //Add the actor to the scene
  renderer->AddActor(KugelVorneActor);
  renderer->AddActor(KugelHintenActor);
  renderer->AddActor(KugelRechtsActor);
  renderer->AddActor(KugelLinksActor);
  renderer->AddActor(UrsprungActor);
  renderer->AddActor(xAchseActor);
  renderer->AddActor(yAchseActor);
  renderer->AddActor(zAchseActor);
  renderer->AddActor(ebeneActor);
  renderer->SetBackground(colors->GetColor3d("white").GetData());
  vtkSmartPointer<vtkOpenVRRenderWindow> renderWindow = 
    vtkSmartPointer<vtkOpenVRRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  renderWindow->SetWindowName("Helloworld");
  renderWindow->SetSize(800,640);
  vtkSmartPointer<vtkOpenVRRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkOpenVRRenderWindowInteractor>::New();
  
  vtkSmartPointer<TestInteractorStyle> style = vtkSmartPointer<TestInteractorStyle>::New();
  style->SetActor(KugelVorneActor);
  renderWindowInteractor->SetInteractorStyle(style);
  vtkSmartPointer<vtkOpenVRCamera> cam = 
    vtkSmartPointer<vtkOpenVRCamera>::New();
  renderer->SetActiveCamera(cam);
  
  //Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();
 
  return EXIT_SUCCESS;
}
