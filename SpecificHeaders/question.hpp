#include <array>
#include <iostream>
#include <string>

namespace Question {
int wordAmount() {
  std::cout << std::endl
            << "-+======================================+-" << std::endl;
  int wordAmount;

  std::cout << std::endl << "How many words do you want to practise? ";

  while (!(std::cin >>
           wordAmount)) { // Keep asking until the user enters a valid number
    std::cout << std::endl << "That's not a valid input, please try again. ";
    std::cin.clear();             // Reset input errors
    std::cin.ignore(10000, '\n'); // Remove bad input
  };

  return wordAmount;
}
int wordType() {
  std::cout << std::endl
            << "-+======================================+-" << std::endl;
  int wordTypeInt;

  std::array<std::string, 6> wordTheme = {
      "Adjectives",          "Nouns",           "Numbers", "Pronouns",
      "Verbs present tense", "Verbs past tense"};

  std::cout << std::endl
            << "What theme would you like to practise? " << std::endl;
  for (int i = 1; i <= wordTheme.size(); i++) {
    std::cout << "  " << wordTheme.at(i - 1) << " (type " << i << ")"
              << std::endl;
  }

  while (!(std::cin >> wordTypeInt) && 1 <= wordTypeInt &&
         wordTypeInt <= 6) { // Keep asking until the user enters a valid number
    std::cout << std::endl << "That's not a valid input, please try again. ";
    std::cin.clear();             // Reset input errors
    std::cin.ignore(10000, '\n'); // Remove bad input
  };

  return wordTypeInt;
}
std::string wordTheme() {
  std::cout << std::endl
            << "-+======================================+-" << std::endl;
  int wordThemeInt;

  std::array<std::string, 10> wordTheme = {
      "general", "places",    "nature",  "body",  "time",
      "people",  "countries", "digital", "other", "any"};

  std::cout << std::endl
            << "What theme would you like to practise? " << std::endl;
  for (int i = 1; i <= wordTheme.size(); i++) {
    std::cout << "  " << wordTheme.at(i - 1) << " (type " << i << ")"
              << std::endl;
  }

  while (!(std::cin >> wordThemeInt) && 1 <= wordThemeInt &&
         wordThemeInt <=
             10) { // Keep asking until the user enters a valid number
    std::cout << std::endl << "That's not a valid input, please try again. ";
    std::cin.clear();             // Reset input errors
    std::cin.ignore(10000, '\n'); // Remove bad input
  };

  return wordTheme.at(wordThemeInt - 1);
}
std::string language() {
  std::string language;

  std::cout << std::endl
            << "In what language would you like to practise the words "
               "(Finnish / English)? ";

  while (true) {
    std::getline(std::cin >> std::ws, language);

    if (language == "Finnish" || language == "finnish") {
      return "finnish";
    };
    if (language == "English" || language == "english") {
      return "english";
    };

    std::cout << std::endl
              << "Sorry, I could not understand that. Please try again:"
              << std::endl;
  };
};
int finCase() {
  std::cout << std::endl
            << "-+======================================+-" << std::endl;
  int finCaseInt;

  std::cout << std::endl
            << "What case would you like to practise? " << std::endl
            << "  Nominatiivi (type 1), " << std::endl
            << "  Genitiivi (type 2), " << std::endl
            << "  Partitiivi (type 3), " << std::endl
            << "  Akkusatiivi (type 4), " << std::endl
            << "  Inessiivi (type 5)" << std::endl;

  while (!(std::cin >> finCaseInt) && 1 <= finCaseInt &&
         finCaseInt <= 5) { // Keep asking until the user enters a valid number
    std::cout << std::endl << "That's not a valid input, please try again. ";
    std::cin.clear();             // Reset input errors
    std::cin.ignore(10000, '\n'); // Remove bad input
  };

  return finCaseInt;
};
} // namespace Question
