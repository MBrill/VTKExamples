# -*- coding: utf-8 -*-
"""
Parametrisierung der Helix
Dieser Python-Code wird als Programmable Source
in Paraview geladen und ausgeführt.

Anschließend kann noch ein Tube-Filter und andere
geometrische Objekte erzeugt werden, wie zum Beispiel
der Zylindermantel als visualisierung für die Helix.
"""
import numpy as np


def helix(a=0.0, b=1.0, radius=1.0, h=1.0, num=200):
    t = np.linspace(a, b, num)
    x = radius * np.cos(2.0 * np.pi * t)
    y = radius * np.sin(2.0 * np.pi * t)
    z = h * t
    return x, y, z


# Anzahl der Punkte
num = 200
# Rechter Punkt des Parameterintervalls
a = 0.0
# Linker Punkt Parameterintervally
b = 1.0
# Ganghöhe der Helix
h = 1.0
# Radius der Helix
radius = 1.0

# Eine Instaz von vtkPolyData erzeugen für die Ausgabe
pdo = self.GetPolyDataOutput()

# Wir erzeugen die Geometrie der Spur in einer Instanz von vtkPoints
newPts = vtk.vtkPoints()
newPts.SetNumberOfPoints(num)
x, y, z = helix(a, b, radius, h, num)
for i in range(0, num):
    newPts.InsertPoint(i, x[i], y[i], z[i])

# Punkte in die Instanz von vtkPolyData einfügen
pdo.SetPoints(newPts)

# Wir erzeugen eine vtkPolyLine als Topologie
aPolyLine = vtk.vtkPolyLine()
aPolyLine.GetPointIds().SetNumberOfIds(num)
for i in range(0,num):
    aPolyLine.GetPointIds().SetId(i, i)

# Die Information über die cells anlegen;
# Wir fügen eine Cell, die Polyline, hinzu
pdo.Allocate(1, 1)
pdo.InsertNextCell(aPolyLine.GetCellType(), aPolyLine.GetPointIds())

# Nicht vergessen Apply in ParaView zu betätigen!
