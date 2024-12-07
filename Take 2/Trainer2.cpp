#include <fstream>
#include <iostream>

std::ifstream readEngFin("wordsEngFin.txt");

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