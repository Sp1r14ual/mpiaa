#include "closest_pair.h"

#include <stdexcept>


using namespace std;

bool CompareX(Point point1, Point point2)
{
	return point1.x < point2.x;
}

bool CompareY(Point point1, Point point2)
{
	return point1.y < point2.y;
}

std::pair<Point, Point> closest_pair_between(std::pair<Point, Point> PLeft, std::pair<Point, Point> PRight, double d)
{
	//to do

}

std::pair<Point, Point> closest_pair(const std::vector<Point> &points) {
	// Return the closest pair of points from given points.
	// Order of points in the result doesn't matter.
	// If there are fewer than 2 points, throw an exception.

	if (points.size() < 2) {
		throw invalid_argument("Not enough points");
	}	

	/*
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
	*/

	if (points.size() <= 3)
	{
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

	std::sort(points.begin(), points.end(), CompareX);
	auto mid = points.begin() + points.size() / 2;

	std::vector<Point> PLeft;
	std::vector<Point> PRight;

	for (auto i = points.begin(); i != mid + 1; i++)
		PLeft.push_back(*i);
	
	for (auto i = mid; i != points.end(); i++)
		PRight.push_back(*i);
	
	auto pl = closest_pair(PLeft);
	auto pr = closest_pair(PRight);

	double d = min(pl.first.distance(pl.second), pr.first.distance(pr.second));

	std::pair<Point, Point> pb = closest_pair_between(pl, pr, d);

	auto min_pair = pl.first.distance(pl.second) < pr.first.distance(pr.second) ? 
	pl.first.distance(pl.second) < pb.first.distance(pb.second) ? pl : pb : 
	pr.first.distance(pr.second) < pb.first.distance(pb.second) ? pr : pb;

	return min_pair;





	





}
