#include <fstream>
#include <string>

void seekLine(std::fstream &file, int k) {
  file.seekg(std::ios::beg);

  std::string line;
  for (int currentLine = 1; currentLine < k; currentLine++) {
    getline(file, line);
  };
}

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