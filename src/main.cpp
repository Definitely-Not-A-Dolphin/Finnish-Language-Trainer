#include "parser.hpp"
#include <string>
#include <iostream>

std::string getFinnish(std::string wordEnglish);

int main() {
    
  std::cout << getFinnish("to be");

}

std::string getFinnish(std::string wordEnglish){
  CsvParser csv("english_finnish.csv");

  for (std::string i : csv.get_mathching_finnish(
           wordEnglish)) {
    return i;
  }
}