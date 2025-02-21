#include <fstream>
#include <string>

int fileSize(std::string fileName) {
  std::fstream file(fileName);

  int lineCounter = 0;
  std::string output;

  while (getline(file, output)) {
    lineCounter++;
  };

  file.close();

  return lineCounter;
}