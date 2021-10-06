#include <iostream>

#include "CinderCellEditor.h"


int main(int argc, char *argv[]) // Don't forget first integral argument 'argc'
{
  std::string exeName = argv[0]; // Name of the current exec program
  std::vector<std::string> args;

  if (argc > 1) {
    args.assign(argv + 1, argv + argc);
  }


  CinderCellEditor cce;

  std::cout << args[0];
  cce.view(args[0]);

  return cce.exec();
}
