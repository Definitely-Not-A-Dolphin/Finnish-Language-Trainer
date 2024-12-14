#include <cmath>
#include <fstream>
#include <iostream>
#include <list>
#include <random>
#include <sstream>
#include <string>
#include <vector>

// Header
void pointerMover(std::string fileName, int k);
int randomInt(int lower, int upper) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(lower, upper);

  int randomX = dis(gen);

  return randomX;
}
bool vectorChecker(std::vector<std::string> searchedVector,
                   std::string searchedWord) {
  bool result = false;

  for (std::string comparer : searchedVector) {
    if (comparer == searchedWord) {
      result = true;
    }
  };

  return result;
}
int fileSize(std::string fileName);

// Get functions
void getEngPractise(std::string fileName, int line);
void getFinPractise(std::string fileName, int line, int finCase);
std::string getEng(std::string fileName, int line);
std::string getFin(std::string fileName, int line, int finCase);
std::string getElement(std::string fileName, int row, int column);

// Practices
void standardPractise(std::string fileName, bool random, std::string language,
                      int finCase);
void verbsPractise();

// Questions
void wordTypeQuestion();
void languageQuestion();
void caseQuestion();
void wordAmountQuestion();
void randomQuestion();

struct {
  std::string wordTypeString;
  int wordTypeInt;
  std::string language;
  int finCase;
  int wordAmount;
  bool random;
} Answer;

struct {
  int correct;
  int incorrect;
} Score;

struct {
  std::vector<std::string> no = {"No",  "no",  "Nah", "nah",
                                 "Nei", "nei", "Nee", "nee"};
  std::vector<std::string> yes = {"Yes", "yes", "Yeah", "yeah", "Yea",
                                  "yea", "Ye",  "ye",   "Ja",   "ja"};
  std::vector<std::string> language = {"Finnish", "finnish", "English",
                                       "english"};
  std::vector<std::string> cases = {"Nominatiivi", "Genitiivi",   "Akkusatiivi",
                                    "Partitiivi",  "nominatiivi", "genitiivi",
                                    "akkusatiivi", "partitiivi"};
  std::vector<std::string> wordType = {"adjectivesFile.csv", "nounsFile.csv",
                                       "numbersFile.csv",    "pronounsFile.csv",
                                       "verbsFile.csv",      "otherFile.csv"};
} Vector;

int main() {

  std::ifstream readFile("nounsFile.csv", std::ios::in);

  std::cout << fileSize("nounsFile.csv") << std::endl;

  readFile.close();

  // Questions
  wordTypeQuestion();
  if (Answer.wordTypeInt != 5) {
    languageQuestion();
    randomQuestion();
    if (Answer.language == "Finnish" or Answer.language == "finnish") {
      caseQuestion();
    }
  };

  wordAmountQuestion();

  if (Answer.wordTypeInt != 5) {
    standardPractise(Answer.wordTypeString, Answer.random, Answer.language,
                     Answer.finCase);
  } else if (Answer.wordTypeInt == 5) {
    verbsPractise();
  };

  return 0;
}

// Questions
void wordTypeQuestion() {
  while (true) {
    std::cout << "What type of word would you like to practise? " << std::endl
              << "  Adjectives (type 1), " << std::endl
              << "  Nouns (type 2), " << std::endl
              << "  Numbers (type 3), " << std::endl
              << "  Pronouns (type 4), " << std::endl
              << "  Verbs (type 5), " << std::endl
              << "  Other (type 6), " << std::endl;
    std::cin >> Answer.wordTypeInt;

    if (1 <= Answer.wordTypeInt <= 6) {
      break;
    } else {
      std::cout << std::endl
                << "Sorry, I could not understand that. Please re-enter your "
                   "answer."
                << std::endl;
    }
  };

  if (Answer.wordTypeInt != 5) {
    Answer.wordTypeString = Vector.wordType.at(Answer.wordTypeInt - 1);
  } else if (Answer.wordTypeInt == 5) {
    Answer.wordTypeString = Vector.wordType.at(4);
  }
}
void languageQuestion() {
  while (true) {
    std::cout << std::endl << "What language would you like to practise? ";
    std::cin >> Answer.language;

    if (vectorChecker(Vector.language, Answer.language)) {
      break;
    } else {
      std::cout << std::endl
                << "Sorry, I could not understand that. Please re-enter your "
                   "answer."
                << std::endl;
    }
  };
}
void caseQuestion() {
  while (true) {
    std::cout << std::endl
              << "What case would you like to practise? " << std::endl
              << "  Nominatiivi (type 1), " << std::endl
              << "  Genitiivi (type 2), " << std::endl
              << "  Partitiivi (type 3), " << std::endl
              << "  Akkusatiivi (type 4), " << std::endl;
    std::cin >> Answer.finCase;

    if (1 <= Answer.finCase <= 4) {
      break;
    } else {
      std::cout << std::endl
                << "Sorry, I could not understand that. Please re-enter your "
                   "answer."
                << std::endl;
    }
  }
}
void wordAmountQuestion() {
  std::cout << std::endl << "How many words do you want to practise? ";
  std::cin >> Answer.wordAmount;
}
void randomQuestion() {
  while (true) {
    std::string ans;
    std::cout << std::endl << "Would you like to randomise the word order? ";
    std::cin >> ans;

    if (vectorChecker(Vector.yes, ans)) {
      Answer.random = true;
      break;
    } else if (vectorChecker(Vector.no, ans)) {
      Answer.random = false;
      break;
    } else {
      std::cout << std::endl
                << "Sorry, I could not understand that. Please re-enter your "
                   "answer."
                << std::endl;
    }
  };
}

void standardPractise(std::string fileName, bool random, std::string language,
                      int finCase) {

  std::ifstream file(fileName, std::ios::in);

  int counter = 0;
  int maxLine = fileSize(fileName);

  if (random) {

    while (true) {

      // Get random sequence n
      int randomNumber = randomInt(2, maxLine);

      if (language == "English" or language == "english") {
        getEngPractise(fileName, randomNumber);
      } else {
        getFinPractise(fileName, randomNumber, finCase);
      }

      counter += 1;

      if (counter == Answer.wordAmount) {
        break;
      }
    }
  } else {
    int line = 2;

    while (true) {
      if (language == "English" or language == "english") {
        getEngPractise(fileName, line);
      } else {
        getFinPractise(fileName, line, finCase);
      };

      counter += 1, line += 1;

      if (counter == Answer.wordAmount) {
        break;
      };

      if (line > maxLine) {
        file.seekg(0, std::ifstream::beg);
        pointerMover(fileName, 2);
      }
    }
  }

  file.close();
}

void verbsPractise() {
  std::ifstream file("verbsFile.csv", std::ios::in);

  int counter = 0;
  int maxLine = fileSize("verbsFile.csv");

  while (true) {
    int randomNumber1 = randomInt(2, maxLine);
    int randomNumber2 = randomInt(2, 8);

    std::string pronoun = getElement("VerbsFile.csv", 1, randomNumber2);
    std::string verb = getElement("verbsFile.csv", randomNumber1, 1);
    std::string wordFin =
        getElement("verbsFile.csv", randomNumber1, randomNumber2);
    std::string wordFinInput;

    std::cout << "Enter the correct conjugation with the verb " << verb << ": "
              << pronoun << " ";
    std::cin >> wordFinInput;

    if (wordFinInput == wordFin) {
      std::cout << "Yes! :)" << std::endl;
    } else {
      std::cout << "No :( The correct word was " << wordFin << std::endl;
    };

    counter += 1;

    if (counter == Answer.wordAmount) {
      break;
    }
  };

  file.close();
}

void getFinPractise(std::string fileName, int line, int finCase) {
  std::ifstream file(fileName, std::ios::in);

  std::string wordEng = getEng(fileName, line);

  std::string wordFin = getFin(fileName, line, finCase);

  std::string wordFinInput;
  std::cout << std::endl << "What is the Finnish word for " << wordEng << "? ";
  std::cin >> wordFinInput;
  std::cout << std::endl;

  if (wordFinInput == wordFin) {
    std::cout << "Yes! :)" << std::endl;
  } else {
    std::cout << "No :( The correct word was " << wordFin << std::endl;
  };

  file.close();
}

void getEngPractise(std::string fileName, int line) {
  std::ifstream file(fileName, std::ios::in);

  std::string wordEng = getEng(fileName, line);

  std::string wordFin = getFin(fileName, line, 1);

  std::string wordEngInput;
  std::cout << std::endl << "What is the Finnish word for " << wordFin << "? ";
  std::cin >> wordEngInput;
  std::cout << std::endl;

  if (wordEngInput == wordEng) {
    std::cout << "Yes! :)" << std::endl;
  } else {
    std::cout << "No :( The correct word was " << wordEng << std::endl;
  };

  file.close();
}

std::string getEng(std::string fileName, int line) {

  std::ifstream file(fileName, std::ios::in);

  std::string wordFin = getElement(fileName, line, 1);

  file.close();

  return wordFin;
}

std::string getFin(std::string fileName, int line, int finCase) {

  std::ifstream file(fileName, std::ios::in);

  std::string wordFin = getElement(fileName, line, finCase + 1);

  file.close();

  return wordFin;
}

std::string getElement(std::string fileName, int row, int column) {

  std::ifstream file(fileName, std::ios::in);

  pointerMover(fileName, row);

  std::string output;
  getline(file, output);

  std::string tmp; // A string to store the word on each iteration.
  std::stringstream str_strm(output);
  std::vector<std::string> wordsVector; // Create vector to hold our words
  while (str_strm >> tmp) {
    tmp.pop_back();
    wordsVector.push_back(tmp);
  };

  file.close();

  return wordsVector.at(column - 1);
}

void pointerMover(std::string fileName, int k) {
  // Special thanks to Elses/Menium for writing this part!
  std::ifstream file(fileName, std::ios::in);

  file.clear();
  file.seekg(0, std::ios::beg);

  std::string line;
  for (int currentLine = 1; currentLine < k; currentLine++) {
    if (!std::getline(file, line)) {
      std::cerr << "Error: Line " << k << " does not exist!" << std::endl;
      return;
    }
  };
  file.close();
}

int fileSize(std::string fileName) {
  std::ifstream file(fileName, std::ios::in);

  int lineCounter = 0;
  std::string output;

  while (getline(file, output)) {
    lineCounter += 1;
  };
  file.close();

  return lineCounter;
}