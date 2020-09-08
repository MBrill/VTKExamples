#!/usr/bin/env python

import vtk
import time


def main():
    # Set the number of random numbers we wish to produce to 3.
    num_rand = 3

    # Without this line, the random numbers will be the same every iteration.
    vtk.vtkMath.RandomSeed(int(time.time()))

    # Generate numRand random numbers from a uniform distribution between 0.0
    # and 2.0
    for i in range(0, num_rand):
        a = vtk.vtkMath.Random(0.0, 2.0)
        print(a)


if __name__ == '__main__':
    main()
