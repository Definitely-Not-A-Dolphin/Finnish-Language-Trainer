#include "../Headers/randomInt.hpp"
#include "../Headers/_fstream.hpp"
#include "../Headers/trimWhiteSpace.hpp"

namespace Practise {
void single(csv_fstream &file, std::string language, int line = 1, int column = 2) {
  std::string wordEng = trimWhiteSpace(
      // Get English word
      file.getElement(line, 1)
  );
  std::string wordFin = trimWhiteSpace(
      // Get Finnish word
      file.getElement(line, column)
  );

  std::string wordInput;
  if (language == "finnish" or language == "Finnish") {
    std::cout << std::endl << "What is the Finnish word for " << wordEng << "? ";
  } else {
    std::cout << std::endl << "What is the English word for " << wordFin << "? ";
  };
  std::getline(std::cin >> std::ws, wordInput);
  std::cout << std::endl;

  if (language == "finnish" or language == "Finnish") {
    if (trimWhiteSpace(wordInput) == wordFin) {
      std::cout << "Yes! :) " << std::endl;
    } else {
      std::cout << "No :( The correct word was " << wordFin << std::endl;
    };
  } else {
    if (trimWhiteSpace(wordInput) == wordEng) {
      std::cout << "Yes! :) " << std::endl;
    } else {
      std::cout << "No :( The correct word was " << wordEng << std::endl;
    };
  }

  // std::cout << " (" << Score::correct << " / " << Score::incorrect << ")"
  //           << std::endl;
};
void standard(std::string fileName, std::string language, int wordAmount) {

  csv_fstream readFile(fileName);

  int maxLine = countLines(readFile.getFileName());

  if (wordAmount == 0) {
    wordAmount = maxLine - 1;
  };

  int counter = 1;

    for (; counter <= wordAmount; counter++) {
      int randomNumber = randomInt(2, maxLine);

      std::cout << std::endl
                << "-+======================================+-" << std::endl;

      Practise::single(readFile, language, randomNumber);
    };

  readFile.close();
};
/*
void verbs( Komt later wel ) {

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
}; */
void nouns(std::string language, int wordAmount, int finCase, std::string wordTheme) {

  csv_fstream readNoun("wordsFiles/2nouns.csv");

  const int maxLine = countLines("wordsFiles/2nouns.csv");
  int minimal;
  int maximal;
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
      std::cout << "maximal found " << i << std::endl;
      maximal = i - 1;
      break;
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

    Practise::single(readNoun, language, randomNumber, finCase + 2);
  };


  readNoun.close();
};
} // namespace Practise
