#include <vtkActor.h>
#include <vtkOpenVRCamera.h>
#include <vtkContourFilter.h>
#include <vtkLookupTable.h>
#include <vtkNamedColors.h>
#include <vtkOutlineFilter.h>
#include <vtkPointData.h>
#include <vtkPointSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkOpenVRRenderWindow.h>
#include <vtkOpenVRRenderWindowInteractor.h>
#include <vtkOpenVRRenderer.h>
#include <vtkStreamTracer.h>
#include <vtkStructuredPointsReader.h>
#include <vtkThresholdPoints.h>
#include <vtkTubeFilter.h>

int main (int argc, char *argv[])
{
  if (argc < 2)
  {
    std::cout << "Usage: " << argv[0] << " carotid.vtk" << std::endl;
    return EXIT_FAILURE;
  }

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
  vtkSmartPointer<vtkStructuredPointsReader> reader =
    vtkSmartPointer<vtkStructuredPointsReader>::New();
  reader->SetFileName(argv[1]);

  vtkSmartPointer<vtkPointSource> psource =
    vtkSmartPointer<vtkPointSource>::New();
  psource->SetNumberOfPoints(25);
  psource->SetCenter(133.1, 116.3, 5.0);
  psource->SetRadius(2.0);

  vtkSmartPointer<vtkThresholdPoints> threshold =
    vtkSmartPointer<vtkThresholdPoints>::New();
  threshold->SetInputConnection(reader->GetOutputPort());
  threshold->ThresholdByUpper(275);

  vtkSmartPointer<vtkStreamTracer> streamers =
    vtkSmartPointer<vtkStreamTracer>::New();
  streamers->SetInputConnection(reader->GetOutputPort());
  streamers->SetSourceConnection(psource->GetOutputPort());
//  streamers->SetMaximumPropagationUnitToTimeUnit();
  streamers->SetMaximumPropagation(100.0);
//  streamers->SetInitialIntegrationStepUnitToCellLengthUnit();
  streamers->SetInitialIntegrationStep(0.2);
  streamers->SetTerminalSpeed(.01);
  streamers->Update();
  double range[2];
  range[0] = streamers->GetOutput()->GetPointData()->GetScalars()->GetRange()[0];
  range[1] = streamers->GetOutput()->GetPointData()->GetScalars()->GetRange()[1];

  vtkSmartPointer<vtkTubeFilter> tubes =
    vtkSmartPointer<vtkTubeFilter>::New();
  tubes->SetInputConnection(streamers->GetOutputPort());
  tubes->SetRadius(0.3);
  tubes->SetNumberOfSides(6);
  tubes->SetVaryRadius(0);

  vtkSmartPointer<vtkLookupTable> lut =
    vtkSmartPointer<vtkLookupTable>::New();
  lut->SetHueRange(.667, 0.0);
  lut->Build();

  vtkSmartPointer<vtkPolyDataMapper> streamerMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  streamerMapper->SetInputConnection(tubes->GetOutputPort());
  streamerMapper->SetScalarRange(range[0], range[1]);
  streamerMapper->SetLookupTable(lut);

  vtkSmartPointer<vtkActor> streamerActor =
    vtkSmartPointer<vtkActor>::New();
  streamerActor->SetMapper(streamerMapper);

// contours of speed
  vtkSmartPointer<vtkContourFilter> iso =
    vtkSmartPointer<vtkContourFilter>::New();
  iso->SetInputConnection(reader->GetOutputPort());
  iso->SetValue(0, 175);

  vtkSmartPointer<vtkPolyDataMapper> isoMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  isoMapper->SetInputConnection(iso->GetOutputPort());
  isoMapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> isoActor =
    vtkSmartPointer<vtkActor>::New();
  isoActor->SetMapper(isoMapper);
  isoActor->GetProperty()->SetRepresentationToWireframe();
  isoActor->GetProperty()->SetOpacity(0.25);

// outline
  vtkSmartPointer<vtkOutlineFilter> outline =
    vtkSmartPointer<vtkOutlineFilter>::New();
  outline->SetInputConnection(reader->GetOutputPort());

  vtkSmartPointer<vtkPolyDataMapper> outlineMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  outlineMapper->SetInputConnection(outline->GetOutputPort());

  vtkSmartPointer<vtkActor> outlineActor =
    vtkSmartPointer<vtkActor>::New();
  outlineActor->SetMapper(outlineMapper);
  outlineActor->GetProperty()->SetColor(colors->GetColor3d("Black").GetData());

// Add the actors to the renderer, set the background and size
//
  ren1->AddActor(outlineActor);
  ren1->AddActor(streamerActor);
  ren1->AddActor(isoActor);
  ren1->SetBackground(colors->GetColor3d("Wheat").GetData());
  renWin->SetSize(640, 480);
  renWin->SetPhysicalScale(10.0);
  vtkSmartPointer<vtkOpenVRCamera> cam1 =
    vtkSmartPointer<vtkOpenVRCamera>::New();
  cam1->SetClippingRange(17.4043, 870.216);
  cam1->SetFocalPoint(136.71, 104.025, 23);
  cam1->SetPosition(204.747, 258.939, 63.7925);
  cam1->SetViewUp(-0.102647, -0.210897, 0.972104);
  cam1->Zoom(1.6);
  ren1->SetActiveCamera(cam1);

// render the image
//
  renWin->Render();
  iren->Start();

  return EXIT_SUCCESS;
}
