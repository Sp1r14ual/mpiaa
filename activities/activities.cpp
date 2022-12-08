#include "activities.h"
#include <algorithm>
#include <vector>

using namespace std;

std::vector<Activity> get_max_activities(const std::vector<Activity> &activities)
{
    if (activities.size() == 0 || activities.size() == 1)
        return activities;

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

    return result;
}
