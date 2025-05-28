#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// Headers
//       "Headers/general/generalFileStream.hpp"
#include "Headers/generalFileLib.hpp"
#include "Headers/datastructChecker.hpp"
#include "Headers/randomInt.hpp"

namespace Answer {
int activity;
std::string wordTypeFile;
int wordTypeInt;
std::string language;
int finCase;
double wordAmount;
bool random;
} // namespace Answer

namespace Score {
double correct;
int incorrect;
} // namespace Score

namespace Vector {
std::vector<std::string> negative = {"No",  "no",  "Nah", "nah", "Nei",
                                     "nei", "Nee", "nee", "N",   "n"};
std::vector<std::string> positive = {"Yes", "yes", "Yeah", "yeah", "Yea", "yea",
                                     "Ye",  "ye",  "Ja",   "ja",   "Y",   "y"};
std::vector<std::string> language = {"Finnish", "finnish", "English",
                                     "english"};
std::vector<std::string> wordTypeFile = {
    "1adjectives", "2nouns",          "3numbers",
    "4pronouns",   "verbs/5preesens", "verbs/6imperfekti"};
std::vector<std::string> gradeMessage = {
    "This is too hard for you. Have you considered Swedish?",
    "Were you even trying?",
    "I would consider that not very good.",
    "It's okay, could be better.",
    "Solid grade!",
    "Wow, good job!"};
} // namespace Vector

// Get functions
std::string getEng(csv_fstream &file, int line) {
  return file.getElement(line, 1);
}
std::string getFin(csv_fstream &file, int line, int finCase) {
  return file.getElement(line, finCase + 1);
}

// Questions
namespace Question {
void wordType() {

  std::cout << std::endl
            << "What type of word would you like to practise? " << std::endl
            << "  Adjectives (type 1), " << std::endl
            << "  Nouns (type 2), " << std::endl
            << "  Numbers (type 3), " << std::endl
            << "  Pronouns (type 4), " << std::endl
            << "  Verbs present tense (type 5), " << std::endl
            << "  Verbs past tense (type 6), " << std::endl;

  while (true) {
    std::cin >> Answer::wordTypeInt;

    if (1 <= Answer::wordTypeInt <= 6) {
      break;
    };

    std::cout << std::endl
              << "Sorry, I could not understand that. Please re-enter your "
                 "answer."
              << std::endl;
  };

  Answer::wordTypeFile =
      "wordsFiles/" + Vector::wordTypeFile.at(Answer::wordTypeInt - 1) + ".csv";
}
void language() {

  std::cout << std::endl
            << "In what language would you like to practise the words "
               "(Finnish / English)? ";

  while (true) {
    std::getline(std::cin >> std::ws, Answer::language);

    if (vectorChecker(Vector::language, Answer::language)) {
      break;
    };

    std::cout << std::endl
              << "Sorry, I could not understand that. Please try again:"
              << std::endl;
  };
}
void finCase() {
  std::cout << std::endl
            << "What case would you like to practise? " << std::endl
            << "  Nominatiivi (type 1), " << std::endl
            << "  Genitiivi (type 2), " << std::endl
            << "  Partitiivi (type 3), " << std::endl
            << "  Akkusatiivi (type 4), " << std::endl
            << "  Inessiivi (type 5)" << std::endl;

  while (true) {

    std::cin >> Answer::finCase;

    if (1 <= Answer::finCase <= 5) {
      break;
    };

    std::cout << std::endl
              << "That's not a valid input, please try again." << std::endl;
  }
}
void wordAmount() {
  if (Answer::wordTypeFile == "wordsFiles/verbs/preesens.csv" or
      Answer::wordTypeFile == "wordsFiles/verbs/imperfekti.csv") {
    std::cout << std::endl
              << "How many words do you want to practise? " << std::endl;
  } else {
    std::cout << std::endl
              << "How many words do you want to practise (there are "
              << countLines(Answer::wordTypeFile) - 1
              << " in the selected category)? " << std::endl;
  };

  while (true) {
    std::cin >> Answer::wordAmount;

    if (Answer::wordAmount >= 0) {
      break;
    };

    std::cout << std::endl
              << "That's not a valid input, please try again." << std::endl;
  };
}
void random() {

  std::string randomInput;
  std::cout << std::endl << "Would you like to randomise the word order? ";
  Answer::random = true;

  while (true) {

    std::getline(std::cin >> std::ws, randomInput);

    if (vectorChecker(Vector::positive, randomInput)) {
      break;
    };

    if (vectorChecker(Vector::negative, randomInput)) {
      Answer::random = false;
      break;
    };

    randomInput = "";

    std::cout << std::endl
              << "Sorry, I could not understand that. Please try again:"
              << std::endl;
  };
}
} // namespace Question

// Practice functions
namespace Practise {
void eng(csv_fstream &file, int line) {
  std::string wordEng = getEng(file, line);
  std::string wordFin = getFin(file, line, 1);

  std::string wordEngInput;
  std::cout << std::endl << "What is the Finnish word for " << wordFin << "? ";
  std::getline(std::cin >> std::ws, wordEngInput);
  std::cout << std::endl;

  if (wordEngInput == wordEng) {
    std::cout << "Yes! :)" << std::endl;
    Score::correct++;
  } else {
    Score::incorrect++;
    std::cout << "No :( The correct word was " << wordEng << std::endl;
  };

  std::cout << " (" << Score::correct << " / " << Score::incorrect << ")"
            << std::endl;
}
void fin(csv_fstream &file, int line, int finCase) {
  std::string wordEng = getEng(file, line);

  std::string wordFin = getFin(file, line, finCase);

  std::string wordFinInput;
  std::cout << std::endl << "What is the Finnish word for " << wordEng << "? ";
  std::getline(std::cin >> std::ws, wordFinInput);
  std::cout << std::endl;

  if (wordFinInput == wordFin) {
    Score::correct++;
    std::cout << "Yes! :) ";
  } else {
    Score::incorrect++;
    std::cout << "No :( The correct word was " << wordFin << std::endl;
  };

  std::cout << " (" << Score::correct << " / " << Score::incorrect << ")"
            << std::endl;
}

void standard(std::string wordType, bool random, std::string language,
              int finCase) {

  csv_fstream readingWordType(wordType);

  int maxLine = countLines(wordType);

  if (Answer::wordAmount == 0) {
    Answer::wordAmount = maxLine - 1;
  };

  int counter = 1;

  if (Answer::random) {
    for (counter; counter <= Answer::wordAmount; counter++) {
      int randomNumber = randomInt(2, maxLine);

      std::cout << std::endl
                << "-+======================================+-" << std::endl;

      if (language == "English" or language == "english") {
        Practise::eng(readingWordType, randomNumber);
      } else {
        Practise::fin(readingWordType, randomNumber, finCase);
      };
    };
  } else {

    int line = 2;

    for (counter; counter <= Answer::wordAmount; counter++) {

      std::cout << "-+======================================+-" << std::endl;

      if (language == "English" or language == "english") {
        Practise::eng(readingWordType, line);
      } else {
        Practise::fin(readingWordType, line, finCase);
      };

      line++;

      if (maxLine < line) {
        readingWordType.seekLine(2);
      };
    };
  };

  readingWordType.close();
}
void verbs(std::string wordType) {

  csv_fstream readingWordType(wordType);

  int maxLine = countLines(wordType);

  if (Answer::wordAmount == 0) {
    Answer::wordAmount = (maxLine - 1) * 6;
  };

  for (int counter = 0; counter < Answer::wordAmount; counter++) {

    int verbInt = randomInt(2, maxLine);
    int pronounInt = randomInt(3, 8);

    std::cout << std::endl
              << "-+======================================+-" << std::endl
              << std::endl;

    std::string pronoun = readingWordType.getElement(1, pronounInt);
    std::string verb = readingWordType.getElement(verbInt, 1);
    std::string verbConj = readingWordType.getElement(verbInt, pronounInt);

    std::string verbConjInput;
    std::cout << "Enter the correct conjugation with the verb " << verb << ": "
              << pronoun << " ";
    std::cin >> verbConjInput;

    if (verbConjInput == verbConj) {
      Score::correct++;
      std::cout << "Yes! :D";
    } else {
      Score::incorrect++;
      std::cout << "No :( The correct word was " << verbConj;
    };

    std::cout << std::endl
              << " (" << Score::correct << " / " << Score::incorrect << ")"
              << std::endl;
  };

  readingWordType.close();
};
} // namespace Practise

// Read Stuff
void readAboutProgram() {
  _fstream readFile("aboutProgram.txt", std::ios::in);

  std::string filler;

  while (getline(readFile, filler)) {
    std::cout << filler << std::endl;
  };

  readFile.close();
};
void readAboutGrammar() {
  int practiseInput;

  std::cout << std::endl
            << "Choose what you want to read about" << std::endl
            << "  Nominatiivi (type 1), " << std::endl
            << "  Genitiivi (type 2), " << std::endl
            << "  Akkusatiivi (type 3)," << std::endl
            << "  Partitiivi (type 4)," << std::endl
            << "  Inessiivi (type 5)," << std::endl
            << "  Preesens (type 6)," << std::endl
            << "  Imperfekti (type 7)," << std::endl;

  while (true) {
    std::cin >> practiseInput;

    if (0 <= practiseInput <= 7) {
      break;
    };

    std::cout << "That's not a valid input, please try again." << std::endl;
  };

  std::cout << std::endl;

  std::vector<std::string> practiseWith = {
      "Nominatiivi", "Genitiivi", "Akkusatiivi", "Partitiivi",
      "Inessiivi",   "Preesens",  "Imperfekti"};

  _fstream file("readAboutFiles/about" +
                    practiseWith.at(practiseInput - 1) + ".txt");

  std::string tempString;

  while (getline(file, tempString)) {
    std::cout << tempString << std::endl;
  };

  file.close();
};

void settingsConfig() {
  bool continuePractising = true;

  while (continuePractising) {

    std::cout << std::endl
              << "-+======================================+-" << std::endl;

    // Questions
    Question::wordType();

    if (Answer::wordTypeInt <= 4) {
      Question::language();
      Question::random();
      if (Answer::language == "Finnish" or Answer::language == "finnish") {
        Question::finCase();
      };
    };

    Question::wordAmount();

    if (Answer::wordTypeInt <= 4) {
      Practise::standard(Answer::wordTypeFile, Answer::random, Answer::language,
                         Answer::finCase);
    } else {
      Practise::verbs(Answer::wordTypeFile);
    };

    double grade = (Score::correct / Answer::wordAmount) * 9 + 1;

    std::cout << "Your grade is " << grade << "/10; "
              << Vector::gradeMessage.at((int)(grade / 2)) << std::endl;

    Score::correct, Score::incorrect = 0;

    std::string continuePractisingInput;
    std::cout << std::endl << "Do you want to continue pracising? ";

    while (true) {

      std::cin >> continuePractisingInput;

      if (vectorChecker(Vector::negative, continuePractisingInput)) {
        continuePractising = false;
        break;
      };

      if (vectorChecker(Vector::positive, continuePractisingInput)) {
        break;
      };

      std::cout << "Sorry, I could not understand that, please try again: "
                << std::endl;
    };

    std::cout << std::endl;

    Score::correct = 0;
    Score::incorrect = 0;
  };
};

int main() {

  while (true) {

    std::cout << std::endl
              << "Tervetuloa, this is a program written in C++ for those who "
                 "want to test their Finnish vocabulary and more!"
              << std::endl
              << "Select what you would like to do:" << std::endl
              << "  Practise (type 1), " << std::endl
              << "  Read about grammar (type 2), " << std::endl
              << "  Read about this very program (type 3)" << std::endl
              << "  Quit (type 0)" << std::endl;

    while (true) {
      std::cin >> Answer::activity;

      if (0 <= Answer::activity <= 3) {
        break;
      };

      std::cout << "That's not a valid input, please try again." << std::endl;
    };

    switch (Answer::activity) {
    case 1:
      settingsConfig();
      break;
    case 2:
      readAboutGrammar();
      break;
    case 3:
      readAboutProgram();
      break;
    };

    if (Answer::activity == 0) {
      break;
    };
  };

  return 0;
};