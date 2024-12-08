#include <fstream>
#include <iostream>
#include <string>

std::ifstream readEngFin("wordsEngFin.txt");

void pointerMover(int line);

int main() {

  std::string wordEng;
  getline(readEngFin, wordEng, '|');

  std::string wordFin;
  getline(readEngFin, wordFin, '|');

  std::string wordFinInput;
  std::cout << "What is the Finnish word for " << wordEng << "? ";
  std::cin >> wordFinInput;

  if (wordFinInput == wordFin) {
    std::cout << "Good Job!" << std::endl;
  } else {
    std::cout << "No :(" << std::endl;
  };

  return 0; 
}

void pointerMover(int k) {

  int currentLine = 0;

  std::string line;

  while (std::getline(readEngFin, line, '\n')) {
    currentLine++;
    if (currentLine == k) {
      break;
    }
  }
}