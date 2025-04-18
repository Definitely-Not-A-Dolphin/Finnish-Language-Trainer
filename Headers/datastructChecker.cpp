#include <list>
#include <vector>

/*
I will get this piece of code working, it is supposed to be the like the others,
but compatible with any datastructuretype

template <typename searchedForType>
bool vectorChecker(std::vector<searchedForType> searchedVector,
                   searchedForType searchedFor) {

  for (searchedVectorType comparer : searchedList) {
    if (comparer == searchedFor) {
      return true;
    };
  };

  return false;
} */

template <typename searchedForType>
bool arrayChecker(searchedForType searchedArray[],
                  searchedForType searchedFor) {

  for (searchedForType comparer : searchedArray) {
    if (comparer == searchedFor) {
      return true;
    };
  };

  return false;
}

template <typename searchedForType>
bool vectorChecker(std::vector<searchedForType> searchedVector,
                   searchedForType searchedFor) {

  for (searchedForType comparer : searchedVector) {
    if (comparer == searchedFor) {
      return true;
    };
  };

  return false;
}

template <typename searchedForType>
bool listChecker(std::list<searchedForType> searchedList,
                 searchedForType searchedFor) {

  for (searchedForType comparer : searchedList) {
    if (comparer == searchedFor) {
      return true;
    };
  };

  return false;
}