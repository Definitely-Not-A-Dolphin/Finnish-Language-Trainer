#include <fstream>
#include <iostream>
#include <string>
#include <vector>

bool exists(std::string fileName) {
  std::ifstream readFile(fileName);

  if (!readFile.is_open()) {
    // std::cerr << fileName << " does not exist!" << std::endl;
    readFile.close();
    return false;
  };

  readFile.close();

  return true;
};

// I am going to revisit this function after I learn
// more about strings in C
bool remove(std::string fileName) {
  int length = fileName.size();

  char *fileNameArray = new char[length];

  for (int k = 0; k <= length - 1; k++) {
    fileNameArray[k] = fileName.at(k);
  };

  remove(fileNameArray);

  delete[] fileNameArray;

  std::ifstream checking(fileName);

  if (checking.is_open()) {
    checking.close();
    return false;
  };

  return true;
};

bool create(std::string fileName) {
  std::ofstream readFile(fileName);

  if (!readFile.is_open()) {
    // std::cerr << "File creation unsuccesfull; could not create " << fileName
    //          << "." << std::endl;
    return false;
  };

  readFile.close();

  return true;
};

int fileSize(std::string fileName) {
  std::ifstream readFile(fileName);

  std::string tmp;
  int size = 0;

  while (std::getline(readFile, tmp)) {
    size += tmp.size() + 1;
  };

  readFile.close();

  return size;
};

int countLines(std::string fileName) {
  std::fstream file(fileName);

  int lineCounter = 0;
  std::string output;

  while (getline(file, output)) {
    lineCounter++;
  };

  file.close();

  return lineCounter;
};

struct _fstream : std::fstream {
  std::string fileName;

  _fstream(std::string fileNameIn,
           ios_base::openmode mode = ios_base::in | ios_base::out)
      : std::fstream(fileNameIn, mode) {
    fileName = fileNameIn;
  };

  bool open(std::string fileNameIn,
            ios_base::openmode mode = ios_base::in | ios_base::out) {
    std::fstream::open(fileNameIn, mode);
    fileName = fileNameIn;
    return !is_open();
  };

  bool seekLine(int k) {
    if (!is_open()) {
      // std::cerr << "File is not open!" << std::endl;
      return false;
    };

    if (countLines(fileName) < k) {
      return false;
    };

    seekg(0, std::fstream::beg);

    std::string line;
    for (int currentLine = 1; currentLine < k; currentLine++) {
      std::getline(*this, line);
    };

    return true;
  };

  bool copyTo(std::string toFile) {
    std::ofstream writeToFile(toFile, std::fstream::app);

    if (!writeToFile.is_open()) {
      return false;
    };

    char c;
    for (int i = 1; i <= fileSize(fileName); i++) {
      c = get();
      writeToFile << c;
    };

    writeToFile.close();

    return true;
  };

  bool clearPart(int start, int final) {
    if (!is_open()) {
      // std::cerr << "File is not open!" << std::endl;
      return false;
    };

    const int startPosition = tellg();

    std::string fileString = "";

    seekg(0);

    char c;
    for (int i = 1; i <= fileSize(fileName); i++) {
      c = get();
      if (start <= i && i <= final) {
        continue;
      };

      fileString.push_back(c);
    };

    close();
    remove(fileName);
    // Remove the current file from the system

    create(fileName);
    open(fileName);

    *this << fileString;

    seekg(startPosition);

    return true;
  };

  bool replacePart(int start, int final, std::string message) {
    if (!is_open()) {
      // std::cerr << "File is not open!" << std::endl;
      return false;
    };

    seekg(0, std::fstream::beg);

    std::string firstPart;
    std::string secondPart;

    char c;
    for (int k = 1; k <= fileSize(fileName); k++) {
      c = get();
      if (k < start) {
        firstPart.push_back(c);
        continue;
      };
      if (final < k) {
        secondPart.push_back(c);
      };
    };

    close();
    remove(fileName);
    // Remove the current file from the system

    create(fileName);
    open(fileName);

    *this << firstPart << message << secondPart;

    return true;
  };
};

struct csv_fstream : _fstream {
  using _fstream::_fstream;

  bool seekElement(int row, int column) {
    if (!is_open()) {
      // std::cerr << "File is not open!" << std::endl;
      return false;
    };

    if (!seekLine(row)) {
      // std::cerr << "Element does not exist" << std::endl;
      return false;
    };

    std::string output;

    for (int k = 1; k < column; k++) {
      std::getline(*this, output, ',');
      if (output[0] == '\n') {
        // std::cerr << "Element does not exist" << std::endl;
        return false;
      };
    };

    return true;
  };

  std::string getElement(int row, int column) {
    if (!is_open()) {
      // std::cerr << "File is not open!" << std::endl;
      return "";
    };

    if (!seekElement(row, column)) {
      // std::cerr << "Element does not exist" << std::endl;
      return "";
    };

    std::string output;
    std::getline(*this, output, ',');

    return output;
  };

  bool clearElement(int row, int column) {
    if (!is_open()) {
      std::cerr << "File is not open!" << std::endl;
      return false;
    };

    seekElement(row, column);
    const int startPosition = tellg();

    std::string tmp;
    std::getline(*this, tmp, ',');

    const int finalPosition = tellg();

    clearPart(startPosition + 1, finalPosition - 1);

    return true;
  };

  bool replaceElement(int row, int column, std::string message) {
    if (!is_open()) {
      std::cerr << "File is not open!" << std::endl;
      return false;
    };

    seekElement(row, column);
    const int start = tellg();

    std::string tmp;
    std::getline(*this, tmp, ',');
    const int final = tellg();

    replacePart(start + 1, final - 1, "thing");

    return true;
  };

  std::vector<std::vector<std::string>> parseToVector() {

    std::vector<std::vector<std::string>> container = {};
    std::vector<std::string> contained = {};
    std::string output = "";

    int amountOfLines = countLines(fileName);
    for (int i = 1; i <= amountOfLines; i++) {
      seekLine(i);
      while (true) {
        std::getline(*this, output, ',');
        if (output[0] == '\n') {
          break;
        };
        contained.push_back(output);
      };

      container.push_back(contained);
      contained.clear();
    };

    return container;
  };
};
