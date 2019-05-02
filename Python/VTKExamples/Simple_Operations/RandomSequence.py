#!/usr/bin/env python

import vtk
import time


def main():
    # Create a random sequence generator.
    sequence = vtk.vtkMinimalStandardRandomSequence()

    # initialize the sequence
    sequence.SetSeed(int(time.time()))

    # Get 3 random numbers.
    x = sequence.GetValue()
    sequence.Next()
    y = sequence.GetValue()
    sequence.Next()
    z = sequence.GetValue()

    # You can also use seq.GetRangeValue(-1.0, 1.0)
    # to set a range on the random values.

    # Output the resulting random numbersl
    print("x:", x, "y:", y, "z:", z)


if __name__ == '__main__':
    main()
