#include "Headers/datastructChecker.hpp"
#include "SpecificHeaders/practise.hpp"
#include "SpecificHeaders/question.hpp"

#include <array>
#include <iostream>
#include <vector>

namespace Answer {
int finCase;
std::string finCaseString;
int wordTheme;
std::string wordThemeString;

int wordType;
std::string readFromFile;

int wordAmount;
std::string language;

std::string continueing;
} // namespace Answer

double grade;

namespace dataStruct {
std::vector<std::string> negative = {"No",  "no",  "Nah", "nah", "Nei",
                                     "nei", "Nee", "nee", "N",   "n"};
std::vector<std::string> positive = {"Yes", "yes", "Yeah", "yeah", "Yea", "yea",
                                     "Ye",  "ye",  "Ja",   "ja",   "Y",   "y"};
std::vector<std::string> language = {"Finnish", "finnish", "English",
                                     "english"};
std::vector<std::string> wordTypeFile = {
    "1adjectives", "2nouns",          "3numbers",
    "4pronouns",   "verbs/5preesens", "verbs/6imperfekti"};
std::vector<std::string> wordTheme = {
    "general", "places",    "nature",  "body",  "time",
    "people",  "countries", "digital", "other", "any"};
std::vector<std::string> gradeMessage = {
    "This is too hard for you. Have you considered Swedish?",
    "Were you even trying?",
    "I would consider that not very good.",
    "It's okay, could be better.",
    "Solid grade!",
    "Wow, good job!"};
} // namespace dataStruct

int main() {

  std::cout << "Here we go again: V5.0.0" << std::endl << std::endl;

  while (true) {
    Answer::wordAmount = Question::wordAmount();

    Answer::wordType = Question::wordType();
    Answer::readFromFile = "wordsFiles/" +
                           dataStruct::wordTypeFile.at(Answer::wordType - 1) +
                           ".csv";

    if (Answer::wordType == 5 || Answer::wordType == 6) {
      grade = Practise::verbs(Answer::readFromFile, Answer::wordAmount);
      continue;
    };

    Answer::language = Question::language();
    if (Answer::language == "finnish") {
      Answer::finCase = Question::finCase();
    };

    if (Answer::wordType == 2) {
      Answer::wordThemeString = Question::wordTheme();
      grade = Practise::nouns(Answer::wordAmount, Answer::language,
                              Answer::wordThemeString, Answer::finCase);
      continue;
    };

    grade = Practise::standard(Answer::readFromFile, Answer::language,
                               Answer::wordAmount, Answer::finCase) * 10;

    std::cout << "Your grade is " << grade << "/10"
              << " " << dataStruct::gradeMessage.at((int)(grade / 2))
              << std::endl
              << std::endl
              << "Would you like to continue practising? ";

    while (true) {
      std::getline(std::cin >> std::ws, Answer::continueing);

      if (vectorChecker(dataStruct::negative, Answer::continueing) ||
          vectorChecker(dataStruct::positive, Answer::continueing)) {
        break;
      };
    };

    if (vectorChecker(dataStruct::negative, Answer::continueing)) {
      break;
    };

    grade = 0;
    Answer::continueing = "";
  };

  return 0;
}
