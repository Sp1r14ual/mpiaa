#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <random>
#include <chrono>
#include <iostream>

using namespace std;

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

std::vector<int> random_sequence(int size, int max)
{
    default_random_engine generator;
    uniform_int_distribution<int> distribution(0, max);
    vector<int> result;
    for (int i = 0; i < size; i++) {
        result.push_back(distribution(generator));
    }
    return result;
}


int main(){
  std::vector<int> counts = {10, 100, 1000, 10000, 100000, 1000000};
  for (auto n : counts)
  {
    std::vector<int> array = random_sequence(n, n);
    auto t1 = std::chrono::high_resolution_clock::now();
    auto result = count_sort(array, 0, n);
    auto t2 = std::chrono::high_resolution_clock::now();
    auto time = std::chrono::duration<double>(t2 - t1).count();
    auto t3 = std::chrono::high_resolution_clock::now();
    std::sort(array.begin(), array.end());
    auto t4 = std::chrono::high_resolution_clock::now();
    auto time2 = std::chrono::duration<double>(t4 - t3).count();
    std::cout << "N = " << n << std::endl;
    std::cout << "Count Sort: " << time << " sec." << std::endl;
    std::cout << "Standart Sort: " << time2 << " sec." << std::endl;
    std::cout << std::endl;
  }
  return 0;
}