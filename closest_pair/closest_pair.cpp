#include "closest_pair.h"

#include <stdexcept>

using namespace std;

std::pair<Point, Point> closest_pair(const std::vector<Point> &points) {
	// Return the closest pair of points from given points.
	// Order of points in the result doesn't matter.
	// If there are fewer than 2 points, throw an exception.

	if (points.size() < 2) {
		throw invalid_argument("Not enough points");
	}	

	double min = 1000000000000001;
	std::pair<Point, Point> result;

	for (auto i = points.begin(); i != points.end(); i++)
		for (auto j = i + 1; j != points.end(); j++)
		{
			double dist = (*i).distance(*j);
			if (dist < min)
			{
				min = dist;
				result = std::make_pair(*i, *j);
			}
		}

	return result;
}
