#include <vtkSmartPointer.h>

#include <vtkBYUReader.h>
#include <vtkOBJReader.h>
#include <vtkPLYReader.h>
#include <vtkPolyDataReader.h>
#include <vtkSTLReader.h>
#include <vtkSphereSource.h>
#include <vtkXMLPolyDataReader.h>

#include <vtkActor.h>
#include <vtkOpenVRCamera.h>
#include <vtkOpenVRInteractorStyle.h>
#include <vtkOpenVRRenderWindow.h>
#include <vtkOpenVRRenderWindowInteractor.h>
#include <vtkOpenVRRenderer.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>

#include <vtkNamedColors.h>
#include <vtkTimerLog.h>
#include <vtksys/SystemTools.hxx>

#include <algorithm>
#include <array>
#include <random>
#include <string>

namespace {
vtkSmartPointer<vtkPolyData> ReadPolyData(const char *fileName);
}

int main(int argc, char *argv[]) {
  // Vis Pipeline
  auto colors = vtkSmartPointer<vtkNamedColors>::New();

  auto renderer = vtkSmartPointer<vtkOpenVRRenderer>::New();

  auto renderWindow = vtkSmartPointer<vtkOpenVRRenderWindow>::New();
  renderWindow->SetSize(640, 480);
  renderWindow->AddRenderer(renderer);

  auto style = vtkSmartPointer<vtkOpenVRInteractorStyle>::New();
  auto interactor = vtkSmartPointer<vtkOpenVRRenderWindowInteractor>::New();
  interactor->SetInteractorStyle(style);
  interactor->SetRenderWindow(renderWindow);

  renderer->SetBackground(colors->GetColor3d("Wheat").GetData());
  renderer->UseHiddenLineRemovalOn();

  std::mt19937 mt(4355412); // Standard mersenne_twister_engine
  std::uniform_real_distribution<double> distribution(.6, 1.0);

  // PolyData file pipeline
  for (int i = 1; i < argc; ++i) {
    std::cout << "Loading: " << argv[i] << std::endl;
    auto polyData = ReadPolyData(argv[i]);

    // Visualize
    auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputData(polyData);

    std::array<double, 3> randomColor;
    randomColor[0] = distribution(mt);
    randomColor[1] = distribution(mt);
    randomColor[2] = distribution(mt);
    auto backProp = vtkSmartPointer<vtkProperty>::New();
    backProp->SetDiffuseColor(colors->GetColor3d("Banana").GetData());
    backProp->SetSpecular(.6);
    backProp->SetSpecularPower(30);

    auto actor = vtkSmartPointer<vtkActor>::New();
    actor->SetPosition(0.0,0.0,0.0);
    actor->SetMapper(mapper);
    actor->SetBackfaceProperty(backProp);
    actor->GetProperty()->SetDiffuseColor(randomColor.data());
    actor->GetProperty()->SetSpecular(.3);
    actor->GetProperty()->SetSpecularPower(30);
    renderer->AddActor(actor);
  }

  auto cam = vtkSmartPointer<vtkOpenVRCamera>::New();
  renderer->SetActiveCamera(cam);
  renderWindow->Render();
  interactor->Start();

  return EXIT_SUCCESS;
}

namespace {
vtkSmartPointer<vtkPolyData> ReadPolyData(const char *fileName) {
  vtkSmartPointer<vtkPolyData> polyData;
  std::string extension =
      vtksys::SystemTools::GetFilenameLastExtension(std::string(fileName));

  // Drop the case of the extension
  std::transform(extension.begin(), extension.end(), extension.begin(),
                 ::tolower);

  if (extension == ".ply") {
    auto reader = vtkSmartPointer<vtkPLYReader>::New();
    reader->SetFileName(fileName);
    reader->Update();
    polyData = reader->GetOutput();
  } else if (extension == ".vtp") {
    auto reader = vtkSmartPointer<vtkXMLPolyDataReader>::New();
    reader->SetFileName(fileName);
    reader->Update();
    polyData = reader->GetOutput();
  } else if (extension == ".obj") {
    auto reader = vtkSmartPointer<vtkOBJReader>::New();
    reader->SetFileName(fileName);
    reader->Update();
    polyData = reader->GetOutput();
  } else if (extension == ".stl") {
    auto reader = vtkSmartPointer<vtkSTLReader>::New();
    reader->SetFileName(fileName);
    reader->Update();
    polyData = reader->GetOutput();
  } else if (extension == ".vtk") {
    auto reader = vtkSmartPointer<vtkPolyDataReader>::New();
    reader->SetFileName(fileName);
    reader->Update();
    polyData = reader->GetOutput();
  } else if (extension == ".g") {
    auto reader = vtkSmartPointer<vtkBYUReader>::New();
    reader->SetGeometryFileName(fileName);
    reader->Update();
    polyData = reader->GetOutput();
  } else {
    auto source = vtkSmartPointer<vtkSphereSource>::New();
    source->Update();
    polyData = source->GetOutput();
  }
  return polyData;
}
} // namespace
