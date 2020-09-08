//! example for the usage of class Compute
#include <iostream>
#include "Compute.h"

int main(void)
{
  long a=40, b=2;
  std::cout << "------------------" << std::endl;
  std::cout << "computing a+b" << std::endl;
  std::cout << "------------------" << std::endl;

  Compute hitchHiker(a, b);
  std::cout << "the sum of " << a << " and " << b << " is " << hitchHiker.compute() << std::endl;
  std::cout << "Bye Bye" << std::endl;
  return 0;
}

/*!
 * \mainpage 
 * If you want text on the index.html, put it in a file and use \\mainpage!
 */

/*! \example main
 * If you want text for a specific example, put it a file and use \\example
 */
