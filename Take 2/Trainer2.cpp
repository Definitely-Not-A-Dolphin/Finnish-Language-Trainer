#include <cmath>
#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <vector>

void practiseWords(std::string way);
void pointerMover(std::ifstream &file, int k);
bool listChecker(std::list<std::string> searchedList, std::string searchedWord);
void getEngFin(int k);
void getFinEng(int k);
std::string gradeMessage(double grade);
std::string getEng(int line);
std::string getFin(int line);

std::ifstream readEngFin("wordsEngFin.txt");

int wordsTrained;
int maxLine = 50;
std::string EngOrFin;

struct {
  bool infinite;
  bool random;
} Practise;

struct {
  std::list<std::string> no = {"No",  "no",  "Nah", "nah",
                               "Nei", "nei", "Nee", "nee"};
  std::list<std::string> yes = {"Yes", "yes", "Yeah", "yeah", "Yea",
                                "yea", "Ye",  "ye",   "Ja",   "ja"};
  std::list<std::string> language = {"Finnish", "finnish", "English", "english"};
} List;

struct {
  int correct;
  int incorrect;
} Score;

int main() {

  while (true) {

    // English or Finnish
    while (true) {
      std::cout
          << "Would you like to practise Finnish words or English words? ";
      std::cin >> EngOrFin;

      if (listChecker(List.language, EngOrFin)) {
        break;
      } else {
        std::cout << std::endl
                  << "Sorry, I could not understand that. Please re-enter your "
                     "answer."
                  << std::endl;
      }
    };

    // How many words?
    std::cout
        << "How many words do you want to practise (the current list contains "
        << maxLine << " words)? ";
    std::cin >> wordsTrained;

    // Random order?
    while (true) {
      std::string answerRandom;
      std::cout << "Do you want to randomise the words? ";
      std::cin >> answerRandom;

      if (listChecker(List.yes, answerRandom)) {
        Practise.random = true;
        break;
      } else if (listChecker(List.no, answerRandom)) {
        Practise.random = false;
        break;
      } else {
        std::cout << std::endl
                  << "Sorry, I could not understand that. Please re-enter your "
                     "answer."
                  << std::endl;
      }
    }

    practiseWords(EngOrFin);

    double grade = (Score.correct / wordsTrained) * 9 + 1;
    std::cout << gradeMessage(grade) << std::endl;

    Score.correct, Score.incorrect = 0;

    std::string repeat;
    std::cout << std::endl << "Do you want to try again? " << std::endl;
    std::cin >> repeat;

    if (listChecker(List.no, repeat)) {
      break;
    }
  }

  return 0;
}

void practiseWords(std::string way) {

  int counter = 0;

  int i = 1;

  if (Practise.random) {
    while (true) {

      // Get random sequence n
      std::vector<int> randomSequence;

      if (way == "Finnish" or way == "finnish") {
        getEngFin(randomSequence.at(0));
      } else {
        getFinEng(randomSequence.at(0));
      };

      counter = counter + 1;

      if (i > maxLine) {
        if (Practise.infinite = false) {
          break;
        } else {
          i = 1;
        }
      }
    }
  } else {
    while (true) {

      if (way == "Finnish" or way == "finnish") {
        getEngFin(i);
      } else {
        getFinEng(i);
      };

      counter = counter + 1;

      i = i + 1;

      if (counter == wordsTrained) {
        break;
      };

      if (i > maxLine) {
        readEngFin.seekg(0, std::ifstream::beg);
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
  std::string wordEng = getEng(k);

  std::string wordFin = getFin(k);

  std::string wordFinInput;
  std::cout << std::endl << "What is the Finnish word for " << wordEng << "? ";
  std::cin >> wordFinInput;
  std::cout << std::endl;

  if (wordFinInput == wordFin) {
    std::cout << "Yes! :)" << std::endl;
    Score.correct += 1;
  } else {
    std::cout << "No :(" << std::endl;
    Score.incorrect += 1;
  };
  std::cout << "Your score: (" << Score.correct << " / " << Score.incorrect
            << ")" << std::endl;
}

void getFinEng(int k) {
  std::string wordEng = getEng(k);

  std::string wordFin = getFin(k);

  std::string wordEngInput;
  std::cout << std::endl
            << "What is the " << EngOrFin << " word for " << wordFin << "? ";
  std::cin >> wordEngInput;
  std::cout << std::endl;

  if (wordEngInput == wordEng) {
    std::cout << "Yes! :)" << std::endl;
    Score.correct += 1;
  } else {
    std::cout << "No :(" << std::endl;
    Score.incorrect += 1;
  };
  std::cout << "Your score: (" << Score.correct << " / " << Score.incorrect
            << ")" << std::endl;
}

std::string gradeMessage(double grade) {
  std::cout << std::endl << "Your grade is: " << grade << "/10" << std::endl;

  std::vector<std::string> gradeMessage = {
      "This is too hard for you. Have you considered Swedish?",
      "Were you even trying?",
      "I would consider that not very good.",
      "It's okay, could be better.",
      "Solid grade!",
      "Wow, good job!"};

  return gradeMessage.at((int)floor(grade / 2));
}

std::string getEng(int line) {

  pointerMover(readEngFin, line);

  std::string wordEng;
  getline(readEngFin, wordEng, '|');

  return wordEng;
}

std::string getFin(int line) {

  pointerMover(readEngFin, line);

  std::string buffer;
  getline(readEngFin, buffer, '|');

  readEngFin.seekg(1, std::ifstream::cur);

  std::string wordFin;
  getline(readEngFin, wordFin, '|');

  return wordFin;
}