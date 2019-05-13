#!/usr/bin/env python

import vtk


def get_program_parameters():
    import argparse
    description = 'Read a .obj file, .mtl file and texturepath'
    epilogue = '''
   '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue)
    parser.add_argument('filename_obj', help='filename_obj.obj')
    parser.add_argument('filename_mtl', help='filename_mtl.mtl')
    parser.add_argument('texturepath', help='')
    args = parser.parse_args()
    return args.filename_obj, args.filename_mtl, args.texturepath


def main():
    filename_obj, filename_mtl, texturepath = get_program_parameters()

    importer = vtk.vtkOBJImporter()
    importer.SetFileName(filename_obj)
    importer.SetFileNameMTL(filename_mtl)
    importer.SetTexturePath(texturepath)

    colors = vtk.vtkNamedColors()

    renderer = vtk.vtkRenderer()
    render_window = vtk.vtkRenderWindow()
    render_window_interactor = vtk.vtkRenderWindowInteractor()

    renderer.SetBackground2(colors.GetColor3d("Silver"))
    renderer.SetBackground(colors.GetColor3d("Gold"))
    renderer.GradientBackgroundOn()
    render_window.AddRenderer(renderer)
    renderer.UseHiddenLineRemovalOn()
    render_window.AddRenderer(renderer)
    render_window.SetSize(640, 480)

    render_window_interactor.SetRenderWindow(render_window)
    importer.SetRenderWindow(render_window)
    importer.Update()

    actors = vtk.vtkActorCollection()
    actors = renderer.GetActors()
    actors.InitTraversal()
    print("There are", actors.GetNumberOfItems(), "actors")

    for a in range(0, actors.GetNumberOfItems()):
        print(importer.GetOutputDescription(a))

        actor = actors.GetNextActor()

        # OBJImporter turns texture interpolation off
        if actor.GetTexture():
            print("Hastexture\n")
            actor.GetTexture().InterpolateOn()

        pd = actor.GetMapper().GetInput()
        clean = vtk.vtkCleanPolyData()
        clean.SetInputData(pd)
        clean.Update()

        normals = vtk.vtkPolyDataNormals()

        normals.SetInputData(pd)
        normals.SplittingOff()
        normals.ConsistencyOn()
        normals.Update()
        mapper = actor.GetMapper()
        mapper.SetInputData(normals.GetOutput())
        mapper.SetInputData(pd)

    render_window.Render()
    render_window_interactor.Start()


if __name__ == '__main__':
    main()
