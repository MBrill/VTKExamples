#include <vtkOpenVRInteractorStyle.h>
#include "vtkRenderingOpenVRModule.h"
#include "vtkOpenVRRenderWindow.h" // for enums
#include "vtkNew.h" // for ivars
#include "vtkEventData.h"
#include <vtkObjectFactory.h>
#include <iostream>
#include <vtkActor.h>
#include <vtkSmartPointer.h>
#include <vtkColor.h>

class TestInteractorStyle : public vtkOpenVRInteractorStyle
{
public:
  static TestInteractorStyle *New();
  vtkTypeMacro(TestInteractorStyle, vtkOpenVRInteractorStyle);

   virtual void OnButton3D(vtkEventData *edata) 
    {
	 //  edata->Print(std::cout);
	   vtkSmartPointer<vtkNamedColors> colors =
		   vtkSmartPointer<vtkNamedColors>::New();
	   myactor->GetProperty()->SetColor(colors->GetColor3d("green").GetData());
      // forward events
      vtkOpenVRInteractorStyle::OnButton3D(edata);
	  
    }
   void SetActor(vtkSmartPointer<vtkActor> actor) { this->myactor = actor; }

private:
	vtkSmartPointer<vtkActor> myactor;

};
vtkStandardNewMacro(TestInteractorStyle);