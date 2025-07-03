#include "../Headers/_fstream.hpp"
#include "../Headers/randomInt.hpp"
#include "../Headers/trimWhiteSpace.hpp"

namespace Score {
int correct;
int incorrect;
} // namespace Score

namespace Practise {
void fin(csv_fstream &file, int line = 1, int finCase = 2) {
  std::string wordEng = trimWhiteSpace(
      // Get English word
      file.getElement(line, 1));
  std::string wordFin = trimWhiteSpace(
      // Get Finnish word
      file.getElement(line, finCase + 1));

  std::cout << wordEng << std::endl << wordFin << std::endl;

  std::string wordInput;
  std::cout << std::endl << "What is the Finnish word for " << wordEng << "? ";

  std::getline(std::cin >> std::ws, wordInput);
  std::cout << std::endl;

  if (trimWhiteSpace(wordInput) == wordFin) {
    std::cout << "Yes! :) " << std::endl;
    Score::correct++;
  } else {
    std::cout << "No :( The correct word was " << wordFin << std::endl;
    Score::incorrect++;
  };

  // std::cout << " (" << Score::correct << " / " << Score::incorrect << ")"
  //           << std::endl;
};
void eng(csv_fstream &file, int line = 1, bool noun = false) {
  std::string wordEng = trimWhiteSpace(
      // Get English word
      file.getElement(line, 1));

  std::string wordFin = trimWhiteSpace(
      // Get Finnish word
      file.getElement(line, 2));

  // Take the next words if nouns are being practised
  if (noun) {
    wordFin = trimWhiteSpace(
        // Get Finnish word
        file.getElement(line, 3));
  }

  std::cout << wordFin << std::endl << wordEng << std::endl;

  std::string wordInput;
  std::cout << std::endl << "What is the English word for " << wordFin << "? ";

  std::getline(std::cin >> std::ws, wordInput);
  std::cout << std::endl;

  if (trimWhiteSpace(wordInput) == wordEng) {
    std::cout << "Yes! :) " << std::endl;
    Score::correct++;
  } else {
    std::cout << "No :( The correct word was " << wordEng << std::endl;
    Score::incorrect++;
  };

  // std::cout << " (" << Score::correct << " / " << Score::incorrect << ")"
  //           << std::endl;
};
double standard(std::string fileName, std::string language, int wordAmount,
                int finCase = 2) {

  csv_fstream readFile(fileName);

  const int maxLine = countLines(fileName);

  if (wordAmount == 0) {
    wordAmount = maxLine - 1;
  };

  int counter = 1;

  for (; counter <= wordAmount; counter++) {
    int randomNumber = randomInt(2, maxLine);

    std::cout << std::endl
              << "-+======================================+-" << std::endl;

    if (language == "finnish") {
      Practise::fin(readFile, randomNumber, finCase);
    } else {
      Practise::eng(readFile, randomNumber);
    };
  };

  readFile.close();

  return ((double)Score::correct) / ((double)wordAmount);
};
double verbs(std::string fileName, int wordAmount) {

  csv_fstream readingWordType(fileName);
  const int maxLine = countLines(fileName);

  if (wordAmount == 0) {
    wordAmount = (maxLine - 1) * 6;
  };

  for (int counter = 1; counter <= wordAmount; counter++) {

    int verbInt = randomInt(2, maxLine);
    int pronounInt = randomInt(3, 8);

    std::cout << std::endl
              << "-+======================================+-" << std::endl
              << std::endl;

    std::string pronoun =
        trimWhiteSpace(readingWordType.getElement(1, pronounInt));
    std::string verb = trimWhiteSpace(readingWordType.getElement(verbInt, 1));
    std::string verbConj =
        trimWhiteSpace(readingWordType.getElement(verbInt, pronounInt));

    std::string verbConjInput;
    std::cout << "Enter the correct conjugation with the verb " << verb << ": "
              << pronoun << " ";
    std::cin >> verbConjInput;

    if (verbConjInput == verbConj) {
      std::cout << "Yes! :D" << std::endl;
    } else {
      std::cout << "No :( The correct word was " << verbConj << std::endl;
    };
  };

  readingWordType.close();

  return ((double)Score::correct) / ((double)wordAmount);
};
double nouns(int wordAmount, std::string language,
             std::string wordTheme = "any", int finCase = 2) {

  csv_fstream readNoun("wordsFiles/2nouns.csv");
  const int maxLine = countLines("wordsFiles/2nouns.csv");

  int minimal = 2;
  int maximal = maxLine;

  if (wordTheme != "any") {
    std::string thing;
    for (int i = 2; i <= maxLine - 1; i++) {
      if (trimWhiteSpace(readNoun.getElement(i, 2)) == wordTheme) {
        std::cout << "minimal found " << i << std::endl;
        minimal = i;
        break;
      }
    }

    for (int i = minimal; i <= maxLine - 1; i++) {
      if (trimWhiteSpace(readNoun.getElement(i, 2)) != wordTheme) {
        std::cout << "maximal found " << i - 1 << std::endl;
        maximal = i - 1;
        break;
      }
    }
  }

  if (wordAmount == 0) {
    wordAmount = maxLine - 1;
  };

  int counter = 1;

  for (; counter <= wordAmount; counter++) {
    int randomNumber = randomInt(minimal, maximal);
    std::cout << std::endl
              << "-+======================================+-" << std::endl;

    if (language == "finnish") {
      Practise::fin(readNoun, randomNumber, finCase + 1);
    } else {
      Practise::eng(readNoun, randomNumber, true);
    };
  };

  readNoun.close();

  return ((double)Score::correct) / ((double)wordAmount);
};
} // namespace Practise
