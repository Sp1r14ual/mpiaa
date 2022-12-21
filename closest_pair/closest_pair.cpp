#include "closest_pair.h"

#include <stdexcept>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <iostream>

using namespace std;

bool CompareX(const Point& point1, const Point& point2)
{
	return point1.x < point2.x;
}

bool CompareY(const Point& point1, const Point& point2)
{
	return point1.y < point2.y;
}

std::pair<Point, Point> closest_pair_between(const std::vector<Point> &PLeft, const std::vector<Point> &PRight, double d)
{
	double x_m = (PLeft[PLeft.size() - 1].x + PRight[0].x) / 2;
	std::vector<Point> PStripe;

	for (auto i = PLeft.begin(); i != PLeft.end(); i++)
		if (abs((*i).x - x_m) < d)
			PStripe.push_back(*i);
	
	for (auto i = PRight.begin(); i != PRight.end(); i++)
		if (abs((*i).x - x_m) < d)
			PStripe.push_back(*i);
		

	sort(PStripe.begin(), PStripe.end(), CompareY);

	std::pair<Point, Point> result;
	if (PStripe.size() > 1)
	{
		result = make_pair(PStripe[0], PStripe[1]);
		for (auto i = PStripe.begin(); i != PStripe.end() - 1; i++)
			for (auto j = i + 1; j != PStripe.end(); j++)
				if ((*i).distance(*j) < result.first.distance(result.second))
					result = std::make_pair(*i, *j);
	}
	else
	{
		result = make_pair(PLeft[0], PRight[0]);
	}

	return result;

}

std::pair<Point, Point> bruteforce(const std::vector<Point> &points)
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

std::pair<Point, Point> closest_pair(const std::vector<Point> &points) {
	// Return the closest pair of points from given points.
	// Order of points in the result doesn't matter.
	// If there are fewer than 2 points, throw an exception.
	auto t1 = std::chrono::high_resolution_clock::now();	

	if (points.size() < 2)
		throw invalid_argument("Not enough points");

	if (points.size() <= 3)
		return bruteforce(points);

	std::vector<Point> points_copy (points);

	sort(points_copy.begin(), points_copy.end(), CompareX);

	std::vector<Point> PLeft;
	std::vector<Point> PRight;

	for (int i = 0; i < points_copy.size() / 2; i++)
		PLeft.push_back(points_copy[i]);
	
	for (int i = points_copy.size() / 2; i < points_copy.size(); i++)
		PRight.push_back(points_copy[i]);
	
	std::pair<Point, Point> pl = closest_pair(PLeft);
	std::pair<Point, Point> pr = closest_pair(PRight);

	double d = min(pl.first.distance(pl.second), pr.first.distance(pr.second));

	std::pair<Point, Point> pb = closest_pair_between(PLeft, PRight, d);

	std::pair<Point, Point> min_pair = pl.first.distance(pl.second) < pr.first.distance(pr.second) ? 
	pl.first.distance(pl.second) < pb.first.distance(pb.second) ? pl : pb : 
	pr.first.distance(pr.second) < pb.first.distance(pb.second) ? pr : pb;

	auto t2 = std::chrono::high_resolution_clock::now();
	auto time = std::chrono::duration<double>(t2 - t1).count();
	std::cout << "Time: " << time << " sec." << std::endl;


	return min_pair;

}
