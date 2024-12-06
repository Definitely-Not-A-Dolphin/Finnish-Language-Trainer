#include "parser.hpp"
#include <iostream>
#include <string>

CsvParser csv("english_finnish.csv");

std::string getFinnish(std::string wordEnglish);

int main() {

  std::cout << getFinnish("nice") << std::endl;

}

std::string getFinnish(std::string wordEnglish) {

  for (std::string i : csv.get_mathching_finnish(wordEnglish)) {
    return i;
  }
}