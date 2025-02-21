#include "seekLine.cpp"
#include <fstream>
#include <string>

void seekElement(std::fstream &file, int row, int column) {
  seekLine(file, row);

  std::string output;

  for (int k = 1; k < column; k++) {
    getline(file, output, ',');
  };
}