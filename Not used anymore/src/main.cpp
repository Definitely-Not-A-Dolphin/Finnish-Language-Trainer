#include "parser.hpp"
#include <iostream>
#include <string>

CsvParser csv("english_finnish.csv");

std::string getFinnish(std::string wordEnglish);
std::string getEnglish(std::string wordFinnish);

    int main() {
  std::cout << getFinnish("nice") << std::endl; 
  
  std::cout << getEnglish("tähti") << std::endl;

  return 0;
}

std::string getFinnish(std::string wordEnglish) {
  return (csv.get_mathching_finnish(wordEnglish))[0];
}

std::string getEnglish(std::string wordFinnish) {
  return (csv.get_mathching_english(wordFinnish));
}