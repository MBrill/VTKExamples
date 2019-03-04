//  ---------------------------------------------------------
//   VTK-Pipeline zum Einlesen und Darstellen eines
//   unstructured Grid
//  ---------------------------------------------------------
#include <fstream>
#include <cmath>
#include <iostream>

#include <vtkSmartPointer.h>
#include <vtkUnstructuredGridReader.h>
#include <vtkLookupTable.h>
#include <vtkUnstructuredGrid.h>
#include <vtkDataSetMapper.h>
#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

int main( int argc, char *argv[] )
{
// Reader-Instanz
vtkSmartPointer<vtkUnstructuredGridReader> reader = vtkSmartPointer<vtkUnstructuredGridReader>::New();
   reader->SetFileName("manual.vtk");
   reader->SetScalarsName("skalare");
   reader->Update();

// Lookup Table von blau nach rot
vtkSmartPointer<vtkLookupTable> lut = vtkSmartPointer<vtkLookupTable>::New();
   lut->SetNumberOfColors(256);
   lut->SetHueRange(0.667,0.0);
   lut->SetSaturationRange(1.0,1.0);
   lut->SetValueRange(1.0,1.0);
   lut->SetRange(reader->GetOutput()->GetScalarRange());
   lut->Build();

vtkSmartPointer<vtkUnstructuredGrid> grid = vtkSmartPointer<vtkUnstructuredGrid>::New();
  grid = reader->GetOutput();
  grid->CopyStructure(reader->GetOutput());

// Grafikausgabe
vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();
   mapper->SetInputConnection(reader->GetOutputPort());
   mapper->SetLookupTable(lut);
   mapper->SetScalarRange(reader->GetOutput()->GetScalarRange());
   mapper->ScalarVisibilityOn();

vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
   actor->SetMapper(mapper);

vtkSmartPointer<vtkRenderer> ren = vtkSmartPointer<vtkRenderer>::New();
   ren->SetBackground(1.0, 1.0, 1.0);
   ren->AddActor(actor);
   //ren->GetActiveCamera()->SetViewUp(0.0, -1.0, 0.0);
   //ren->ResetCamera();

vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(ren);
  renWin->SetSize(800, 450);

vtkSmartPointer<vtkRenderWindowInteractor> iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

renWin->Render();
renWin->MakeCurrent();

iren->SetRenderWindow(renWin);
iren->Initialize();
iren->Start();

return EXIT_SUCCESS;
}