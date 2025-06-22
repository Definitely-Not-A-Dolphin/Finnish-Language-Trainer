#include "Headers/datastructChecker.hpp"

#include "SpecificHeaders/practise.hpp"
#include "SpecificHeaders/question.hpp"

#include <array>
#include <vector>
#include <iostream>

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

namespace dataStruct {
std::vector<std::string> negative = {"No",  "no",  "Nah", "nah", "Nei",
                                        "nei", "Nee", "nee", "N",   "n"};
std::vector<std::string> positive = {"Yes", "yes", "Yeah", "yeah",
                                        "Yea", "yea", "Ye",   "ye",
                                        "Ja",  "ja",  "Y",    "y"};
std::vector<std::string> language = {"Finnish", "finnish", "English",
                                       "english"};
std::vector<std::string> wordTypeFile = {
    "1adjectives", "2nouns",          "3numbers",
    "4pronouns",   "verbs/5preesens", "verbs/6imperfekti"};
std::vector<std::string> wordTheme = {"general",   "places",  "nature",
                                        "body",      "time",    "people",
                                        "countries", "digital", "other"};
std::vector<std::string> gradeMessage = {
    "This is too hard for you. Have you considered Swedish?",
    "Were you even trying?",
    "I would consider that not very good.",
    "It's okay, could be better.",
    "Solid grade!",
    "Wow, good job!"};
} // namespace dataStruct

int main() {

  std::cout << "Here we go again: V5.0.0" << std::endl;

  Answer::wordAmount = Question::wordAmount();
  Answer::wordType = Question::wordType();
  Answer::readFromFile = "wordsFiles/" + dataStruct::wordTypeFile.at(Answer::wordType - 1) + ".csv";
  Answer::language = Question::language();

  Practise::standard(Answer::readFromFile, Answer::language, Answer::wordAmount);

  return 0;
}
