#include <vtkOpenVRInteractorStyle.h>
#include "vtkRenderingOpenVRModule.h"
#include "vtkOpenVRRenderWindow.h" // for enums
#include "vtkNew.h" // for ivars
#include "vtkEventData.h"
#include <vtkObjectFactory.h>
class TestInteractorStyle : public vtkOpenVRInteractorStyle
{
public:
  static TestInteractorStyle *New();
  vtkTypeMacro(TestInteractorStyle, vtkOpenVRInteractorStyle);

   virtual void OnPan() 
    {
      std::cout << "test" << std::endl;
      // forward events
      vtkOpenVRInteractorStyle::OnPan();
    }

};
vtkStandardNewMacro(TestInteractorStyle);