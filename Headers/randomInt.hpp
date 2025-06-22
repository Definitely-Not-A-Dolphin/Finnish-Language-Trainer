#include <random>

int randomInt(int lower, int upper) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(lower, upper);

  int randomX = dis(gen);

  return randomX;
}
