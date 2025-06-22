#include <iostream>
#include <array>
#include <string>

namespace Question {
int wordType() {
  int wordTypeInt;

  std::cout << std::endl
            << "What type of word would you like to practise? " << std::endl
            << "  Adjectives (type 1), " << std::endl
            << "  Nouns (type 2), " << std::endl
            << "  Numbers (type 3), " << std::endl
            << "  Pronouns (type 4), " << std::endl
            << "  Verbs present tense (type 5), " << std::endl
            << "  Verbs past tense (type 6), " << std::endl;

  while (true) {
    std::cin >> wordTypeInt;

    if (1 <= wordTypeInt && wordTypeInt <= 6) {
      return wordTypeInt;
    };

    std::cout << std::endl
              << "Sorry, I could not understand that. Please re-enter your "
                 "answer."
              << std::endl;
  };
}
std::string wordTheme() {
  int wordThemeInt;

  std::array<std::string, 9> wordTheme = {"general",   "places",  "nature",
                                          "body",      "time",    "people",
                                          "countries", "digital", "other"};

  std::cout << std::endl
            << "What theme would you like to practise? " << std::endl
            << "  General (type 1), " << std::endl
            << "  Places (type 2), " << std::endl
            << "  Nature (type 3), " << std::endl
            << "  Body (type 4), " << std::endl
            << "  Time (type 5), " << std::endl
            << "  Places (type 6), " << std::endl
            << "  Countries (type 7), " << std::endl
            << "  Digital (type 8), " << std::endl
            << "  Other (type 9), " << std::endl;

  while (true) {
    std::cin >> wordThemeInt;

    if (1 <= wordThemeInt && wordThemeInt <= 9) {
      return wordTheme.at(wordThemeInt - 1);
    };

    std::cout << std::endl
              << "Sorry, I could not understand that. Please re-enter your "
                 "answer."
              << std::endl;
  };
}
std::string language() {
  std::string language;

  std::cout << std::endl
            << "In what language would you like to practise the words "
               "(Finnish / English)? ";

  while (true) {
    std::getline(std::cin >> std::ws, language);

    if (language == "Finnish" || language == "finnish") { return "finnish"; };
    if (language == "English" || language == "english") { return "english"; };

    std::cout << std::endl
              << "Sorry, I could not understand that. Please try again:"
              << std::endl;
  };
}
int finCase() {
  int finCaseInt;

  std::cout << std::endl
            << "What case would you like to practise? " << std::endl
            << "  Nominatiivi (type 1), " << std::endl
            << "  Genitiivi (type 2), " << std::endl
            << "  Partitiivi (type 3), " << std::endl
            << "  Akkusatiivi (type 4), " << std::endl
            << "  Inessiivi (type 5)" << std::endl;

  while (true) {

    std::cin >> finCaseInt;

    if (1 <= finCaseInt && finCaseInt <= 5) {
      return finCaseInt;
    };

    std::cout << std::endl
              << "That's not a valid input, please try again." << std::endl;
  }
}
int wordAmount() {
  int wordAmount;

  std::cout << std::endl
            << "How many words do you want to practise? " << std::endl;

  while (true) {
    std::cin >> wordAmount;

    if (0 <= wordAmount) {
      return wordAmount;
    };

    std::cout << std::endl
              << "That's not a valid input, please try again." << std::endl;
  };
}
} // namespace Question
