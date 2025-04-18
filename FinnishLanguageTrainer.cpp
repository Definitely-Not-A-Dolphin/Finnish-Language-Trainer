#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// Headers
//       "Headers/generalFileStream.cpp"
#include "Headers/csvFileStream.cpp"
#include "Headers/datastructChecker.cpp"
#include "Headers/randomInt.cpp"

struct {
  int activity;
  std::string wordTypeFile;
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
  std::vector<std::string> negative = {"No",  "no",  "Nah", "nah",
                                       "Nei", "nei", "Nee", "nee"};
  std::vector<std::string> positive = {"Yes", "yes", "Yeah", "yeah", "Yea",
                                       "yea", "Ye",  "ye",   "Ja",   "ja"};
  std::vector<std::string> language = {"Finnish", "finnish", "English",
                                       "english"};
  std::vector<std::string> cases = {"Nominatiivi", "Genitiivi",   "Akkusatiivi",
                                    "Partitiivi",  "nominatiivi", "genitiivi",
                                    "akkusatiivi", "partitiivi"};
  std::vector<std::string> gradeMessage = {
      "This is too hard for you. Have you considered Swedish?",
      "Were you even trying?",
      "I would consider that not very good.",
      "It's okay, could be better.",
      "Solid grade!",
      "Wow, good job!"};
} Vector;

// Soon-to-be Headers

// Get functions
void getEngPractise(std::fstream &file, int line);
void getFinPractise(std::fstream &file, int line, int finCase);
std::string getEng(std::fstream &file, int line);
std::string getFin(std::fstream &file, int line, int finCase);

// Practice functions
void standardPractise(std::string wordType, bool random, std::string language,
                      int finCase);
void verbsPractise(std::string wordType);

// Questions
void wordTypeQuestion() {

  std::cout << std::endl
            << "What type of word would you like to practise? " << std::endl
            << "  Adjectives (type 1), " << std::endl
            << "  Nouns (type 2), " << std::endl
            << "  Numbers (type 3), " << std::endl
            << "  Pronouns (type 4), " << std::endl
            << "  Verbs present tense (type 5), " << std::endl
            << "  Verbs past tense (type 6), " << std::endl;

  while (true) {
    std::cin >> Answer.wordTypeInt;

    if (1 <= Answer.wordTypeInt <= 6) {
      break;
    };

    std::cout << std::endl
              << "Sorry, I could not understand that. Please re-enter your "
                 "answer."
              << std::endl;
  };

  Answer.wordTypeFile = "wordsFiles";

  switch (Answer.wordTypeInt) {
  case 1:
    Answer.wordTypeFile = "wordsFiles/1adjectives.csv";
    break;
  case 2:
    Answer.wordTypeFile = "wordsFiles/2nouns.csv";
    break;
  case 3:
    Answer.wordTypeFile = "wordsFiles/3numbers.csv";
    break;
  case 4:
    Answer.wordTypeFile = "wordsFiles/4pronouns.csv";
    break;
  case 5:
    Answer.wordTypeFile = "wordsFiles/verbs/5preesens.csv";
    break;
  case 6:
    Answer.wordTypeFile = "wordsFiles/verbs/6imperfekti.csv";
    break;
  };
}
void languageQuestion() {
  while (true) {
    std::cout << std::endl
              << "In what language would you like to practise the words "
                 "(Finnish / English)? ";
    std::getline(std::cin >> std::ws, Answer.language);

    if (vectorChecker(Vector.language, Answer.language)) {
      break;
    };

    std::cout << std::endl
              << "Sorry, I could not understand that. Please try again:"
              << std::endl;
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
    };

    std::cout << std::endl
              << "That's not a valid input, please try again." << std::endl;
  }
}
void wordAmountQuestion() {
  while (true) {

    if (Answer.wordTypeFile == "wordsFiles/verbs/preesens.csv" or
        Answer.wordTypeFile == "wordsFiles/verbs/imperfekti.csv") {
      std::cout << std::endl
                << "How many words do you want to practise? " << std::endl;
    } else {
      std::cout << std::endl
                << "How many words do you want to practise (there are "
                << countLines(Answer.wordTypeFile) - 1
                << " in the selected category)? " << std::endl;
    }

    std::cin >> Answer.wordAmount;

    if (Answer.wordAmount >= 0) {
      break;
    };

    std::cout << "That's not a valid input, please try again." << std::endl;
  };
}
void randomQuestion() {

  std::string randomInput;
  std::cout << std::endl << "Would you like to randomise the word order? ";
  Answer.random = true;

  while (true) {

    std::getline(std::cin >> std::ws, randomInput);

    if (vectorChecker(Vector.positive, randomInput)) {
      break;
    };

    if (vectorChecker(Vector.negative, randomInput)) {
      Answer.random = false;
      break;
    };

    randomInput = "";

    std::cout << std::endl
              << "Sorry, I could not understand that. Please try again:"
              << std::endl;
  };
}

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

void settingsConfig() {
  bool continuePractising = true;

  while (continuePractising) {

    while (continuePractising) {
      std::cout << std::endl
                << "-+======================================+-" << std::endl;

      // Questions
      wordTypeQuestion();

      if (Answer.wordTypeInt <= 4) {
        languageQuestion();
        randomQuestion();
        if (Answer.language == "Finnish" or Answer.language == "finnish") {
          caseQuestion();
        };
      };

      wordAmountQuestion();

      if (Answer.wordTypeInt <= 4) {
        standardPractise(Answer.wordTypeFile, Answer.random, Answer.language,
                         Answer.finCase);
      } else {
        verbsPractise(Answer.wordTypeFile);
      };

      double grade = (Score.correct / Answer.wordAmount) * 9 + 1;

      std::cout << "Your grade is " << grade << "/10; "
                << Vector.gradeMessage.at((int)(grade / 2)) << std::endl;

      Score.correct, Score.incorrect = 0;

      std::string continuePractisingInput;
      std::cout << std::endl << "Do you want to continue pracising? ";

      while (true) {

        std::cin >> continuePractisingInput;

        if (vectorChecker(Vector.negative, continuePractisingInput)) {
          continuePractising = false;
          break;
        };

        if (vectorChecker(Vector.positive, continuePractisingInput)) {
          break;
        };

        std::cout << "Sorry, I could not understand that, please try again: "
                  << std::endl;
      };

      std::cout << std::endl;

      Score.correct = 0;
      Score.incorrect = 0;
    };
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
      std::cin >> Answer.activity;

      if (0 <= Answer.activity <= 3) {
        break;
      };

      std::cout << "That's not a valid input, please try again." << std::endl;
    };

    switch (Answer.activity) {
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

    if (Answer.activity == 0) {
      break;
    };
  };

  return 0;
};

void standardPractise(std::string wordType, bool random, std::string language,
                      int finCase) {

  std::fstream readingWordType(wordType);

  int maxLine = countLines(wordType);

  if (Answer.wordAmount == 0) {
    Answer.wordAmount = maxLine - 1;
  };

  // Used for both random and non-random practise
  int counter = 0;

  if (Answer.random) {
    for (counter = 1; counter <= Answer.wordAmount; counter++) {
      int randomNumber = randomInt(2, maxLine);

      std::cout << std::endl
                << "-+======================================+-" << std::endl;

      if (language == "English" or language == "english") {
        getEngPractise(readingWordType, randomNumber);
      } else {
        getFinPractise(readingWordType, randomNumber, finCase);
      };
    };
  } else {

    int line = 2;

    while (counter != Answer.wordAmount) {

      std::cout << "-+======================================+-" << std::endl;

      if (language == "English" or language == "english") {
        getEngPractise(readingWordType, line);
      } else {
        getFinPractise(readingWordType, line, finCase);
      };

      counter++;
      line++;

      if (maxLine < line) {
        seekLine(readingWordType, 2);
      };
    };
  };

  readingWordType.close();
}

void verbsPractise(std::string wordType) {

  std::fstream readingWordType(wordType);

  int maxLine = countLines(wordType);

  if (Answer.wordAmount == 0) {
    Answer.wordAmount = (maxLine - 1) * 6;
  };

  int counter = 0;

  while (counter != Answer.wordAmount) {

    int verbInt = randomInt(2, maxLine);
    int pronounInt = randomInt(3, 8);

    std::cout << std::endl
              << "-+======================================+-" << std::endl
              << std::endl;

    std::string pronoun = getElement(readingWordType, 1, pronounInt);
    std::string verb = getElement(readingWordType, verbInt, 1);
    std::string verbConj = getElement(readingWordType, verbInt, pronounInt);

    std::string verbConjInput;
    std::cout << "Enter the correct conjugation with the verb " << verb << ": "
              << pronoun << " ";
    std::cin >> verbConjInput;

    if (verbConjInput == verbConj) {
      Score.correct++;
      std::cout << "Yes! :D";
    } else {
      Score.incorrect++;
      std::cout << "No :( The correct word was " << verbConj;
    };

    std::cout << std::endl
              << " (" << Score.correct << " / " << Score.incorrect << ")"
              << std::endl;

    counter++;
  };

  readingWordType.close();
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