#include "activities.h"
#include <algorithm>
#include <vector>
#include <chrono>
#include <iostream>

using namespace std;
/*
//naive
vector<Activity> get_max_activities(const vector<Activity>& activities)
{
    vector <Activity> result;
    if (activities.empty()) {
        return result;
    }

    Activity a = activities[0];
    for (auto i = 0; i < activities.size(); ++i)
    {
        if (activities[i].finish < a.finish) {
            a = activities[i];
        }
    }
    result.push_back(a);

    for (auto i = 0; i < activities.size(); ++i)
    {
        Activity b = activities[i];
        if (a.finish <= b.start)
        {
            for (auto j = 0; j < activities.size(); ++j)
            {
                if (activities[j].finish > a.finish and activities[j].finish < b.finish and a.finish <= activities[j].start)
                {
                    bool k = false;
                    for (auto it = 0; it < result.size(); ++it)
                    {
                        if (activities[j] == result[it])
                        {
                            k = true;
                            break;
                        }
                    }
                    if (!k) {
                        b = activities[j];
                    }
                }
            }
            result.push_back(b);
            a = b;
        }
    }


    return result;
}
*/
//effective
std::vector<Activity> get_max_activities(const std::vector<Activity> &activities)
{
    auto t1 = std::chrono::high_resolution_clock::now();
    if (activities.size() == 0 || activities.size() == 1)
    {
        auto t2 = std::chrono::high_resolution_clock::now();		
	    auto time = std::chrono::duration<double>(t2 - t1).count();
        std::cout << "Time: " << time << " sec." << std::endl;
        return activities;
    }

    vector<Activity> s_activities = activities;
    vector<Activity> result;

    sort(s_activities.begin(), s_activities.end(), [](const Activity& s1, const Activity& s2){ return s1.finish < s2.finish; });
    
    result.push_back(s_activities[0]);
    int k = 0;

    for (int i = 1; i < s_activities.size(); i++)
    {
        if (s_activities[i].start >= s_activities[k].finish)
        {
            result.push_back(s_activities[i]);
            k = i;
        }
    }

    auto t2 = std::chrono::high_resolution_clock::now();		
    auto time = std::chrono::duration<double>(t2 - t1).count();
    std::cout << "Time: " << time << " sec." << std::endl;
    return result;
}