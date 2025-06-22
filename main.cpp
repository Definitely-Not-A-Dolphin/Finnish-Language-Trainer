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

  while (true) {
    std::cout << "Here we go again: V5.0.0" << std::endl;

    std::cout << std::endl
              << "-+======================================+-" << std::endl;
    Answer::wordAmount = Question::wordAmount();

    std::cout << std::endl
              << "-+======================================+-" << std::endl;
    Answer::wordType = Question::wordType();
    Answer::readFromFile = "wordsFiles/" +
                           dataStruct::wordTypeFile.at(Answer::wordType - 1) +
                           ".csv";

    if (Answer::wordType == 5 || Answer::wordType == 6) {
      std::cout << std::endl
                << "-+======================================+-" << std::endl;
      Practise::verbs(Answer::readFromFile, Answer::wordAmount);
    }

    std::cout << std::endl
              << "-+======================================+-" << std::endl;
    Answer::language = Question::language();
    if (Answer::language == "english") {
      std::cout << std::endl
                << "-+======================================+-" << std::endl;
      Answer::finCase = Question::finCase();
    }
    if (Answer::wordType == 2) {
      Answer::wordThemeString = Question::wordTheme();
      Practise::nouns(Answer::wordAmount, Answer::language,
                      Answer::wordThemeString, Answer::finCase);
      continue;
    };

    Practise::standard(Answer::readFromFile, Answer::language,
                       Answer::wordAmount, Answer::finCase);
  }

  return 0;
}
