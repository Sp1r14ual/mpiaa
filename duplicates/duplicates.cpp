#include "duplicates.h"
/*
bool has_duplicates(const std::vector<int> &data)
{
    for (auto i = data.begin(); i != data.end(); i++)
        for (auto j = std::next(i, 1); j != data.end(); j++)
            if (*i == *j)
                return true;
    return false;
}


std::vector<int> get_duplicates(const std::vector<int> &data) 
{
    std::vector<int> result;
    std::vector<int> duplicates;

    if (has_duplicates(data))
        for (auto i = data.begin(); i != data.end(); i++)
            for (auto j = std::next(i, 1); j != data.end(); j++)
                if (*i == *j && std::find(duplicates.begin(), duplicates.end(), *i) == duplicates.end())
                {
                    result.push_back(*i);
                    duplicates.push_back(*i);
                }


    return result;
}
*/

bool has_duplicates(const std::vector<int> &data)
{
    if (data.empty())
        return false;

    std::vector<int> v;
    for (auto x : data)
        v.push_back(x);

    std::sort(v.begin(), v.end());
    for (auto i = v.begin() + 1; i != v.end(); i++)
        if (*i == *(i - 1))
            return true;
    return false;
}

std::vector<int> get_duplicates(const std::vector<int> &data)
{

    if (data.empty())
        return std::vector<int>{};

    std::vector<int> result{};
    std::set<int> duplicates{};

    std::vector<int> v;
    for (auto x : data)
        v.push_back(x);

    if (has_duplicates(data))
    {
        std::sort(v.begin(), v.end());
        for (auto i = v.begin() + 1; i != v.end(); i++)
            if (*i == *(i - 1) && std::find(duplicates.begin(), duplicates.end(), *i) == duplicates.end())
            {
                result.push_back(*i);
                duplicates.insert(*i);
            }
    }

    return result;
}