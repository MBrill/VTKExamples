#include <vtkSmartPointer.h>
#include <vtkImageActor.h>
#include <vtkImageMapToColors.h>
#include <vtkLookupTable.h>
#include <vtkDEMReader.h>
#include <vtkImageData.h>
#include <vtkImageMapper3D.h>
#include <vtkOpenVRRenderWindow.h>
#include <vtkOpenVRRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkOpenVRRenderer.h>
#include <vtkOpenVRCamera.h>

int main(int argc, char* argv[])
{
  // Verify arguments
  if(argc < 2)
  {
    std::cerr << "Required: filename.dem" << std::endl;
    return EXIT_FAILURE;
  }

  // Read the file
  vtkSmartPointer<vtkDEMReader> reader =
    vtkSmartPointer<vtkDEMReader>::New();
  reader->SetFileName(argv[1]);
  reader->Update();

  vtkSmartPointer<vtkLookupTable> lut =
    vtkSmartPointer<vtkLookupTable>::New();
  lut->SetHueRange(0.6, 0);
  lut->SetSaturationRange(1.0, 0);
  lut->SetValueRange(0.5, 1.0);
  lut->SetTableRange(reader->GetOutput()->GetScalarRange());

  // Visualize
  vtkSmartPointer<vtkImageMapToColors> mapColors =
    vtkSmartPointer<vtkImageMapToColors>::New();
  mapColors->SetLookupTable(lut);
  mapColors->SetInputConnection(reader->GetOutputPort());

  // Create an actor
  vtkSmartPointer<vtkImageActor> actor =
    vtkSmartPointer<vtkImageActor>::New();
  actor->GetMapper()->SetInputConnection(mapColors->GetOutputPort());

  // Setup renderer
  vtkSmartPointer<vtkOpenVRRenderer> renderer =
    vtkSmartPointer<vtkOpenVRRenderer>::New();
  renderer->AddActor(actor);
  //renderer->ResetCamera();

  // Setup render window
  vtkSmartPointer<vtkOpenVRRenderWindow> renderWindow =
    vtkSmartPointer<vtkOpenVRRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  // Setup render window interactor
  vtkSmartPointer<vtkOpenVRRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkOpenVRRenderWindowInteractor>::New();
  vtkSmartPointer<vtkInteractorStyleImage> style =
    vtkSmartPointer<vtkInteractorStyleImage>::New();

  renderWindowInteractor->SetInteractorStyle(style);

  // Render and start interaction

  renderWindowInteractor->SetRenderWindow(renderWindow);

  auto cam = vtkSmartPointer<vtkOpenVRCamera>::New();
  renderer->SetActiveCamera(cam);
  renderWindow->Render();
  renderWindowInteractor->Initialize();

  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
