#ifndef PARSER_HPP
#define PARSER_HPP

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class CsvParser {
private:
  std::ifstream csvFile;
  std::vector<std::string> *english_column = new std::vector<std::string>();
  std::vector<std::string> *finnish_column = new std::vector<std::string>();

  void init_vector() { // Put the data of the csv into the vectors.
    std::string line;

    while (std::getline(csvFile, line)) {
      std::stringstream ss(line);
      std::string cell;
      int col = 0;

      while (std::getline(ss, cell, ',')) {
        if (col == 0) {
          english_column->push_back(cell);
        } else if (col == 1) {
          finnish_column->push_back(cell);
        }
        col++;
      }
    }
    english_column->erase(english_column->begin());
    finnish_column->erase(finnish_column->begin());
  }

public:
  CsvParser(const std::string &filename) {
    csvFile = std::ifstream(filename);
    if (!csvFile.is_open())
      throw std::runtime_error("Could not open file");
    init_vector();
  }

  ~CsvParser() {
    delete english_column;
    delete finnish_column;
  }

  std::vector<std::string> get_mathching_finnish(const std::string &english) {
    std::vector<std::string> output;

    for (int i = 0; i < english_column->size(); i++) {
      if ((*english_column)[i] == english) {
        output.push_back((*finnish_column)[i]);
      }
    }
    return output;
  }

  std::vector<std::string> get_mathching_english(const std::string &finnish) {
    std::vector<std::string> output;

    for (int i = 0; i < finnish_column->size(); i++) {
      if ((*finnish_column)[i] == finnish) {
        output.push_back((*english_column)[i]);
      }
    }
    return output;
  }
};

#endif