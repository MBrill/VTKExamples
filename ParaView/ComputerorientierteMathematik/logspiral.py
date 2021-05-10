# -*- coding: utf-8 -*-
"""
Parametrisierung der logarithmischen Spirale.

Dieser Python-Code wird als Programmable Source
in Paraview geladen und ausgeführt.
"""
import numpy as np


def logSpiralHelix(a=2.0, b=0.08, h=1.0, l=0.0, r=8.0*np.pi, n=200):
    """
    Parametrisierung der Schraubenlinie über einer logarithmischen Spirale.

    Parameters
    ----------
    a : float
        Parameter a der logarithmischen Spirale. Default ist 1.0.
    b : float
        Parameter b der logarithmischen Spirale. Default ist 0.08.
    h : float
        Ganghöhe. Default ist 1.0.
    l : float
        Linke Grenze des Parameterintervalls. Default ist 0.0.
    r:  float
        Linke Grenze des Parameterintervalls. Default ist 6 pi.
    num: int
        Anzahl der Punkte für die Polyline. Default ist 200.

    Returns
    -------
    x : float
        x-Koordinate.
    y : float
        y-Koordinate.
    z : float
        z-Koordinate.
    """
    t = np.linspace(l, r, n)
    r = a * np.exp(b*t)
    x = r * np.cos(t)
    y = r * np.sin(t)
    z = h * t
    return x, y, z


num = 200
# Eine Instaz von vtkPolyData erzeugen für die Ausgabe
pdo = self.GetPolyDataOutput()

# Wir erzeugen die Geometrie der Spur in einer Instanz von vtkPoints
newPts = vtk.vtkPoints()
newPts.SetNumberOfPoints(num)
x, y, z = logSpiralHelix(n=num)
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
