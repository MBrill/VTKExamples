#include <vtkSphereSource.h>
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

  vtkSmartPointer<vtkSphereSource> red = 
    vtkSmartPointer<vtkSphereSource>::New();
  red->SetRadius(0.5);
  red->SetCenter(0.0,0.0,0.0);
  red->SetPhiResolution(64);
  red->SetThetaResolution(64);
  //red->Update();

  vtkSmartPointer<vtkSphereSource> yellow = 
    vtkSmartPointer<vtkSphereSource>::New();
  yellow->SetRadius(0.5);
  yellow->SetCenter(10.0,0.0,0.0);
  yellow->SetPhiResolution(64);
  yellow->SetThetaResolution(64);
  //yellow->Update();
  
  //Create a mapper and actor
  //size_t size = 10;
  std::vector<vtkSmartPointer<vtkPolyDataMapper>> mappers;
  mappers.push_back(vtkSmartPointer<vtkPolyDataMapper>::New());
  mappers[0]->SetInputConnection(red->GetOutputPort());
  mappers.push_back(vtkSmartPointer<vtkPolyDataMapper>::New());
  mappers[1]->SetInputConnection(yellow->GetOutputPort());

  /*vtkSmartPointer<vtkPolyDataMapper> redMapper =
	  vtkSmartPointer<vtkPolyDataMapper>::New();
      redMapper->SetInputConnection(red->GetOutputPort());*/

  vtkSmartPointer<vtkActor> redActor =
	  vtkSmartPointer<vtkActor>::New();
      //redActor->SetMapper(redMapper);
      redActor->SetMapper(mappers[0]);
	  redActor->GetProperty()->SetColor(1.0, 0.0, 0.0);

  /*vtkSmartPointer<vtkPolyDataMapper> yellowMapper =
		  vtkSmartPointer<vtkPolyDataMapper>::New();
  yellowMapper->SetInputConnection(yellow->GetOutputPort());*/

  vtkSmartPointer<vtkActor> yellowActor =
		  vtkSmartPointer<vtkActor>::New();
      //yellowActor->SetMapper(yellowMapper);
	  yellowActor->SetMapper(mappers[1]);
      yellowActor->GetProperty()->SetColor(1.0, 1.0, 0.0);

  //Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();

  //Add the actor to the scene
  //renderer->AddActor(actors[0]);
  //renderer->AddActor(actors[1]);
  renderer->AddActor(redActor);
  renderer->AddActor(yellowActor);
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
