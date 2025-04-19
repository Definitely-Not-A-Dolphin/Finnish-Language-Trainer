#include "generalFileStream.hpp"
#include "trimWhiteSpace.hpp"
#include <fstream>
#include <string>

void seekElement(std::fstream &file, int row, int column) {
  seekLine(file, row);

  std::string output;

  for (int k = 1; k < column; k++) {
    getline(file, output, ',');
  };
}

std::string getElement(std::fstream &file, int row, int column) {

  seekElement(file, row, column);

  std::string output;
  std::getline(file, output, ',');
  output = trimWhiteSpace(output);
  return output;
}