#include <cmath>
#include <fstream>
#include <iostream>
#include <list>
#include <random>
#include <string>
#include <vector>

// Headers
//       "Headers/generalFileStream.cpp"
#include "Headers/csvFileStream.cpp"

// Soon-to-be Headers
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

// Get functions
void getEngPractise(std::fstream &file, int line);
void getFinPractise(std::fstream &file, int line, int finCase);
std::string getEng(std::fstream &file, int line);
std::string getFin(std::fstream &file, int line, int finCase);

// Practices
void standardPractise(int wordTypeInt, bool random, std::string language,
                      int finCase);
void verbsPractise();

// Questions
void wordTypeQuestion();
void languageQuestion();
void caseQuestion();
void wordAmountQuestion();
void randomQuestion();

// ReadStuff
void readAboutProgram() {
  std::fstream readFile("aboutProgram.txt", std::ios::in);

  std::string filler;

  while (getline(readFile, filler)) {
    std::cout << filler << std::endl;
  };

  readFile.close();
};
void readAboutGrammar() {
  int startDec2;

  while (true) {
    std::cout << std::endl
              << "Choose what you want to read about" << std::endl
              << "  Nominatiivi (type 1), " << std::endl
              << "  Genitiivi (type 2), " << std::endl
              << "  Akkusatiivi (type 3)," << std::endl
              << "  Partitiivi (type 4)," << std::endl
              << "  Inessiivi (type 5)," << std::endl
              << "  Preesens (type 6)," << std::endl
              << "  Imperfekti (type 7)," << std::endl;
    std::cin >> startDec2;

    if (0 <= startDec2 and startDec2 <= 7) {
      break;
    } else {
      std::cout << "That's not a valid input, please try again." << std::endl;
    };
  };

  std::cout << std::endl;

  std::vector<std::string> polkVector = {"readAboutFiles/aboutNominatiivi.txt",
                                         "readAboutFiles/aboutGenitiivi.txt",
                                         "readAboutFiles/aboutAkkusatiivi.txt",
                                         "readAboutFiles/aboutPartitiivi.txt",
                                         "readAboutFiles/aboutInessiivi.txt",
                                         "readAboutFiles/aboutPreesens.txt",
                                         "readAboutFiles/aboutImperfekti.txt"};
  std::string polk = polkVector.at(startDec2 - 1);
  std::fstream file(polk);

  std::string temp;
  while (getline(file, temp)) {
    std::cout << temp << std::endl;
  };

  file.close();
};

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
  // verbsFile.csv doesnt exist anymore, it is solely a placeholder for the
  // directory that bears a part of its name.
  std::vector<std::string> wordType = {
      "wordsFiles/adjectivesFile.csv", "wordsFiles/nounsFile.csv",
      "wordsFiles/numbersFile.csv",    "wordsFiles/pronounsFile.csv",
      "wordsFiles/verbsFile.csv",      "wordsFiles/otherFile.csv"};
  std::vector<std::string> gradeMessage = {
      "This is too hard for you. Have you considered Swedish?",
      "Were you even trying?",
      "I would consider that not very good.",
      "It's okay, could be better.",
      "Solid grade!",
      "Wow, good job!"};
} Vector;

int main() {
  int startDec1;

  while (true) {
    while (true) {
      std::cout << std::endl
                << "Tervetuloa, this is a program written in C++ for those who "
                   "want to test their Finnish vocabulary and more!"
                << std::endl
                << "Select what "
                   "you would like to do:"
                << std::endl
                << "  Practise (type 1), " << std::endl
                << "  Read about grammar (type 2), " << std::endl
                << "  Read about this very program (type 3)" << std::endl
                << "  Quit (type 0)" << std::endl;
      std::cin >> startDec1;

      if (0 <= startDec1 and startDec1 <= 3) {
        break;
      } else {
        std::cout << "That's not a valid input, please try again." << std::endl;
      };
    };

    if (startDec1 == 3) {
      readAboutProgram();
    } else if (startDec1 == 2) {
      readAboutGrammar();
    } else if (startDec1 == 0) {
      break;
    } else if (startDec1 == 1) {
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

        if (Answer.wordTypeInt != 5) {
          standardPractise(Answer.wordTypeInt, Answer.random, Answer.language,
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
          std::cout << std::endl
                    << "Do you want to keep going with pracising? ";
          std::cin >> keepGoing;

          if (vectorChecker(Vector.no, keepGoing)) {
            keepGoingBool = false;
            break;
          } else if (vectorChecker(Vector.yes, keepGoing)) {
            keepGoingBool = true;
            break;
          } else {
            std::cout
                << "Sorry, I could not understand that, please try again: "
                << std::endl;
          };
        };

        Score.correct = 0;
        Score.incorrect = 0;

        if (!keepGoingBool) {
          break;
        };
      };
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

  Answer.wordTypeString = Vector.wordType.at(Answer.wordTypeInt - 1);
}
void languageQuestion() {
  while (true) {
    std::cout << std::endl
              << "In what language would you like to practise the words "
                 "(Finnish / English)? ";
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
              << "  Akkusatiivi (type 4), " << std::endl
              << "  Inessiivi (type 5)" << std::endl;
    std::cin >> Answer.finCase;

    if (1 <= Answer.finCase <= 5) {
      break;
    } else {
      std::cout << std::endl
                << "That's not a valid input, please try again." << std::endl;
    }
  }
}
void wordAmountQuestion() {
  while (true) {
    std::cout
        << std::endl
        << "How many words do you want to practise (type 0 if you want to "
           "practise the amount of words in the selected catogory)? "
        << std::endl;
    std::cin >> Answer.wordAmount;

    if (Answer.wordAmount >= 0) {
      break;
    } else {
      std::cout << "That's not a valid input, please try again." << std::endl;
    };
  };
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

void standardPractise(int wordTypeInt, bool random, std::string language,
                      int finCase) {

  std::string fileDirecName = Vector.wordType.at(Answer.wordTypeInt - 1);

  std::fstream file(fileDirecName);

  if (Answer.wordAmount == 0) {
    Answer.wordAmount = fileSize(fileDirecName) - 1;
  };

  int counter = 0;
  int maxLine = fileSize(fileDirecName);

  if (Answer.random) {
    while (true) {
      int randomNumber = randomInt(2, maxLine);

      std::cout << std::endl
                << "-+======================================+-" << std::endl;

      if (language == "English" or language == "english") {
        getEngPractise(file, randomNumber);
      } else {
        getFinPractise(file, randomNumber, finCase);
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
        getEngPractise(file, line);
      } else {
        getFinPractise(file, line, finCase);
      };

      counter++;
      line++;

      if (counter == Answer.wordAmount) {
        break;
      };

      if (line > maxLine) {
        file.seekg(0, std::fstream::beg);
        seekLine(file, 2);
      }
    }
  };

  file.close();
}

void verbsPractise() {
  std::cout << "What tense do you want to practise:" << std::endl
            << "  Preesens (present tense) (type 1)," << std::endl
            << "  Imperfekti (past tense) (type 2)," << std::endl;
  int tenseInt;
  std::cin >> tenseInt;

  std::string tenseFileName;

  while (true) {
    if (tenseInt == 1) {
      tenseFileName = "verbsFilePreesens.csv";
      break;
    } else if (tenseInt == 2) {
      tenseFileName = "verbsFileImperfekti.csv";
      break;
    } else {
      std::cout << "Sorry, I could not understand that. Please re-enter your "
                   "answer."
                << std::endl;
    }
  };

  std::string plok;

  switch (tenseInt) {
  case 1:
    plok = "wordsFiles/verbs/verbsFilePreesens.csv";
    break;
  case 2:
    plok = "wordsFiles/verbs/verbsFileImperfekti.csv";
    break;
  };

  std::fstream fileDirec{plok};

  if (Answer.wordAmount == 0) {
    Answer.wordAmount = (fileSize(plok) - 1) * 6;
  };

  int counter = 0;
  int maxLine = fileSize(plok);

  while (counter != Answer.wordAmount) {

    int verbInt = randomInt(2, maxLine);
    int pronounInt = randomInt(3, 8);

    std::cout << std::endl
              << "-+======================================+-" << std::endl
              << std::endl;

    std::string pronoun = getElement(fileDirec, 1, pronounInt);
    std::string verb = getElement(fileDirec, verbInt, 1);
    std::string verbConj = getElement(fileDirec, verbInt, pronounInt);

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

    std::cout << std::endl
              << " (" << Score.correct << " / " << Score.incorrect << ")"
              << std::endl;

    counter++;
  };

  fileDirec.close();
}

void getFinPractise(std::fstream &file, int line, int finCase) {
  std::string wordEng = getEng(file, line);

  std::string wordFin = getFin(file, line, finCase);

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
}

void getEngPractise(std::fstream &file, int line) {
  std::string wordEng = getEng(file, line);

  std::string wordFin = getFin(file, line, 1);

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
}

std::string getEng(std::fstream &file, int line) {
  return getElement(file, line, 1);
}

std::string getFin(std::fstream &file, int line, int finCase) {
  return getElement(file, line, finCase + 1);
}