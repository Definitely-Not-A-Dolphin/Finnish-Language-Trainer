#include <array>
#include <fstream>
#include <iostream>

void readGrammer() {
  int whatToRead;
  std::array<std::string, 5> things = {
      "Nominatiivi", "Genitiivi", "Akkusatiivi", "Partitiivi", "Inessiivi"};

  std::cout << "What would you like to read about?" << std::endl;
  for (int i = 0; i <= things.size() - 1; i++) {
    std::cout << "\t" << things[i] << " (type " << i + 1 << ")" << std::endl;
  };
  while (!(std::cin >> whatToRead || (1 <= whatToRead && whatToRead <= 5))) {
    std::cout << std::endl << "That's not a valid input, please try again. ";
    std::cin.clear();
    std::cin.ignore(10000, '\n');
  };

  std::string basepath = "../readAboutFiles/";
}
