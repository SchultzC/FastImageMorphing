#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

#include "Morph.h"

using namespace cv;
using namespace std;

Mat src = imread("img/SimpleMorph.png", IMREAD_COLOR);
Mat dst = Mat::zeros(src.size(), CV_8UC3);

shared_ptr<Mat> sharedSrc = make_shared<Mat>(move(src));
shared_ptr<Mat> sharedDst = make_shared<Mat>(move(dst));

Morph d = Morph(sharedSrc, sharedDst);

string winName = "SpeedMorphing Demo";

int line1Xstart = 72;
int line1Ystart = 152;
int line1Xend = 72;
int line1Yend = 52;

int line2Xstart = 70;
int line2Ystart = 50;
int line2Xend = 132;
int line2Yend = 50;

int maxXstart = 200;
int maxYstart = 200;
int maxXend = 200;
int maxYend = 200;

void Morphing(int, void *);

int main(int argc, char **argv)
{

    namedWindow(winName, WINDOW_AUTOSIZE);

    createTrackbar("Line1 Xstart:", winName,
                   &line1Xstart, maxXstart,
                   Morphing);

    createTrackbar("Line1 Ystart:", winName,
                   &line1Ystart, maxYstart,
                   Morphing);

    createTrackbar("Line1 Xend:", winName,
                   &line1Xend, maxXstart,
                   Morphing);

    createTrackbar("Line1 Yend:", winName,
                   &line1Yend, maxYstart,
                   Morphing);

    createTrackbar("Line2 Xstart:", winName,
                   &line2Xstart, maxXstart,
                   Morphing);

    createTrackbar("Line2 Ystart:", winName,
                   &line2Ystart, maxYstart,
                   Morphing);

    createTrackbar("Line2 Xend:", winName,
                   &line2Xend, maxXstart,
                   Morphing);

    createTrackbar("Line2 Yend:", winName,
                   &line2Yend, maxYstart,
                   Morphing);

    // d.test();

    Morphing(0, 0);
    waitKey(0);
    return 0;
}

void Morphing(int, void *)
{

    vector<vector<double>> correspondence = {{72, 152, 72, 52, (double)line1Xstart, (double)line1Ystart, (double)line1Xend, (double)line1Yend},
                                             {70, 50, 132, 50, (double)line2Xstart, (double)line2Ystart, (double)line2Xend, (double)line2Yend}};

    float aParam = 0.1;
    float bParam = 1;
    float pParam = 0.1;
    string broderTreatment = "copy"; //wrap is also accepted

    // calculate new output
    d.createOutput(correspondence, aParam, bParam, pParam, broderTreatment);


    // draw vectors being used.
    int thickness = 2;
    int lineType = LINE_8;
    line(*sharedDst,
         Point(line2Xstart, line2Ystart),
         Point(line2Xend, line2Yend),
         Scalar(0, 0, 255),
         thickness,
         lineType);
    line(*sharedDst,
         Point(line1Xstart, line1Ystart),
         Point(line1Xend, line1Yend),
         Scalar(0, 0, 255),
         thickness,
         lineType);

    // redraw
    imshow(winName, *sharedDst);
}