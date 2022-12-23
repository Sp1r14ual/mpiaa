#include "count_sort.h"

// Return sorted array. 
// All elements of array are assumed to be from [min, max] range.

std::vector<int> count_sort(const std::vector<int> &array, int min, int max) {
  int range = max - min + 1;
  std::vector<int> counts (range, 0);
  std::vector<int> result(array.size(), 0);

  for (int i = 0; i < array.size(); i++)
    counts[array[i] - min]++;

  int index = 0;
  for (int i = 0; i < counts.size(); i++)
    for (int j = 0; j < counts[i]; j++)
      result[index++] = i + min;

  return result;
}


