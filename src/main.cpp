#include "parser.hpp"
#include <iostream>

int main() {
  CsvParser csv("english_finnish.csv");

  for (std::string i : csv.get_mathching_finnish(
           "nice")) { // for-loop because there could be more than one
                      // translation of a word.
    std::cout << "Match found: " << i << std::endl;
  }
}