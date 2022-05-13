#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <string>

using namespace std;
using namespace cv;

const int max_value_H = 180;
const int max_value = 255;

int main()
{
 
    string im = "Res/Input.png";
    Mat img = imread(im, IMREAD_COLOR);
    resize(img, img, Size(600, 400));

    if (img.empty())
    {
        cout << "failed to load image" << endl;
        return EXIT_FAILURE;
    }
    vector<int> lower_bound = { 24,255,255 };
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    int low_H = lower_bound[0], low_S = lower_bound[1], low_V = lower_bound[2];
    int high_H = max_value_H, high_S = max_value, high_V = max_value;

    Mat hsvImg, imgThreshold, threshy;
    Mat gray, binaryImg, contoursImg;
    cvtColor(img, gray, COLOR_RGB2GRAY);

    threshold(gray, binaryImg, 0, 255, THRESH_BINARY);

    findContours(binaryImg, contours, hierarchy, RETR_TREE, CHAIN_APPROX_NONE);

    imshow("Original Image", img);

    for (int contour = 0; contour < contours.size(); contour++)
    {
        Scalar colour(rand() & 0xFF, rand() & 0xFF, rand() & 0xFF);
        drawContours(img, contours, contour, colour, FILLED, 8, hierarchy);
    }

    imshow("Contour Image", img);
    waitKey();

    return EXIT_SUCCESS;
}