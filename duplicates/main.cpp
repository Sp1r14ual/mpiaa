#include "duplicates.h"

#define CATCH_CONFIG_RUNNER
#include "../catch.hpp"

//#include "duplicates_test.cpp"
#include <chrono>

using namespace std;

vector<int> random_sequence(int size, int max)
{
    default_random_engine generator;
    uniform_int_distribution<int> distribution(0, max);
    vector<int> result;
    for (int i = 0; i < size; i++) {
        result.push_back(distribution(generator));
    }
    return result;
}

int main(int argc, char **argv) {
    int result = Catch::Session().run(argc, argv);

    vector<int> counts {10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000};

    //all elements are the same
    for (const auto n: counts)
    {
        vector<int> sequence;
        for (int i = 0; i < n; i++)
            sequence.push_back(4);


        auto t1 = chrono::high_resolution_clock::now();

        auto duplicates = get_duplicates(sequence);

        auto t2 = chrono::high_resolution_clock::now();
        auto time = std::chrono::duration<double>(t2 - t1).count();
        cout << "For N = " << n << " Time: " << time << " sec." << endl;

    }


    //all elements are random
    for (const auto n: counts)
    {
        vector<int> sequence = random_sequence(n, n);

        auto t1 = chrono::high_resolution_clock::now();

        auto duplicates = get_duplicates(sequence);

        auto t2 = chrono::high_resolution_clock::now();
        auto time = std::chrono::duration<double>(t2 - t1).count();
        cout << "For N = " << n << " Time: " << time << " sec." << endl;
    }

    //all elements are unique
    for (const auto n: counts)
    {
        vector<int> sequence;

        for (auto i = 0; i < n; i++)
            sequence.push_back(i);


        auto t1 = chrono::high_resolution_clock::now();

        auto duplicates = get_duplicates(sequence);

        auto t2 = chrono::high_resolution_clock::now();
        auto time = std::chrono::duration<double>(t2 - t1).count();
        cout << "For N = " << n << " Time: " << time << " sec." << endl;
    }

    return result;
}
