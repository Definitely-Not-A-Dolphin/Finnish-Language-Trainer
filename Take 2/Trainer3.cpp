#include <cmath>
#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <vector>

// I'll use these as headers if I could figure out how they work
void pointerMover(std::ifstream &file, int k);
bool listChecker(std::list<std::string> searchedList, std::string searchedWord);
int fileLenght(std::ifstream &file);

// Practise Functions
void practiseStandard(bool random, std::string language, int finCase);
void practiseVerbs();

// Get Functions
void getEngFin(int line, int finCase);
void getFinEng(int line);
std::string getElement(int row, int column);
std::string getEng(int line);
std::string getFin(int line, int finCase);

// Other
std::string gradeMessage(double grade);

int maxLine = 3;

struct {
  // Questions
  int wordType;
  std::string language;
  int finCase;
  double wordAmount;
  bool random;
} Practise;

struct {
  std::list<std::string> no = {"No",  "no",  "Nah", "nah",
                               "Nei", "nei", "Nee", "nee"};
  std::list<std::string> yes = {"Yes", "yes", "Yeah", "yeah", "Yea",
                                "yea", "Ye",  "ye",   "Ja",   "ja"};
  std::list<std::string> language = {"Finnish", "finnish", "English",
                                     "english"};
  std::list<std::string> cases = {"Nominatiivi", "Genitiivi",   "Akkusatiivi",
                                  "Partitiivi",  "nominatiivi", "genitiivi",
                                  "akkusatiivi", "partitiivi"};
} List;

struct {
  std::vector<std::string> wordType = {
      "adjectivesEngFin.csv", "nounsEngFin.csv", "numbersEngFin.csv",
      "pronounsEngFin.csv",   "verbsEngFin.csv", "otherEngFin.csv",
  };
} Vector;

struct {
  double correct;
  int incorrect;
} Score;

// File-related
std::string fileName = Vector.wordType.at(Practise.wordType - 1);
std::ifstream open(fileName, std::ios::in);
std::ifstream readFile(fileName);

int main() {

  while (true) {
    // Word Type
    while (true) {
      std::cout << "What type of word would you like to practise? " << std::endl
                << "  Adjectives (type 1), " << std::endl
                << "  Nouns (type 2), " << std::endl
                << "  Numbers (type 3), " << std::endl
                << "  Pronouns (type 4), " << std::endl
                << "  Verbs (type 5), " << std::endl
                << "  Other (type 6), " << std::endl;
      std::cin >> Practise.wordType;

      if (1 <= Practise.wordType <= 6) {
        break;
      } else {
        std::cout << std::endl
                  << "Sorry, I could not understand that. Please re-enter your "
                     "answer."
                  << std::endl;
      }
    };

    // English or Finnish
    while (true) {
      std::cout << std::endl << "What language would you like to practise? ";
      std::cin >> Practise.language;

      if (listChecker(List.language, Practise.language)) {
        break;
      } else {
        std::cout << std::endl
                  << "Sorry, I could not understand that. Please re-enter your "
                     "answer."
                  << std::endl;
      }
    };

    // What case?
    if ((Practise.language == "Finnish" or Practise.language == "finnish") and
        Practise.wordType != 5) {
      while (true) {
        std::cout << std::endl
                  << "What case would you like to practise? " << std::endl
                  << "  Nominatiivi (type 1), " << std::endl
                  << "  Genitiivi (type 2), " << std::endl
                  << "  Partitiivi (type 3), " << std::endl
                  << "  Akkusatiivi (type 4), " << std::endl;
        std::cin >> Practise.finCase;

        if (1 <= Practise.finCase <= 4) {
          break;
        } else {
          std::cout
              << std::endl
              << "Sorry, I could not understand that. Please re-enter your "
                 "answer."
              << std::endl;
        }
      }
    }

    // How many words?
    std::cout << std::endl
              << "How many words do you want to practise (the current list "
                 "contains "
              << maxLine << " words)? ";
    std::cin >> Practise.wordAmount;

    // Random order?
    while (true) {
      std::string answerRandom;
      std::cout << std::endl << "Do you want to randomise the words? ";
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

    if (Practise.wordType != 5) {
      practiseStandard(Practise.random, Practise.language, Practise.finCase);
    } else if (Practise.wordType = 5) {
      practiseVerbs();
    }

    std::cout << Score.correct << std::endl << Practise.wordAmount << std::endl;
    double grade = (Score.correct / Practise.wordAmount) * 9 + 1;
    std::cout << grade << std::endl;
    std::cout << gradeMessage(grade) << std::endl;

    Score.correct, Score.incorrect = 0;

    std::string repeat;
    std::cout << std::endl << "Do you want to try again? " << std::endl;
    std::cin >> repeat;

    readFile.close();

    if (listChecker(List.no, repeat)) {
      break;
    }
  }

  return 0;
}

void practiseStandard(bool random, std::string language, int finCase) {

  int counter = 0;

  if (random) {
    while (true) {

      // Get random sequence n
      std::vector<int> randomSequence;

      if (language == "English" or language == "english") {
        getFinEng(randomSequence.at(counter));
      } else {
        getEngFin(randomSequence.at(counter), finCase);
      }

      counter += 1;

      if (counter == Practise.wordAmount) {
        break;
      }
    }
  } else {
    int line = 2;

    while (true) {
      if (language == "English" or language == "english") {
        getFinEng(line);
      } else {
        getEngFin(line, finCase);
      };

      counter += 1, line += 1;

      if (counter == Practise.wordAmount) {
        break;
      };

      if (line > maxLine) {
        readFile.seekg(0, std::ifstream::beg);
        pointerMover(readFile, 2);
      }
    }
  }
  readFile.close();
}

void practiseVerbs() {
  std::ifstream readFile("verbsEngFin.csv");

  std::vector<int> randomSequence1;
  std::vector<int> randomSequence2;

  int counter = 0;

  while (true) {

    std::string verb = getElement(randomSequence1.at(counter), 1);
    std::string pronoun = getElement(1, randomSequence2.at(counter));
    std::string conjugationFile =
        getElement(randomSequence1.at(counter), randomSequence2.at(counter));
    std::string conjugationInput;
    std::cout << "Give the correct conjugation of the verb " << verb << ": "
              << pronoun;
    std::cin >> conjugationInput;
    std::cout << std::endl;

    if (conjugationInput == conjugationFile) {
      std::cout << "Yes! :)" << std::endl;
      Score.correct += 1;
    } else {
      std::cout << "No :(" << std::endl;
      Score.incorrect += 1;
    };
    std::cout << "Your current score: (" << Score.correct << " / "
              << Score.incorrect << ")" << std::endl;

    counter += 1;

    if (counter == Practise.wordAmount) {
      break;
    }
  }
  readFile.close();
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

void getEngFin(int line, int finCase) {
  std::string wordEng = getEng(line);

  std::string wordFin = getFin(line, finCase);

  std::string wordFinInput;
  std::cout << std::endl << "What is the Finnish word for " << wordEng << "? ";
  std::cin >> wordFinInput;
  std::cout << std::endl;

  if (wordFinInput == wordFin) {
    std::cout << "Yes! :)" << std::endl;
    Score.correct += 1;
  } else {
    std::cout << "No :( The correct word was " << wordFin << std::endl;
    Score.incorrect += 1;
  };
  std::cout << "Your current score: (" << Score.correct << " / "
            << Score.incorrect << ")" << std::endl;
}

void getFinEng(int line) {
  std::string wordEng = getEng(line);

  std::string wordFin = getFin(line, 2);

  std::string wordEngInput;
  std::cout << std::endl << "What is the English word for " << wordFin << "? ";
  std::cin >> wordEngInput;
  std::cout << std::endl;

  if (wordEngInput == wordEng) {
    std::cout << "Yes! :)" << std::endl;
    Score.correct += 1;
  } else {
    std::cout << "No :(" << std::endl;
    Score.incorrect += 1;
  };
  std::cout << "Your current score: (" << Score.correct << " / "
            << Score.incorrect << ")" << std::endl;
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

  std::string wordEng = getElement(line, 1);

  return wordEng;
}

std::string getFin(int line, int finCase) {

  std::string wordFin = getElement(line, finCase + 1);

  return wordFin;
}

std::string getElement(int row, int column) {
  pointerMover(readFile, row);

  std::string output;
  std::getline(readFile, output);

  std::string tmp; // A string to store the word on each iteration.
  std::stringstream str_strm(output);
  std::vector<std::string> wordsVector; // Create vector to hold our words
  while (str_strm >> tmp) {
    tmp.pop_back();
    wordsVector.push_back(tmp);
  }

  return wordsVector.at(column - 1);
}

int fileLenght(std::ifstream &file) {
  char ch;
  int lineCount=0;
  while (file.get(ch)) { // Read one character at a time
    if (ch == '\n') {
      lineCount++;
    }
  }
  return lineCount;
}