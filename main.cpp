#include <iostream>

#include "CinderCellEditor.h"


int main(int argc, char *argv[])
{
  std::string exeName = argv[0];
  std::vector<std::string> args;

  if (argc > 1) {
    args.assign(argv + 1, argv + argc);
  }


  CinderCellEditor cce;

  cce.view(args[0]);

  return cce.exec();
}
