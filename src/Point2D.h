#ifndef POINT2D_H
#define POINT2D_H

#include <vector>
#include <string>

using namespace std;

class Point2D
{
public:
    // constructor
    Point2D() : px(0), py(0) {}
    Point2D(double pointX, double pointY) : px(pointX), py(pointY) {}

    //get
    vector<double> getVect();

    //set
    void setPx(double x);
    void setPy(double y);

    // overlaod the sum and difference operators
    Point2D operator-(const Point2D &obj) const;
    Point2D operator+(const Point2D &obj) const;

    // helper functions
    double shortestDistance(vector<Point2D> line);
    Point2D perpendicular(vector<Point2D> line);
    double euclideanNorm();
    double euclideanDistance(Point2D pt);
    double dot(Point2D b);
    Point2D scale(double scale);

private:
    double px, py;
};

#endif