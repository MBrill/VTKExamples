# -*- coding: utf-8 -*-
import vtk


def create_arrow(pd_length, start_point, end_point):
    # Create an arrow.
    arrow_source = vtk.vtkArrowSource()
    arrow_source.SetShaftRadius(pd_length * 0.01)
    arrow_source.SetShaftResolution(20)
    arrow_source.SetTipLength(pd_length * 0.1)
    arrow_source.SetTipRadius(pd_length * 0.05)
    arrow_source.SetTipResolution(20)

    # Compute a basis
    normalized_x = [0.0, 0.0, 0.0]
    normalized_y = [0.0, 0.0, 0.0]
    normalized_z = [0.0, 0.0, 0.0]

    # The X axis is a vector from start to end
    vtk.vtkMath.Subtract(end_point, start_point, normalized_x)
    length = vtk.vtkMath.Norm(normalized_x)
    vtk.vtkMath.Normalize(normalized_x)

    # The Z axis is an arbitrary vector cross X
    rng = vtk.vtkMinimalStandardRandomSequence()
    rng.SetSeed(8775070)  # For testing.

    arbitrary = [0.0, 0.0, 0.0]

    for i in range(0, 3):
        rng.Next()
        arbitrary[i] = rng.GetRangeValue(-10, 10)

    vtk.vtkMath.Cross(normalized_x, arbitrary, normalized_z)
    vtk.vtkMath.Normalize(normalized_z)

    # The Y axis is Z cross X
    vtk.vtkMath.Cross(normalized_z, normalized_x, normalized_y)
    matrix = vtk.vtkMatrix4x4()

    # Create the direction cosine matrix
    matrix.Identity()

    for i in range(0, 3):
        matrix.SetElement(i, 0, normalized_x[i])
        matrix.SetElement(i, 1, normalized_y[i])
        matrix.SetElement(i, 2, normalized_z[i])

    # Apply the transforms
    transform = vtk.vtkTransform()
    transform.Translate(start_point)
    transform.Concatenate(matrix)
    transform.Scale(length, length, length)

    # Transform the poly_data
    transform_pd = vtk.vtkTransformPolyDataFilter()
    transform_pd.SetTransform(transform)
    transform_pd.SetInputConnection(arrow_source.GetOutputPort())
    transform_pd.Update()
    poly_data = transform_pd.GetOutput()

    return poly_data


def main():
    colors = vtk.vtkNamedColors()

    background_color = colors.GetColor3d("SlateGray")
    legend_background_color = colors.GetColor3d("Black")
    origin_color = colors.GetColor3d("Tomato")
    center_color = colors.GetColor3d("Banana")
    point1_color = colors.GetColor3d("Peru")
    point2_color = colors.GetColor3d("Bisque")
    x_axis_color = colors.GetColor3d("lime")
    y_axis_color = colors.GetColor3d("orange")
    normal_color = colors.GetColor3d("Raspberry")

    # Create actors
    plane_source = vtk.vtkPlaneSource()
    plane_source.SetOrigin(0.0, 0.0, 0.0)
    plane_source.SetPoint1(1, 0, 0)
    plane_source.SetPoint2(0, 1.0, 0)
    plane_source.Update()

    bounds = [0.0, 0.0, 0.0, 0.0, 0.0, 0.0]
    plane_source.GetOutput().GetBounds(bounds)

    length = max(bounds[1] - bounds[0], bounds[3] - bounds[2])

    plane_mapper = vtk.vtkPolyDataMapper()
    plane_mapper.SetInputConnection(plane_source.GetOutputPort())
    plane_actor = vtk.vtkActor()
    plane_actor.SetMapper(plane_mapper)

    sphere_source = vtk.vtkSphereSource()
    sphere_source.SetRadius(length * .04)
    origin_mapper = vtk.vtkPolyDataMapper()
    origin_mapper.SetInputConnection(sphere_source.GetOutputPort())
    origin_actor = vtk.vtkActor()
    origin_actor.SetPosition(plane_source.GetOrigin())
    origin_actor.SetMapper(origin_mapper)
    origin_actor.GetProperty().SetDiffuseColor(origin_color)

    center_mapper = vtk.vtkPolyDataMapper()
    center_mapper.SetInputConnection(sphere_source.GetOutputPort())
    center_actor = vtk.vtkActor()
    center_actor.SetPosition(plane_source.GetCenter())
    center_actor.SetMapper(center_mapper)
    center_actor.GetProperty().SetDiffuseColor(center_color)

    point1_mapper = vtk. vtkPolyDataMapper()
    point1_mapper.SetInputConnection(sphere_source.GetOutputPort())
    point1_actor = vtk.vtkActor()
    point1_actor.SetPosition(plane_source.GetPoint1())
    point1_actor.SetMapper(point1_mapper)
    point1_actor.GetProperty().SetDiffuseColor(point1_color)

    point2_mapper = vtk.vtkPolyDataMapper()
    point2_mapper.SetInputConnection(sphere_source.GetOutputPort())
    point2_actor = vtk.vtkActor()
    point2_actor.SetPosition(plane_source.GetPoint2())
    point2_actor.SetMapper(point2_mapper)
    point2_actor.GetProperty().SetDiffuseColor(point2_color)

    center = [0.0, 0.0, 0.0]
    origin = [0.0, 0.0, 0.0]
    normal = [0.0, 0.0, 0.0]
    point1 = [0.0, 0.0, 0.0]
    point2 = [0.0, 0.0, 0.0]

    for i in range(0, 3):
        point1[i] = plane_source.GetPoint1()[i]
        point2[i] = plane_source.GetPoint2()[i]
        origin[i] = plane_source.GetOrigin()[i]
        center[i] = plane_source.GetCenter()[i]
        normal[i] = plane_source.GetNormal()[i] * length

    x_axis_poly_data = create_arrow(length, origin, point1)
    x_axis_mapper = vtk.vtkPolyDataMapper()
    x_axis_mapper.SetInputData(x_axis_poly_data)
    x_axis_actor = vtk.vtkActor()
    x_axis_actor.SetMapper(x_axis_mapper)
    x_axis_actor.GetProperty().SetDiffuseColor(x_axis_color)

    y_axis_poly_data = create_arrow(length, origin, point2)
    y_axis_mapper = vtk.vtkPolyDataMapper()
    y_axis_mapper.SetInputData(y_axis_poly_data)
    y_axis_actor = vtk.vtkActor()
    y_axis_actor.SetMapper(y_axis_mapper)
    y_axis_actor.GetProperty().SetDiffuseColor(y_axis_color)

    normal_poly_data = create_arrow(length, origin, normal)
    normal_mapper = vtk.vtkPolyDataMapper()
    normal_mapper.SetInputData(normal_poly_data)
    normal_actor = vtk.vtkActor()
    normal_actor.SetMapper(normal_mapper)
    normal_actor.GetProperty().SetDiffuseColor(normal_color)

    # Create the render_window, Renderer
    renderer = vtk.vtkRenderer()

    legend = vtk.vtkLegendBoxActor()
    legend.SetNumberOfEntries(7)
    legend.UseBackgroundOn()
    legend.SetBackgroundColor(legend_background_color)
    legend.GetPositionCoordinate().SetValue(.7, .7)
    legend.GetPosition2Coordinate().SetValue(.3, .3)

    entry = 0
    legend.SetEntry(entry, sphere_source.GetOutput(), "center", center_color)
    entry += 1
    legend.SetEntry(entry, sphere_source.GetOutput(), "origin", origin_color)
    entry += 1
    legend.SetEntry(entry, sphere_source.GetOutput(), "point1", point1_color)
    entry += 1
    legend.SetEntry(entry, sphere_source.GetOutput(), "point2", point2_color)
    entry += 1
    legend.SetEntry(entry, x_axis_poly_data, "xAxis", x_axis_color)
    entry += 1
    legend.SetEntry(entry, x_axis_poly_data, "yAxis", y_axis_color)
    entry += 1
    legend.SetEntry(entry, x_axis_poly_data, "normal", normal_color)
    entry += 1

    render_window = vtk.vtkRenderWindow()
    render_window.AddRenderer(renderer)
    render_window.SetSize(640, 480)

    interactor = vtk.vtkRenderWindowInteractor()
    interactor.SetRenderWindow(render_window)

    renderer.SetBackground(background_color)
    renderer.AddActor(plane_actor)
    renderer.AddActor(origin_actor)
    renderer.AddActor(center_actor)
    renderer.AddActor(point1_actor)
    renderer.AddActor(point2_actor)
    renderer.AddActor(x_axis_actor)
    renderer.AddActor(y_axis_actor)
    renderer.AddActor(normal_actor)
    renderer.AddActor(legend)

    render_window.Render()
    renderer.GetActiveCamera().SetPosition(1, 0, 0)
    renderer.GetActiveCamera().SetFocalPoint(0, 1, 0)
    renderer.GetActiveCamera().SetViewUp(0, 0, 1)
    renderer.GetActiveCamera().Azimuth(30)
    renderer.GetActiveCamera().Elevation(30)
    renderer.ResetCamera()
    render_window.Render()
    interactor.Start()


if __name__ == '__main__':
    main()
