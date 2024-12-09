#include <fstream>
#include <iostream>
#include <list>
#include <string>

std::ifstream readEngFin("wordsEngFin.txt");

void englishFinnish(bool IP);

void pointerMover(std::ifstream &file, int k);

bool listChecker(std::list<std::string> searchedList, std::string searchedWord);

int maxLine = 50;

bool infinitePractise;

int main() {


  while (true) {
    std::string answerIP;
    std::cout << "Do you want to infinite practise? ";
    std::cin >> answerIP;

    std::list<std::string> noList = {"no",  "No",  "nah", "Nah",
                                     "nei", "Nei", "nee", "Nee"};
    std::list<std::string> yesList = {"Yes", "yes", "Yeah", "yeah",
                                      "Yea", "yea", "Ye",   "ye"};

    if (listChecker(yesList, answerIP)) {
      infinitePractise = true;
      break;
    } else if (listChecker(noList, answerIP)) {
      infinitePractise = false;
      break;
    } else {
      std::cout << "Sorry, I could not understand that. Please re-enter your answer." << std::endl;
    }
  }
  
  englishFinnish(infinitePractise);

  return 0;
}

void englishFinnish(bool IP) {

  int i = 1;

  while (true) {

    pointerMover(readEngFin, i);

    std::string wordEng;
    getline(readEngFin, wordEng, '|');

    readEngFin.seekg(1, std::ifstream::cur);

    std::string wordFin;
    getline(readEngFin, wordFin, '|');

    std::string wordFinInput;
    std::cout << "What is the Finnish word for " << wordEng << "? ";
    std::cin >> wordFinInput;

    if (wordFinInput == wordFin) {
      std::cout << "Yes! :)" << std::endl;
    } else {
      std::cout << "No :(" << std::endl;
    };

    i = i + 1;

    if (IP = false) {
      break;
    } else {
      i = 1;
    }
  }
}

void pointerMover(std::ifstream &file, int k) {

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

bool listChecker(std::list<std::string> searchedList,
                 std::string searchedWord) {
  bool result = false;

  for (std::string comparer : searchedList) {
    if (comparer == searchedWord) {
      result = true;
    }
  };

  return result;
}