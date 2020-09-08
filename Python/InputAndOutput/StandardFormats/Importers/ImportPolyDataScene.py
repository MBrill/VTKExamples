#!/usr/bin/env python

import vtk


def get_program_parameters():
    import argparse
    description = 'Read a .jpeg image file'
    epilogue = '''
   '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue)
    parser.add_argument('filename', help='clouds.jpeg')
    args = parser.parse_args()
    return args.filename


def main():
    filename = get_program_parameters()

    # Visualization
    colors = vtk.tkNamedColors()
    
    renderer = vtk.vtkRenderer()
    
    renderWindow = vtk.vtkRenderWindow()
    renderWindow.AddRenderer(renderer);

    renderWindowInteractor =vtk.vtkRenderWindowInteractor()
    renderWindowInteractor.SetRenderWindow(renderWindow);

    ImportMultiBlockScene(renderer.GetPointer(), filename);
    renderWindow.Render();

    renderer.SetBackground(colors.GetColor3d("Silver"));

    renderWindow.SetSize(640, 480);
    renderWindow.Render();
    renderWindowInteractor.Start();

ImportMultiBlockScene(renderer, fileName):

    amera = renderer.GetActiveCamera();

    prefix = vtk.vtksys.SystemTools.GetFilenameName(fileName);

// Read
the
multiblock
data
auto
reader = vtkSmartPointer < vtkXMLMultiBlockDataReader >::New();
vtkSmartPointer < vtkXMLMultiBlockDataReader >::New();
reader.SetFileName(fileName.c_str());
reader.Update();
std::cout << "Importing "
     << dynamic_cast < vtkMultiBlockDataSet * > (reader.GetOutput()).GetNumberOfBlocks()
                                                                       << " actors" << std::endl;

# if VTK890
vtkDataObjectTree * input =
dynamic_cast < vtkDataObjectTree * > (reader.GetOutput());

using
Opts = vtk::DataObjectTreeOptions;
for (vtkDataObject * dso :
vtk::Range(input, Opts::SkipEmptyNodes | Opts::VisitOnlyLeaves))
{
    vtkPolyData * pd = dynamic_cast < vtkPolyData * > (dso);
RestoreCameraFromFieldData("Camera", camera, pd);
auto
mapper = vtkSmartPointer < vtkPolyDataMapper >::New();
mapper.SetInputData(pd);

auto
actor = vtkSmartPointer < vtkActor >::New();
actor.SetMapper(mapper);
RestorePropertyFromFieldData("Property", actor.GetProperty(), pd);
auto
backProperty = vtkSmartPointer < vtkProperty >::New();
actor.SetBackfaceProperty(backProperty);
RestorePropertyFromFieldData("BackfaceProperty",
                             actor.GetBackfaceProperty(), pd);
RestoreActorFromFieldData("Actor", actor, pd);
renderer.AddActor(actor);
}
# else
vtkCompositeDataSet * input =
dynamic_cast < vtkCompositeDataSet * > (reader.GetOutput());

auto
iter = vtkSmartPointer < vtkDataObjectTreeIterator >::New();
iter.SetDataSet(input);
iter.SkipEmptyNodesOn();
iter.VisitOnlyLeavesOn();
for (iter.InitTraversal(); !iter.IsDoneWithTraversal();
iter.GoToNextItem())
{
    vtkDataObject * dso = iter.GetCurrentDataObject();
vtkPolyData * pd = dynamic_cast < vtkPolyData * > (dso);
RestoreCameraFromFieldData("Camera", camera, pd);
auto
mapper = vtkSmartPointer < vtkPolyDataMapper >::New();
mapper.SetInputData(pd);

auto
actor = vtkSmartPointer < vtkActor >::New();
actor.SetMapper(mapper);
RestorePropertyFromFieldData("Property", actor.GetProperty(), pd);
auto
backProperty = vtkSmartPointer < vtkProperty >::New();
actor.SetBackfaceProperty(backProperty);
RestorePropertyFromFieldData("BackfaceProperty",
                             actor.GetBackfaceProperty(), pd);
RestoreActorFromFieldData("Actor", actor, pd);
renderer.AddActor(actor);
}
# endif
}
void
RestoreCameraFromFieldData(std::string
arrayPrefix, vtkCamera * camera,
vtkPolyData * pd)
{
    vtkFieldData * fd = pd.GetFieldData();
camera.SetFocalPoint(
    fd.GetArray(std::string(arrayPrefix + ":" + "FocalPoint").c_str())
.GetTuple(0));
camera.SetPosition(
    fd.GetArray(std::string(arrayPrefix + ":" + "Position").c_str())
.GetTuple(0));
camera.SetViewUp(
    fd.GetArray(std::string(arrayPrefix + ":" + "ViewUp").c_str())
.GetTuple(0));
camera.SetClippingRange(
    fd.GetArray(std::string(arrayPrefix + ":" + "ClippingRange").c_str())
.GetTuple(0));
camera.SetViewAngle(
    fd.GetArray(std::string(arrayPrefix + ":" + "ViewAngle").c_str())
.GetTuple1(0));
}
void
RestorePropertyFromFieldData(std::string
arrayPrefix,
vtkProperty * property, vtkPolyData * pd)
{
if (property)
{
    vtkFieldData * fd = pd.GetFieldData();

property.SetAmbient(
    fd.GetArray(std::string(arrayPrefix + ":" + "Ambient").c_str())
.GetTuple1(0));
property.SetAmbientColor(
    fd.GetArray(std::string(arrayPrefix + ":" + "AmbientColor").c_str())
.GetTuple(0));
property.SetAmbientColor(
    fd.GetArray(std::string(arrayPrefix + ":" + "AmbientColor").c_str())
.GetTuple(0));
property.SetDiffuse(
    fd.GetArray(std::string(arrayPrefix + ":" + "Diffuse").c_str())
.GetTuple1(0));
property.SetDiffuseColor(
    fd.GetArray(std::string(arrayPrefix + ":" + "DiffuseColor").c_str())
.GetTuple(0));
property.SetSpecular(
    fd.GetArray(std::string(arrayPrefix + ":" + "Specular").c_str())
.GetTuple1(0));
property.SetSpecularColor(
    fd.GetArray(std::string(arrayPrefix + ":" + "SpecularColor").c_str())
.GetTuple(0));
property.SetSpecularPower(
    fd.GetArray(std::string(arrayPrefix + ":" + "SpecularPower").c_str())
.GetTuple1(0));
property.SetEdgeColor(
    fd.GetArray(std::string(arrayPrefix + ":" + "EdgeColor").c_str())
.GetTuple(0));
property.SetEdgeVisibility(
    fd.GetArray(std::string(arrayPrefix + ":" + "EdgeVisibility").c_str())
.GetTuple1(0));
property.SetVertexColor(
    fd.GetArray(std::string(arrayPrefix + ":" + "VertexColor").c_str())
.GetTuple(0));
property.SetVertexVisibility(
    fd.GetArray(
    std::string(arrayPrefix + ":" + "VertexVisibility").c_str())
.GetTuple1(0));
property.SetInterpolation(
    fd.GetArray(std::string(arrayPrefix + ":" + "Interpolation").c_str())
.GetTuple1(0));
property.SetOpacity(
    fd.GetArray(std::string(arrayPrefix + ":" + "Opacity").c_str())
.GetTuple1(0));
property.SetRepresentation(
    fd.GetArray(std::string(arrayPrefix + ":" + "Representation").c_str())
.GetTuple1(0));
property.SetBackfaceCulling(
    fd.GetArray(std::string(arrayPrefix + ":" + "BackfaceCulling").c_str())
.GetTuple1(0));
property.SetFrontfaceCulling(
    fd.GetArray(
    std::string(arrayPrefix + ":" + "FrontfaceCulling").c_str())
.GetTuple1(0));
property.SetPointSize(
    fd.GetArray(std::string(arrayPrefix + ":" + "PointSize").c_str())
.GetTuple1(0));
property.SetLineWidth(
    fd.GetArray(std::string(arrayPrefix + ":" + "LineWidth").c_str())
.GetTuple1(0));
property.SetLineStipplePattern(
    fd.GetArray(
    std::string(arrayPrefix + ":" + "LineStipplePattern").c_str())
.GetTuple1(0));
property.SetLineStippleRepeatFactor(
    fd.GetArray(std::string(arrayPrefix + ":" + "LineStippleRepeatFactor")
    .c_str())
.GetTuple1(0));
property.SetLighting(
    fd.GetArray(std::string(arrayPrefix + ":" + "Lighting").c_str())
.GetTuple1(0) == 1.0
? true
: false);
property.SetRenderPointsAsSpheres(
    fd.GetArray(
    std::string(arrayPrefix + ":" + "RenderPointsAsSpheres").c_str())
.GetTuple1(0) == 1.0
? true
: false);
property.SetRenderLinesAsTubes(
    fd.GetArray(
    std::string(arrayPrefix + ":" + "RenderLinesAsTubes").c_str())
.GetTuple1(0) == 1.0
? true
: false);
property.SetShading(
    fd.GetArray(std::string(arrayPrefix + ":" + "Shading").c_str())
.GetTuple1(0) == 1.0
? true
: false);
}
}
void
RestoreActorFromFieldData(std::string
arrayPrefix, vtkActor * actor,
vtkPolyData * pd)
{
    vtkFieldData * fd = pd.GetFieldData();

actor.SetDragable(
    fd.GetArray(std::string(arrayPrefix + ":" + "Dragable").c_str())
.GetTuple1(0) == 1.0
? true
: false);
actor.SetPickable(
    fd.GetArray(std::string(arrayPrefix + ":" + "Pickable").c_str())
.GetTuple1(0) == 1.0
? true
: false);
actor.SetVisibility(
    fd.GetArray(std::string(arrayPrefix + ":" + "Visibility").c_str())
.GetTuple1(0));
actor.SetPosition(
    fd.GetArray(std::string(arrayPrefix + ":" + "Position").c_str())
.GetTuple(0));
actor.SetOrientation(
    fd.GetArray(std::string(arrayPrefix + ":" + "Orientation").c_str())
.GetTuple(0));
actor.SetOrigin(
    fd.GetArray(std::string(arrayPrefix + ":" + "Origin").c_str())
.GetTuple(0));
actor.SetScale(fd.GetArray(std::string(arrayPrefix + ":" + "Scale").c_str())
.GetTuple(0));
actor.SetForceOpaque(
    fd.GetArray(std::string(arrayPrefix + ":" + "ForceOpaque").c_str())
.GetTuple1(0) == 1.0
? true
: false);
actor.SetForceTranslucent(
    fd.GetArray(std::string(arrayPrefix + ":" + "ForceTranslucent").c_str())
.GetTuple1(0) == 1.0
? true
: false);
}
} // namespace


if __name__ == '__main__':
    main()
