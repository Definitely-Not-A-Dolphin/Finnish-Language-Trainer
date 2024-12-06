#include "parser.hpp"
#include <string>
#include <iostream>

string getFinnish(string wordEnglish);

int main() {
  CsvParser csv("english_finnish.csv");

  for (std::string i : csv.get_mathching_finnish(
           "star")) { // for-loop because there could be more than one
                      // translation of a word.
    std::cout << "Match found: " << i << std::endl;
  }
}

string getFinnish(string wordEnglish){
  
}