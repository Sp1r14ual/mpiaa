#include "count_sort.h"
#include <chrono>
#include <iostream>

// Return sorted array. 
// All elements of array are assumed to be from [min, max] range.
std::vector<int> count_sort(const std::vector<int> &array, int min, int max) {
  std::cout << "Array Size: " << array.size() << std::endl;
  auto t1 = std::chrono::high_resolution_clock::now();
  int range = max - min + 1;
  std::vector<int> counts (range, 0);
  std::vector<int> result(array.size(), 0);

  for (int i = 0; i < array.size(); i++)
    counts[array[i] - min]++;

  int index = 0;
  for (int i = 0; i < counts.size(); i++)
    for (int j = 0; j < counts[i]; j++)
      result[index++] = i + min;

  auto t2 = std::chrono::high_resolution_clock::now();
  auto time = std::chrono::duration<double>(t2 - t1).count();
  std::cout << "Time: " << time << " sec." << std::endl;
  std::cout << std::endl;

  return result;
}
