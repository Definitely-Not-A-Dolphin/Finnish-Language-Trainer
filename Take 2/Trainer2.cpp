#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <vector>

void englishFinnish();
void pointerMover(std::ifstream &file, int k);
bool listChecker(std::list<std::string> searchedList, std::string searchedWord);
void getEngFin(int k);

std::ifstream readEngFin("wordsEngFin.txt");

int wordsTrained;
int maxLine = 50;
bool infinitePractise;
bool randomPractise;
std::list<std::string> noList = {"no",  "No",  "nah", "Nah",
                                 "nei", "Nei", "nee", "Nee"};
std::list<std::string> yesList = {"Yes", "yes", "Yeah", "yeah",
                                  "Yea", "yea", "Ye",   "ye"};

int main() {

  std::cout << "How many words do you want to practise (the current list contains " << maxLine << " words)? ";
  std::cin >> wordsTrained;

  while (true) {
    std::string answerRandom;
    std::cout << "Do you want to randomise the words? ";
    std::cin >> answerRandom;

    if (listChecker(yesList, answerRandom)) {
      randomPractise = true;
      break;
    } else if (listChecker(noList, answerRandom)) {
      randomPractise = false;
      break;
    } else {
      std::cout
          << std::endl
          << "Sorry, I could not understand that. Please re-enter your answer."
          << std::endl;
    }
  }

  englishFinnish();

  return 0;
}

void englishFinnish() {

  int counter = 0;

  int i = 1;

  if (randomPractise) {
    while (true) {

      //Get random sequence n
      std::vector<int> randomSequence;

      getEngFin(randomSequence.at(0));

      counter = counter + 1;

      if (i > maxLine) {
        if (infinitePractise = false) {
          break;
        } else {
          i = 1;
        }
      }
    }
  } else {
    while (true) {

      getEngFin(i);

      counter = counter + 1;

      i = i + 1;

      if (counter == wordsTrained) {
        break;
      };

      if (i > maxLine) {
        readEngFin.seekg(0,std::ifstream::beg);  
      }
    }
  }
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

void getEngFin(int k) {
  pointerMover(readEngFin, k);

  std::string wordEng;
  getline(readEngFin, wordEng, '|');

  readEngFin.seekg(1, std::ifstream::cur);

  std::string wordFin;
  getline(readEngFin, wordFin, '|');

  std::string wordFinInput;
  std::cout << "What is the Finnish word for " << wordEng << "? " << std::endl;
  std::cin >> wordFinInput;
  std::cout << std::endl;

  if (wordFinInput == wordFin) {
    std::cout << "Yes! :)" << std::endl;
  } else {
    std::cout << "No :(" << std::endl;
  };
}