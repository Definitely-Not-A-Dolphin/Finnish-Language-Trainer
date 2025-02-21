#include <fstream>
#include <string>

void seekLine(std::fstream &file, int k) {
  file.seekg(std::ios::beg);

  std::string line;
  for (int currentLine = 1; currentLine < k; currentLine++) {
    getline(file, line);
  };
}