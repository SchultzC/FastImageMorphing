#include <cmath>
#include <vector>
#include <iostream>
#include <opencv2/core.hpp>

#include "Point2D.h"

using namespace cv;
using namespace std;

// implementaion of Point

vector<double> Point2D::getVect()
{
    vector<double> v(2);
    v[0] = px;
    v[1] = py;
    return v;
}

void Point2D::setPx(double x){
    px = x;
}

void Point2D::setPy(double y){
    py = y;
}

Point2D Point2D::operator-(const Point2D &pt) const
{
    Point2D answer;
    answer.px = px - pt.px;
    answer.py = py - pt.py;
    return answer;
}
Point2D Point2D::operator+(const Point2D &pt) const
{
    Point2D answer;
    answer.px = px + pt.px;
    answer.py = py + pt.py;
    return answer;
}

double Point2D::shortestDistance(vector<Point2D> line)
{
    double linedx, linedy, norm, u, x, y, dx, dy, distance;

    linedx = line[1].px - line[0].px;
    linedy = line[1].py - line[0].py;

    norm = linedx * linedx + linedy * linedy;

    u = ((px - line[0].px) * linedx +
         (py - line[0].py) * linedy) /
        norm;

    if (u > 1)
    {
        u = 1;
    }
    else if (u < 0)
    {
        u = 0;
    }

    x = line[0].px + u * linedx;
    y = line[0].py + u * linedy;

    dx = x - px;
    dy = y - py;

    distance = sqrt(dx * dx + dy * dy);

    return distance;
}

Point2D Point2D::perpendicular(vector<Point2D> line)
{
    Point2D perp;
    perp.px = -1 * (line[1].py - line[0].py);
    perp.py = line[1].px - line[0].px;
    return perp;
}

double Point2D::euclideanNorm()
{
    return sqrt(pow(px, 2) + pow(py, 2));
}

double Point2D::euclideanDistance(Point2D pt)
{
    return sqrt(pow(pt.px - px, 2) + pow(pt.py - py, 2));
}

double Point2D::dot(Point2D b)
{
    return px * b.px + py * b.py;
}

Point2D Point2D::scale(double scale)
{
    Point2D scaled;
    scaled.px = px * scale;
    scaled.py = py * scale;
    return scaled;
}