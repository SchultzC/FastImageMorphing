#include <cmath>
#include <vector>
#include <iostream>
#include <opencv2/core.hpp>

#include "Morph.h"
#include "Point2D.h"

using namespace cv;
using namespace std;

// implementaion of Warp
void Morph::createOutput(vector<vector<double>> lineCorrespondence, float aParam, float bParam, float pParam, string borderMode)
{
    int columns = src->cols;
    int rows = src->rows;

    for (int x = 0; x < columns; x++)
    {
        for (int y = 0; y < rows; y++)
        {
            Point2D xPoint(x, y);
            Point2D dSum;
            Point2D xPrime;
            double weightSum = 0;
            double dist;

            //  I would like to multi thread this protion since there is nothing stopping me from running this in parrallel.
            calculateNewValueLocation(lineCorrespondence, columns, rows, aParam, bParam, pParam, xPoint, dSum, xPrime, weightSum, dist, borderMode);
        }
    }
}

void Morph::calculateNewValueLocation(vector<vector<double>> lineCorrespondence, int columns, int rows, float aParam, float bParam, float pParam, Point2D xPoint, Point2D dSum, Point2D xPrime, double weightSum, double dist, string borderMode)
{
    for (vector<double> line : lineCorrespondence)
    {

        Point2D pPrimePoint(line[0], line[1]);
        Point2D qPrimePoint(line[2], line[3]);

        Point2D pPoint(line[4], line[5]);
        Point2D qPoint(line[6], line[7]);

        double u = calcU(xPoint, pPoint, qPoint);
        // cout << "U is: " << u << endl;
        double v = calcV(xPoint, pPoint, qPoint);
        // cout << "V is: " << v << endl;

        xPrime = calulateXprime(pPrimePoint, qPrimePoint, u, v);
        // cout << "xPrime: " << xPrime.getVect()[0] << "," << xPrime.getVect()[1] << endl;

        Point2D d = xPrime - xPoint;
        // cout << "d: " << d.getVect()[0] << "," << d.getVect()[1] << endl;

        if ((u >= 0) && (u <= 1))
        {
            dist = abs(v);
        }
        else
        {
            vector<Point2D> dstLine{pPoint, qPoint};
            dist = xPoint.shortestDistance(dstLine);
        }
        // cout << "dist: " << dist << endl;
        double demonw = aParam + dist;
        double weight = pow(pow(pPoint.euclideanDistance(qPoint), pParam) / demonw, bParam);
        // cout << "weight: " << weight << endl;

        dSum = dSum + d.scale(weight);
        // cout << "dSum: " << dSum.getVect()[0] << "," << dSum.getVect()[1] << endl;

        weightSum += weight;
    }

    double denom = weightSum;
    if (denom == 0)
    {
        denom = 0.0001;
    }

    xPrime = xPoint + dSum.scale(1 / denom);
    // cout << "NNNxPrime: " << xPrime.getVect()[0] << "," << xPrime.getVect()[1] << endl;

    // cout << "--------------------------" << endl;
    setOutputValues(xPoint, xPrime, columns, rows, borderMode);
}

void Morph::setOutputValues(Point2D location, Point2D fromLocation, int columns, int rows, string borderMode)
{
    // cout << "from1: " << fromLocation.getVect()[0] << "," << fromLocation.getVect()[1] << endl;
    if (borderMode == "copy")
    {
        if (fromLocation.getVect()[1] > rows - 1)
        {
            fromLocation.setPy(rows - 1);
        }
        if (fromLocation.getVect()[1] < 0)
        {
            fromLocation.setPy(0);
        }

        if (fromLocation.getVect()[0] > columns - 1)
        {
            fromLocation.setPx(columns - 1);
        }

        if (fromLocation.getVect()[0] < 0)
        {
            fromLocation.setPx(0);
        }
    }
    else if (borderMode == "wrap")
    {
        if (fromLocation.getVect()[1] < 0)
        {
            fromLocation.setPy(rows + (int)round(fromLocation.getVect()[1]) % rows);
        }
        else
        {
            fromLocation.setPy((int)round(fromLocation.getVect()[1]) % rows);
        }

        if (fromLocation.getVect()[0] < 0)
        {
            fromLocation.setPx(columns + (int)round(fromLocation.getVect()[0]) % columns);
        }
        else
        {
            fromLocation.setPy((int)round(fromLocation.getVect()[1]) % rows);
        }
    }

    // cout << "from2: " << fromLocation.getVect()[0] << "," << fromLocation.getVect()[1] << endl;

    int setX = (int)round(location.getVect()[0]);
    int setY = (int)round(location.getVect()[1]);
    int fromX = fromLocation.getVect()[0];
    int fromY = fromLocation.getVect()[1];

    dst->at<Vec3b>(setY, setX)[0] = src->at<Vec3b>(fromY, fromX)[0];
    dst->at<Vec3b>(setY, setX)[1] = src->at<Vec3b>(fromY, fromX)[1];
    dst->at<Vec3b>(setY, setX)[2] = src->at<Vec3b>(fromY, fromX)[2];

    // cout << "in set output" << endl;
}

double Morph::calcU(Point2D X, Point2D P, Point2D Q)
{
    double denom = pow((Q - P).euclideanNorm(), 2);
    if (denom == 0)
    {
        denom = 0.0001;
    }
    return (X - P).dot(Q - P) / denom;
}

double Morph::calcV(Point2D X, Point2D P, Point2D Q)
{
    Point2D originPoint;
    vector<Point2D> vectorline{originPoint, Q - P};

    double denom = (Q - P).euclideanNorm();
    if (denom == 0)
    {
        denom = 0.0001;
    }

    return (X - P).dot(X.perpendicular(vectorline)) / denom;
}

Point2D Morph::calulateXprime(Point2D Pprime, Point2D Qprime, double u, double v)
{
    Point2D originPoint;
    vector<Point2D> vectorline{originPoint, Qprime - Pprime};
    Point2D pt = Pprime + (Qprime - Pprime).scale(u) + (Pprime.perpendicular(vectorline).scale(v)).scale(1 / (Qprime - Pprime).euclideanNorm());

    return pt;
}

void Morph::test()
{
    Point2D a(5, 5);
    Point2D b(5, 15);
    double scalingConstant = 6;

    Point2D c = a + b;
    vector<double> answer_c = c.getVect();
    cout << "sum [" << a.getVect()[0] << "," << a.getVect()[1] << "] and [" << b.getVect()[0] << "," << b.getVect()[1] << "] is: [" << answer_c[0] << "," << answer_c[1] << "]" << endl;

    Point2D d = a - b;
    vector<double> answer_d = d.getVect();
    cout << "difference [" << a.getVect()[0] << "," << a.getVect()[1] << "] and [" << b.getVect()[0] << "," << b.getVect()[1] << "] is: [" << answer_d[0] << "," << answer_d[1] << "]" << endl;

    double dotProduct = a.dot(b);
    cout << "dotProduct [" << a.getVect()[0] << "," << a.getVect()[1] << "] and [" << b.getVect()[0] << "," << b.getVect()[1] << "] is: " << dotProduct << endl;

    Point2D e = a.scale(scalingConstant);
    vector<double> answer_e = e.getVect();
    cout << "sclaing [" << a.getVect()[0] << "," << a.getVect()[1] << "] by " << scalingConstant << " is: [" << e.getVect()[0] << "," << e.getVect()[1] << "]" << endl;

    vector<Point2D> sampLine(2);
    sampLine[0] = a;
    sampLine[1] = b;
    Point2D qPoint(6, 8);
    double shortestPath = qPoint.shortestDistance(sampLine);
    cout << "shortest distance between Point[" << qPoint.getVect()[0] << "," << qPoint.getVect()[1] << "] and line: [[" << sampLine[0].getVect()[0] << "," << sampLine[0].getVect()[1] << "],[" << sampLine[1].getVect()[0] << "," << sampLine[1].getVect()[1] << "]] is: " << shortestPath << endl;

    Point2D perpOut = a.perpendicular(sampLine);
    cout << "perpenicular slope is [" << perpOut.getVect()[0] << "," << perpOut.getVect()[1] << "] for line: [[" << sampLine[0].getVect()[0] << "," << sampLine[0].getVect()[1] << "],[" << sampLine[1].getVect()[0] << "," << sampLine[1].getVect()[1] << "]]" << endl;

    double eucDistance = b.euclideanNorm();
    cout << "euclidean Norm for [" << b.getVect()[0] << "," << b.getVect()[1] << "] is: " << eucDistance << endl;
};