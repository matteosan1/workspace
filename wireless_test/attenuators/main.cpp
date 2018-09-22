#include "moxa.h"
#include "oring.h"

#include <string>
#include <iostream>

int main()
{
  std::string choice;
  std::cout << "MOXA or ORING ? (M/O) :";
  std::cin >> choice;

  if (choice == "M") {
    std::cout << "Running test for MOXA..." << std::endl;
    testMOXA();
  }
  else if (choice == "O") {
    std::cout << "Running test for ORING..." << std::endl;
    testOring();
  }
  else {
    std::cout << "Unknown device" << std::endl;
  }
      
  return 0;
}
  
