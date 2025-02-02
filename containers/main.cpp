#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <set>
#include <algorithm>
#include <numeric>
#include <random>
#include <chrono>

using namespace std;

// Returns shuffled sequence of unique numbers of specified size, with values from start to start + size - 1.
vector<int> shuffled_sequence(int size, int start = 0) 
{
    vector<int> result(size);
    iota(result.begin(), result.end(), start);
    random_shuffle(result.begin(), result.end());
    return result;
}

// Returns sequence of random numbers of specified size, with values from 0 to max.
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

int main(int argc, char **argv) 
{

    const int size = (argc > 1 ? stoi(argv[1]) : 10);

    vector<int> counts {10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000};

    cout << "Vector" << endl;
    cout << "Time measurement for push_back(): " << endl;
    for (const auto n: counts)
    {
        vector<int> container;
        const auto elems_to_add = shuffled_sequence(size);
        for (auto elem: elems_to_add) 
            container.push_back(elem);

        auto sequence = random_sequence(n, n);

        auto t1 = chrono::high_resolution_clock::now();

        for (auto elem: sequence)
            container.push_back(elem);

        auto t2 = chrono::high_resolution_clock::now();
        auto time = std::chrono::duration<double>(t2 - t1).count();
        cout << "For N = " << n << " Time: " << time << " sec." << endl;

    }
    cout << endl;

    cout << "Time measurement for insert(): " << endl;
    for (const auto n: counts)
    {
        vector<int> container;
        const auto elems_to_add = shuffled_sequence(size);
        for (auto elem: elems_to_add) 
            container.push_back(elem);

        auto sequence = random_sequence(n, n);

        auto t1 = chrono::high_resolution_clock::now();
        
        for (auto elem: sequence)
            container.insert(container.begin(), elem);

        auto t2 = chrono::high_resolution_clock::now();
        auto time = std::chrono::duration<double>(t2 - t1).count();
        cout << "For N = " << n << " Time: " << time << " sec." << endl;

    }
    cout << endl;

    cout << "List" << endl;
    cout << "Time measurement for push_back(): " << endl;
    for (const auto n: counts)
    {
        list<int> container;
        const auto elems_to_add = shuffled_sequence(size);
        for (auto elem: elems_to_add)
            container.push_back(elem);

        auto sequence = random_sequence(n, n);

        auto t1 = chrono::high_resolution_clock::now();


        for (auto elem: sequence)
            container.push_back(elem);

        auto t2 = chrono::high_resolution_clock::now();
        auto time = std::chrono::duration<double>(t2 - t1).count();
        cout << "For N = " << n << " Time: " << time << " sec." << endl;

    }
    cout << endl;

    cout << "Time measurement for push_front(): " << endl;
    for (const auto n: counts)
    {
        list<int> container;
        const auto elems_to_add = shuffled_sequence(size);
        for (auto elem: elems_to_add)
            container.push_back(elem);

        auto sequence = random_sequence(n, n);

        auto t1 = chrono::high_resolution_clock::now();


        for (auto elem: sequence)
            container.push_front(elem);

        auto t2 = chrono::high_resolution_clock::now();
        auto time = std::chrono::duration<double>(t2 - t1).count();
        cout << "For N = " << n << " Time: " << time << " sec." << endl;

    }
    cout << endl;


    cout << "Set" << endl;
    cout << "Time measurement for insert(): " << endl;
    for (const auto n: counts)
    {
        set<int> container;
        const auto elems_to_add = shuffled_sequence(size);
        for (auto elem: elems_to_add)
            container.insert(elem);

        auto sequence = random_sequence(n, n);

        auto t1 = chrono::high_resolution_clock::now();


        for (auto elem: sequence)
            container.insert(elem);

        auto t2 = chrono::high_resolution_clock::now();
        auto time = std::chrono::duration<double>(t2 - t1).count();
        cout << "For N = " << n << " Time: " << time << " sec." << endl;

    }
    cout << endl;

    cout << "Search" << endl;
    cout << "Time measurement for Vector" << endl;

    for (const auto m: counts)
    {
        vector<int> container;
        const auto elems_to_add = shuffled_sequence(size);
        for (auto elem: elems_to_add)
            container.push_back(elem);

        const auto elems_to_search = random_sequence(m, 2 * size);
        int hits = 0;

        auto t1 = chrono::high_resolution_clock::now();
        
        for (const auto &elem: elems_to_search) 
        {
            auto it = find(container.begin(), container.end(), elem);
            if (it != container.end()) 
                hits++;
        }

        auto t2 = chrono::high_resolution_clock::now();
        auto time = std::chrono::duration<double>(t2 - t1).count();
        cout << "For m = " << m << " Time: " << time << " sec." << endl;
        cout << "From " << m << " elements found " << hits << " elements." << endl << endl;

    }
    cout << endl;

    cout << "Time measurement for List" << endl;
    for (const auto m: counts)
    {
        list<int> container;
        const auto elems_to_add = shuffled_sequence(size);
        for (auto elem: elems_to_add)
            container.push_back(elem);

        const auto elems_to_search = random_sequence(m, 2 * size);
        int hits = 0;

        auto t1 = chrono::high_resolution_clock::now();
        
        for (const auto &elem: elems_to_search) 
        {
            auto it = find(container.begin(), container.end(), elem);
            if (it != container.end()) 
                hits++;
        }

        auto t2 = chrono::high_resolution_clock::now();
        auto time = std::chrono::duration<double>(t2 - t1).count();
        cout << "For m = " << m << " Time: " << time << " sec." << endl;
        cout << "From " << m << " elements found " << hits << " elements." << endl << endl;

    }
    cout << endl;

    cout << "Time measurement for Set" << endl;
    for (const auto m: counts)
    {
        set<int> container;
        const auto elems_to_add = shuffled_sequence(size);
        for (auto elem: elems_to_add)
            container.insert(elem);

        const auto elems_to_search = random_sequence(m, 2 * size);
        int hits = 0;

        auto t1 = chrono::high_resolution_clock::now();
        
        for (const auto &elem: elems_to_search) 
        {
            auto it = container.find(elem);
            if (it != container.end()) 
                hits++;
        }

        auto t2 = chrono::high_resolution_clock::now();
        auto time = std::chrono::duration<double>(t2 - t1).count();
        cout << "For m = " << m << " Time: " << time << " sec." << endl;
        cout << "From " << m << " elements found " << hits << " elements." << endl << endl;

    }
    cout << endl;
}
 