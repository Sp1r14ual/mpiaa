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

    std::sort(data.begin(), data.end())
    for (int i = 0; i < data.size() - 1; i++)
        if (*data[i] == *data[i+1])
            return true;
    return false;

        
}


std::vector<int> get_duplicates(const std::vector<int> &data) 
{
    std::vector<int> result;
    std::vector<int> duplicates;
    if (has_duplicates(data))
        for (int i = 0; i < data.size() - 1; i++)
            if (*data[i] == *data[i+1] && std::find(duplicates.begin(), duplicates.end(), *i) == duplicates.end())
            {
                result.push_back(*i);
                duplicates.push_back(*i);
            }


    return result;
}