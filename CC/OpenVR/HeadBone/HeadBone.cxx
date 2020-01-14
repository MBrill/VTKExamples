#include <vtkActor.h>
#include <vtkOpenVRCamera.h>
#include <vtkMarchingCubes.h>
#include <vtkMergePoints.h>
#include <vtkMetaImageReader.h>
#include <vtkNamedColors.h>
#include <vtkOutlineFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkOpenVRRenderWindow.h>
#include <vtkOpenVRRenderWindowInteractor.h>
#include <vtkOpenVRRenderer.h>

int main (int argc, char *argv[])
{
  if (argc < 2)
  {
    std::cout << "Usage: " << argv[0] << " FullHead.mhd" << std::endl;
    return EXIT_FAILURE;
  }

// Create the RenderWindow, Renderer and both Actors
//
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkOpenVRRenderer> ren1 =
    vtkSmartPointer<vtkOpenVRRenderer>::New();

  vtkSmartPointer<vtkOpenVRRenderWindow> renWin =
    vtkSmartPointer<vtkOpenVRRenderWindow>::New();
  renWin->AddRenderer(ren1);

  vtkSmartPointer<vtkOpenVRRenderWindowInteractor> iren =
    vtkSmartPointer<vtkOpenVRRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

// create pipeline
//

  vtkSmartPointer<vtkMetaImageReader> reader =
    vtkSmartPointer<vtkMetaImageReader>::New();
  reader->SetFileName(argv[1]);
  reader->Update();

  vtkSmartPointer<vtkMergePoints> locator =
    vtkSmartPointer<vtkMergePoints>::New();
  locator->SetDivisions(64, 64, 92);
  locator->SetNumberOfPointsPerBucket(2);
  locator->AutomaticOff();

  vtkSmartPointer<vtkMarchingCubes> iso =
    vtkSmartPointer<vtkMarchingCubes>::New();
  iso->SetInputConnection(reader->GetOutputPort());
  iso->ComputeGradientsOn();
  iso->ComputeScalarsOff();
  iso->SetValue(0, 1150);
  iso->SetLocator(locator);

  vtkSmartPointer<vtkPolyDataMapper> isoMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  isoMapper->SetInputConnection(iso->GetOutputPort());
  isoMapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> isoActor =
    vtkSmartPointer<vtkActor>::New();
  isoActor->SetMapper(isoMapper);
  isoActor->GetProperty()->SetColor(colors->GetColor3d("Wheat").GetData());

  vtkSmartPointer<vtkOutlineFilter> outline =
    vtkSmartPointer<vtkOutlineFilter>::New();
  outline->SetInputConnection(reader->GetOutputPort());

  vtkSmartPointer<vtkPolyDataMapper> outlineMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  outlineMapper->SetInputConnection(outline->GetOutputPort());

  vtkSmartPointer<vtkActor> outlineActor =
    vtkSmartPointer<vtkActor>::New();
  outlineActor->SetMapper(outlineMapper);

// Add the actors to the renderer, set the background and size
//
  auto cam = vtkSmartPointer<vtkOpenVRCamera>::New();
  ren1->SetActiveCamera(cam);

  ren1->AddActor(outlineActor);
  ren1->AddActor(isoActor);
  ren1->SetBackground(colors->GetColor3d("SlateGray").GetData());
  ren1->GetActiveCamera()->SetFocalPoint(0, 0, 0);
  ren1->GetActiveCamera()->SetPosition(0, -1, 0);
  ren1->GetActiveCamera()->SetViewUp(0, 0, -1);
  ren1->ResetCamera();
  ren1->GetActiveCamera()->Dolly(1.5);
  ren1->ResetCameraClippingRange();

  renWin->SetSize(640, 480);

  renWin->Render();
  iren->Start();
  return EXIT_SUCCESS;
}

