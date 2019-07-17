#ifndef MORPH_H
#define MORPH_H

#include <vector>
#include <string>
#include <opencv2/core.hpp>
#include "Point2D.h"

using namespace cv;
using namespace std;

class Morph
{
public:
    // constructor
    Morph(shared_ptr<Mat> source, shared_ptr<Mat> destination) : src(source), dst(destination) {}
    Morph(){};
    // calculate and fill output
    void createOutput(vector<vector<double>> lineCorrespondence, float aParam, float bParam, float pParam, string borderMode = "copy");

    void test();

private:
    // Pointers to input image and output holder
    shared_ptr<Mat> src;
    shared_ptr<Mat> dst;

    // intermediate calculations
    double calcU(Point2D X, Point2D P, Point2D Q);
    double calcV(Point2D X, Point2D P, Point2D Q);
    Point2D calulateXprime(Point2D Pprime, Point2D Qprime, double u, double v);

    // setting output values
    void calculateNewValueLocation(vector<vector<double>> lineCorrespondence, int columns, int rows, float aParam, float bParam, float pParam, Point2D xPoint, Point2D dSum, Point2D xPrime, double weightSum, double dist, string borderMode);
    void setOutputValues(Point2D location, Point2D fromLocation, int columns, int rows, string borderMode);
};

#endif