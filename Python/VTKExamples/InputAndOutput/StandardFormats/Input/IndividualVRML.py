#!/usr/bin/env python

import vtk


def get_program_parameters():
    import argparse
    description = 'Required arguments: Filename Actorname'
    epilogue = '''
   '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue)
    parser.add_argument('filename', help='')
    parser.add_argument('actorname', help='')
    args = parser.parse_args()
    return args.filename, args.actorname


def main():
    filename, actorname = get_program_parameters()
    print("Showing", actorname, "from", filename)

    renderer = vtk.vtkRenderer()
    render_window = vtk.vtkRenderWindow()
    render_window.AddRenderer(renderer)

    render_window_interactor = vtk.vtkRenderWindowInteractor()
    render_window_interactor.SetRenderWindow(render_window)

    # VRML Import
    importer = vtk.vtkVRMLImporter()
    importer.SetFileName(filename)
    importer.Read()
    importer.SetRenderWindow(render_window)
    importer.Update()

    # ----------------------------------------------------------
    def_actor = importer.GetVRMLDEFObject(actorname)
    if def_actor is None:
        print("Cannot locate actor", actorname, "in", filename)
        # importer.Print()

    actor = vtk.vtkActor(actorname)
    color = {0.89, 0.81, 0.34}
    actor.GetProperty().SetColor(color)
    actor.GetProperty().SetRepresentationToWireframe()

    transform = vtk.vtkTransform()

    transform.Translate(actor.GetCenter()[0],
                        actor.GetCenter()[1],
                        actor.GetCenter()[2])
    # axes
    axes = vtk.vtkAxesActor()

    l = [0.0, 0.0, 0.0]
    l[0] = (actor.GetBounds()[1] - actor.GetBounds()[0]) * 1.5
    l[1] = (actor.GetBounds()[3] - actor.GetBounds()[2]) * 1.5
    l[2] = (actor.GetBounds()[5] - actor.GetBounds()[4]) * 1.5

    axes.SetTotalLength(l)
    axes.SetUserTransform(transform)
    renderer.AddActor(axes)

    named_colors = vtk.vtkNamedColors()
    renderer.SetBackground(named_colors.GetColor3d("Azure"))

    render_window.Render()
    render_window_interactor.Start()


if __name__ == '__main__':
    main()
