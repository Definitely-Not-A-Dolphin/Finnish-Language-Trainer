#include <cmath>
#include <fstream>
#include <iostream>
#include <list>
#include <random>
#include <sstream>
#include <string>
#include <vector>

// Header
void pointerMover(std::ifstream &file, int k);
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
bool vectorCheckerInt(std::vector<int> searchedVector, int searchedInt) {
  bool result = false;

  for (int comparer; comparer < searchedVector.size(); comparer++) {
    if (comparer = searchedInt) {
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
// Not used anymore, but I decided to keep it in, I might need it later as a
// temporary substitute if its char-version stops functioning for whatever
// reason it may be.
std::string getElement(std::string fileName, int row, int column);
std::string getElementChar(std::string fileName, int row, int column);

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
  double wordAmount;
  bool random;
} Answer;

struct {
  double correct;
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
  std::vector<std::string> gradeMessage = {
      "This is too hard for you. Have you considered Swedish?",
      "Were you even trying?",
      "I would consider that not very good.",
      "It's okay, could be better.",
      "Solid grade!",
      "Wow, good job!"};
} Vector;

int main() {

  while (true) {

    std::cout << std::endl
              << "-+======================================+-" << std::endl;

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

    if (Answer.wordAmount == 0) {
    };

    if (Answer.wordTypeInt != 5) {
      standardPractise(Answer.wordTypeString, Answer.random, Answer.language,
                       Answer.finCase);
    } else if (Answer.wordTypeInt == 5) {
      verbsPractise();
    };

    double grade = (Score.correct / Answer.wordAmount) * 9 + 1;

    std::cout << "Your grade is " << grade << "/10; "
              << Vector.gradeMessage.at((int)floor(grade / 2)) << std::endl;

    Score.correct, Score.incorrect = 0;

    bool keepGoingBool;

    while (true) {
      std::string keepGoing;
      std::cout << std::endl << "Do you want to keep going with pracising? ";
      std::cin >> keepGoing;

      if (vectorChecker(Vector.no, keepGoing)) {
        keepGoingBool = false;
        break;
      } else if (vectorChecker(Vector.yes, keepGoing)) {
        keepGoingBool = true;
        break;
      } else {
        std::cout << "Sorry, I could not understand that, please try again: "
                  << std::endl;
      };
    };

    Score.correct = 0;
    Score.incorrect = 0;

    if (!keepGoingBool) {
      break;
    };
  };

  return 0;
}

// Questions
void wordTypeQuestion() {
  while (true) {
    std::cout << std::endl
              << "What type of word would you like to practise? " << std::endl
              << "  Adjectives (type 1), " << std::endl
              << "  Nouns (type 2), " << std::endl
              << "  Numbers (type 3), " << std::endl
              << "  Pronouns (type 4), " << std::endl
              << "  Verbs (type 5), " << std::endl;
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
    // std::cin >> Answer.language;
    std::getline(std::cin >> std::ws, Answer.language);

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
    std::getline(std::cin >> std::ws, ans);

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

  if (Answer.wordAmount == 0) {
    Answer.wordAmount = fileSize(fileName) - 1;
  };

  int counter = 0;
  int maxLine = fileSize(fileName);

  if (random) {
    while (true) {

      int randomNumber = randomInt(2, maxLine);

      std::cout << std::endl
                << "-+======================================+-" << std::endl;

      if (language == "English" or language == "english") {
        getEngPractise(fileName, randomNumber);
      } else {
        getFinPractise(fileName, randomNumber, finCase);
      };

      counter++;

      if (counter == Answer.wordAmount) {
        break;
      };
    }
  } else {
    int line = 2;

    while (true) {

      std::cout << "-+======================================+-" << std::endl;

      if (language == "English" or language == "english") {
        getEngPractise(fileName, line);
      } else {
        getFinPractise(fileName, line, finCase);
      };

      counter += 1;
      line += 1;

      if (counter == Answer.wordAmount) {
        break;
      };

      if (line > maxLine) {
        file.seekg(0, std::ifstream::beg);
        pointerMover(file, 2);
      }
    }
  };

  file.close();
}

void verbsPractise() {
  std::ifstream file("verbsFile.csv", std::ios::in);

  // std::cout << fileSize("verbsFile.csv") << std::endl;

  if (Answer.wordAmount == 0) {
    Answer.wordAmount = (fileSize("verbsFile.csv") - 1) * 6;
  };

  int counter = 0;
  int maxLine = fileSize("verbsFile.csv");

  while (counter != Answer.wordAmount) {

    int verbInt = randomInt(2, maxLine);
    int pronounInt = randomInt(3, 8);

    std::cout << std::endl
              << "-+======================================+-" << std::endl;

    // Tot hier gaat alles goed!
    std::string pronoun = getElement("verbsFile.csv", 1, pronounInt);
    std::string verb = getElement("verbsFile.csv", verbInt, 1);
    std::string verbConj = getElement("verbsFile.csv", verbInt, pronounInt);

    std::string verbConjInput;
    std::cout << "Enter the correct conjugation with the verb " << verb << ": "
              << pronoun << " ";
    std::cin >> verbConjInput;

    if (verbConjInput == verbConj) {
      Score.correct++;
      std::cout << "Yes! :)";
    } else {
      Score.incorrect++;
      std::cout << "No :( The correct word was " << verbConj;
    };

    std::cout << " (" << Score.correct << " / " << Score.incorrect << ")"
              << std::endl;

    counter++;
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
    Score.correct++;
    std::cout << "Yes! :) ";
  } else {
    Score.incorrect++;
    std::cout << "No :( The correct word was " << wordFin << std::endl;
  };

  std::cout << " (" << Score.correct << " / " << Score.incorrect << ")"
            << std::endl;

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
    Score.correct++;
  } else {
    Score.incorrect++;
    std::cout << "No :( The correct word was " << wordEng << std::endl;
  };

  std::cout << " (" << Score.correct << " / " << Score.incorrect << ")"
            << std::endl;

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

  pointerMover(file, row);

  std::string output;

  std::vector<std::string> wordsVector = {};

  while (getline(file, output, ',')) {

    if (output[0] == ' ') {
      output.erase(output.begin());
    };

    wordsVector.push_back(output);

    output.erase();
  };

  file.close();

  return wordsVector.at(column - 1);
}

// this function is not used because it is whacky (reference to my collegue
// whose name is wh4cky) and finite, its here for the sake of being here
std::string getElementChar(std::string fileName, int row, int column) {

  std::ifstream readFile(fileName, std::ios::in);

  pointerMover(readFile, row);

  struct {
    char thing1[36];
    char thing2[36];
    char thing3[36];
    char thing4[36];
    char thing5[36];
    char thing6[36];
    char thing7[36];
    char thing8[36];
    char thing9[36];
  } val;

  struct {
    std::string thing1;
    std::string thing2;
    std::string thing3;
    std::string thing4;
    std::string thing5;
    std::string thing6;
    std::string thing7;
    std::string thing8;
    std::string thing9;
  } tpt;

  std::vector<char *> charVector = {val.thing1, val.thing2, val.thing3,
                                    val.thing4, val.thing5, val.thing6,
                                    val.thing7, val.thing8, val.thing9};

  std::vector<std::string> strVector = {tpt.thing1, tpt.thing2, tpt.thing3,
                                        tpt.thing4, tpt.thing5, tpt.thing6,
                                        tpt.thing7, tpt.thing8, tpt.thing9};

  int g;

  for (int gloop = 1; gloop <= column; gloop++) {

    readFile.get(charVector.at(gloop), 36, ',');
    readFile.seekg(1, std::ifstream::cur);

    strVector.at(gloop) = charVector.at(gloop);

    if (gloop == column) {
      readFile.close();
      g = gloop;
    };
  };

  if (strVector.at(g)[0] == ' ') {
    strVector.at(g).erase(strVector.at(g).begin());
  };
  return strVector.at(g);
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

int fileSize(std::string fileName) {
  std::ifstream file(fileName, std::ios::in);

  int lineCounter = 0;
  std::string output;

  while (getline(file, output, '\n')) {
    lineCounter += 1;
  };

  file.close();

  return lineCounter;
}