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
  red->Update();

  vtkSmartPointer<vtkSphereSource> yellow = 
    vtkSmartPointer<vtkSphereSource>::New();
  yellow->SetRadius(0.5);
  yellow->SetCenter(10.0,0.0,0.0);
  
  //Create a mapper and actor
  size_t size = 10;
  std::vector<vtkSmartPointer<vtkPolyDataMapper>> mappers;
  mappers.push_back(vtkSmartPointer<vtkPolyDataMapper>::New());
  mappers[0]->SetInputConnection(red->GetOutputPort());
  mappers.push_back(vtkSmartPointer<vtkPolyDataMapper>::New());
  mappers[1]->SetInputConnection(yellow->GetOutputPort());
  std::vector<vtkSmartPointer<vtkActor>> actors(size, vtkSmartPointer<vtkActor>::New()); 
  actors[0]->SetMapper(mappers[0]);
  actors[1]->SetMapper(mappers[1]);
  
  //Set the color of the sphere
  actors[0]->GetProperty()->SetColor(1.0, 0.0, 0.0); //(R,G,B)
  actors[1]->GetProperty()->SetColor(1.0, 1.0, 0.0); //(R,G,B)
  //Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  renderWindow->SetWindowName("TEST");
  renderWindow->SetSize(800,640);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
 
  //Add the actor to the scene
  renderer->AddActor(actors[0]);
  renderer->AddActor(actors[1]);
  renderer->SetBackground(1,1,1); 
  
 
 
  //Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();
 
  return EXIT_SUCCESS;
}
