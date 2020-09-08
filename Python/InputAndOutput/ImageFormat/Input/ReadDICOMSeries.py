#!/usr/bin/env python

import vtk


def get_program_parameters():
    import argparse
    description = 'Read a DICOM image file'
    epilogue = '''
   '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue)
    parser.add_argument('filename', help='TestReadDICOMSeries_1.png')
    args = parser.parse_args()
    return args.filename


# helper class to format slice status message
class StatusMessage:
    @staticmethod
    def Format(slice, maxSlice):
        tmp = "Slice Number" + str(slice + 1) + "/" + str(maxSlice + 1)
        return tmp


# Define own interaction style


class myVtkInteractorStyleImage(vtk.vtkInteractorStyleImage):

    def __init__(self, imageViewer, mapper, iren):
        self._iren = iren
        self._ImageViewer = imageViewer
        self._MinSlice = imageViewer.GetSliceMin()
        self._MaxSlice = imageViewer.GetSliceMax()
        self._Slice = self._MinSlice
        self._StatusMapper = mapper
        print("Slicer: Min =", self._MinSlice, ", Max =", self._MaxSlice)

        iren.AddObserver("OnKeyDown", self.OnKeyDown)

    def start(self):
        print("a")
        self._iren.AddObserver("OnKeyDown", self.OnKeyDown)

        self._iren.AddObserver(
            "OnMouseWheelBackwards",
            self.OnMouseWheelBackward)

        self._iren.AddObserver(
            "OnMouseWheelForward",
            self.OnMouseWheelForward)

    def MoveSliceForward(self):
        if self._Slice < self._MaxSlice:
            self._Slice += 1
            print("MoveSliceForward::Slice =", self._Slice)
            self._ImageViewer.SetSlice(self._Slice)
            msg = StatusMessage.Format(self._Slice, self._MaxSlice)
            self._StatusMapper.SetInput(msg)
            self._ImageViewer.Render()

    def MoveSliceBackward(self):
        if self._Slice > self._MinSlice:
            self._Slice -= 1
            print("MoveSliceBackward::Slice =", self._Slice)
            self._ImageViewer.SetSlice(self._Slice)
            msg = StatusMessage.Format(self._Slice, self._MaxSlice)
            self._StatusMapperSetInput(msg)
            self._ImageViewer.Render()

    def OnKeyDown(self, obj, ev):
        print(self.OnKeyDown.key)
        if self.GetInteractionMode() is not None:
            key = self.GetInteractor().GetKeySym()
            print(key)
            if key == "w":
                print("Up arrow key was pressed.")
                self.MoveSliceForward()
            elif key == "Down":
                print("Down arrow key was pressed.")
                self.MoveSliceBackward()
            # forward event

    def OnMouseWheelForward(self, obj, ev):
        print("Scrolled mouse wheel forward.")
        # self.MoveSliceForward()
        # don't forward events, otherwise the image will be zoomed
        # in case another interactorstyle is used(e.g. trackballstyle, ...)
        # vtk.vtkInteractorStyleImage.OnMouseWheelForward()

    def OnMouseWheelBackward(self, obj, ev):
        print("Scrolled mouse wheel backward.")
        if self._Slice > self._MinSlice:
            self.MoveSliceBackward()
        # don't forward events, otherwise the image will be zoomed
        # in case another interactorstyle is used(e.g. trackballstyle, ...)
        # vtk.vtkInteractorStyleImage.OnMouseWheelBackward()


def main():
    folder = get_program_parameters()

    # Read all the DICOM files in the specified directory.
    reader = vtk.vtkDICOMImageReader()

    reader.SetDirectoryName(folder)
    reader.Update()

    # Visualize
    imageViewer = vtk.vtkImageViewer2()
    imageViewer.SetInputConnection(reader.GetOutputPort())

    # slice status message
    sliceTextProp = vtk.vtkTextProperty()
    sliceTextProp.SetFontFamilyToCourier()
    sliceTextProp.SetFontSize(20)
    sliceTextProp.SetVerticalJustificationToBottom()
    sliceTextProp.SetJustificationToLeft()

    sliceTextMapper = vtk.vtkTextMapper()
    msg = StatusMessage.Format(
        imageViewer.GetSliceMin(),
        imageViewer.GetSliceMax())
    sliceTextMapper.SetInput(msg)
    sliceTextMapper.SetTextProperty(sliceTextProp)

    sliceTextActor = vtk.vtkActor2D()
    sliceTextActor.SetMapper(sliceTextMapper)
    sliceTextActor.SetPosition(15, 10)

    # usage hint message
    usageTextProp = vtk.vtkTextProperty()
    usageTextProp.SetFontFamilyToCourier()
    usageTextProp.SetFontSize(20)
    usageTextProp.SetVerticalJustificationToTop()
    usageTextProp.SetJustificationToLeft()

    usageTextMapper = vtk.vtkTextMapper()
    usageTextMapper.SetInput(
        "- Slice with mouse wheel\n  or Up/Down-Key\n- Zoom with pressed right\n  mouse button while dragging")
    usageTextMapper.SetTextProperty(usageTextProp)

    usageTextActor = vtk.vtkActor2D()
    usageTextActor.SetMapper(usageTextMapper)
    usageTextActor.GetPositionCoordinate().SetCoordinateSystemToNormalizedDisplay()
    usageTextActor.GetPositionCoordinate().SetValue(0.05, 0.95)

    # create an interactor with our own style (inherit from vtkInteractorStyleImage)
    # in order to catch mousewheel and key events
    renderWindowInteractor = vtk.vtkRenderWindowInteractor()

    myInteractorStyle = myVtkInteractorStyleImage(
        imageViewer, sliceTextMapper, renderWindowInteractor)

    # make imageviewer2 and sliceTextMapper visible to our interactorstyle
    # to enable slice status message updates when scrolling through the slices

    imageViewer.SetupInteractor(renderWindowInteractor)

    myInteractorStyle.start()
    # make the interactor use our own interactorstyle
    # cause SetupInteractor() is defining it's own default interatorstyle
    # this must be called after SetupInteractor()
    renderWindowInteractor.SetInteractorStyle(myInteractorStyle)
    # add slice status message and usage hint message to the renderer
    imageViewer.GetRenderer().AddActor2D(sliceTextActor)
    imageViewer.GetRenderer().AddActor2D(usageTextActor)

    # initialize rendering and interaction
    imageViewer.GetRenderWindow().SetSize(400, 300)
    imageViewer.GetRenderer().SetBackground(0.2, 0.3, 0.4)
    imageViewer.Render()
    imageViewer.GetRenderer().ResetCamera()
    imageViewer.Render()
    renderWindowInteractor.Start()


if __name__ == '__main__':
    main()
