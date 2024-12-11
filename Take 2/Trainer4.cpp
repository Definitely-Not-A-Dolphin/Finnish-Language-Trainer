#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

std::string getElement(std::ifstream &file, int row, int column);

void pointerMover(std::ifstream &file, int k);

std::string getEng(std::ifstream &file, int line);

std::string getFin(std::ifstream &file, int line, int finCase);

int main() {

  std::cout << "Yep, this runs!" << std::endl;

  //Open File
  std::ifstream readFile("nounsFile.csv", std::ios::in);
  std::ifstream readFile("nounsFile.csv");
  std::cout << getFin(readFile, 3, 1);

  readFile.close();

  return 0;
}

std::string getEng(std::ifstream readFile, int line) {

  std::string wordFin = getElement(readFile, line, 1);

  return wordFin;
}

std::string getFin(std::ifstream readFile, int line, int finCase) {

  std::string wordFin = getElement(readFile, line, finCase + 1);

  return wordFin;
}

std::string getElement(std::ifstream &file, int row, int column) {
  pointerMover(file, row);

  std::string output;
  getline(file, output);

  std::string tmp; // A string to store the word on each iteration.
  std::stringstream str_strm(output);
  std::vector<std::string> wordsVector; // Create vector to hold our words
  while (str_strm >> tmp) {
    tmp.pop_back();
    wordsVector.push_back(tmp);
  }

  return wordsVector.at(column - 1);
}

void pointerMover(std::ifstream &file, int k) {

  // Special thanks to Elses/Menium for writing this part!

  file.clear();
  file.seekg(0, std::ios::beg);

  std::string line;
  for (int currentLine = 1; currentLine < k; currentLine++) {
    if (!std::getline(file, line)) {
      std::cerr << "Error: Line " << k << " does not exist!" << std::endl;
      return;
    }
  }
}