#include <string>

std::string trimWhiteSpace(std::string input) {
  while (input[0] == ' ') {
    input.erase(input.begin());
  };

  while (input[input.size() - 1] == ' ') {
    input.pop_back();
  };

  return input;
};