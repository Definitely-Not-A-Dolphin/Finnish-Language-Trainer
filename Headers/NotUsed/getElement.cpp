#include "seekElement.cpp"
#include "trimWhiteSpace.cpp"
#include <fstream>
#include <string>

std::string getElement(std::fstream &file, int row, int column) {

  seekElement(file, row, column);

  std::string output;
  std::getline(file, output, ',');
  output = trimWhiteSpace(output);
  return output;
}