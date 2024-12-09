#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <vector>

void englishFinnish();
void pointerMover(std::ifstream &file, int k);
bool listChecker(std::list<std::string> searchedList, std::string searchedWord);
void getEngFin(int k);
void grade();
std::string getEng(int line);
std::string getFin(int line);

std::ifstream readEngFin("wordsEngFin.txt");

int wordsTrained;
int maxLine = 50;

struct {
  bool infinite;
  bool random;
} Practise;

struct {
  std::list<std::string> no = {"No",  "no",  "Nah", "nah",
                               "Nei", "nei", "Nee", "nee"};
  std::list<std::string> yes = {"Yes", "yes", "Yeah", "yeah", "Yea",
                                "yea", "Ye",  "ye",   "Ja",   "ja"};
} List;

struct {
  int correct;
  int incorrect;
} Score;

int main() {

  std::cout
      << "How many words do you want to practise (the current list contains "
      << maxLine << " words)? ";
  std::cin >> wordsTrained;

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
      std::cout
          << std::endl
          << "Sorry, I could not understand that. Please re-enter your answer."
          << std::endl;
    }
  }

  englishFinnish();

  void grade();

  Score.correct, Score.incorrect = 0;

  return 0;
}

void englishFinnish() {

  int counter = 0;

  int i = 1;

  if (Practise.random) {
    while (true) {

      // Get random sequence n
      std::vector<int> randomSequence;

      getEngFin(randomSequence.at(0));

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

      getEngFin(i);

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

void grade() {
  double grade = (Score.correct / wordsTrained) * 9 + 1;
  std::cout << std::endl << "Your grade is: " << grade << "/10" << std::endl;

  std::string gradeMessage;

  if (grade == 10) {
    gradeMessage = "Wow, good job!";
  } else if (8 <= grade < 10) {
    gradeMessage = "Solid grade!";
  } else if (6 <= grade < 8) {
    gradeMessage = "It's okay, could be better.";
  } else if (4 <= grade < 6) {
    gradeMessage = "I would consider that not very good.";
  } else if (2 <= grade < 4) {
    gradeMessage = "Were you even trying?";
  } else {
    gradeMessage = "This is too hard for you. Have you considered Swedish?";
  };
  std::cout << gradeMessage << std::endl;
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