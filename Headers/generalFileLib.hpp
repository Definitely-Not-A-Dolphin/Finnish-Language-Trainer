#include <fstream>
#include <iostream>
#include <string>
#include "trimWhiteSpace.hpp"

int countLines(std::string fileName) {

  std::fstream file(fileName);

  int lineCounter = 0;
  std::string output;

  while (getline(file, output)) {
    lineCounter++;
  };

  file.close();

  return lineCounter;
}

struct _fstream : std::fstream {
  using std::fstream::fstream;

  void seekLine(int k) {
    if (!is_open()) {
      std::cerr << "File is not open!" << std::endl;
      return;
    };

    seekg(0);

    std::string line;
    for (int currentLine = 1; currentLine < k; currentLine++) {
      std::getline(*this, line);
    };
  };
};

struct csv_fstream : _fstream {
  using _fstream::_fstream;

  void seekElement(int row, int column) {
    seekLine(row);

    char c;
    std::string output;

    for (int k = 1; k < column; k++) {
      std::getline(*this, output, ',');
    };
  };

  std::string getElement(int row, int column) {

    seekElement(row, column);

    std::string output;

    std::getline(*this, output, ',');

    output = trimWhiteSpace(output);

    return output;
  };
};
