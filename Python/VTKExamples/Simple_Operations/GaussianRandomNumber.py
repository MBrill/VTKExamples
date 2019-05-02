#!/usr/bin/env python

import vtk
import time


def main():
    # The number of random numbers we wish to produce unsigned
    num_rand = 3

    # without this line, the random numbers will be the same every iteration
    vtk.vtkMath.RandomSeed(int(time.time()))

    # Generate numRand random numbers from a Gaussian distribution with mean
    # 0.0 and standard deviation 2.0
    for i in range(0, num_rand):
        a = vtk.vtkMath.Gaussian(0.0, 2.0)
        print(a)


if __name__ == '__main__':
    main()
