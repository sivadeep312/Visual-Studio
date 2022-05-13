#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

const int max_value_H = 180;
const int max_value = 255;

int main()
{

    string image_path1= "Res/Input.png";
    Mat image1 = imread(image_path1, IMREAD_COLOR);
    resize(image1, image1, { 500,500 });

    if (image1.empty())
    {
        cout << "Could not read the image: " << endl;
        return 1;
    }

    vector<int> lower_bound = { 24,255,255 };
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    int low_H = lower_bound[0], low_S = lower_bound[1], low_V = lower_bound[2];
    int high_H = max_value_H, high_S = max_value, high_V = max_value;

    Mat hsvImg, imgThreshold, threshy;

  
    cvtColor(image1, hsvImg, COLOR_BGR2HSV);

    inRange(hsvImg, Scalar(low_H, low_S, low_V), Scalar(high_H, high_S, high_V), imgThreshold);
    //threshold(imgThreshold, binaryImg, 254, 255, THRESH_BINARY);
    //findContours(binaryImg, contours, hierarchy, RETR_TREE, CHAIN_APPROX_NONE);
    //findContours(imgThreshold, contours, hierarchy, RETR_TREE, CHAIN_APPROX_NONE);
    //imshow("Original Image", binaryImg);
    //imshow("Hsv Image", hsvImg);
    //imshow("Threshold Image", imgThreshold);
   


    int k = waitKey(0); // Wait for a keystroke in the window

    if (k == 'q') {
        destroyAllWindows();
    }
    return 0;
}