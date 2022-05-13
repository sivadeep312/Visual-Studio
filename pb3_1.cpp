#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

const int max_value_H = 180;
const int max_value = 255;

int main()
{

    string image_path1 = "Res/Input.png";
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

    Mat hsvImg, imgThreshold, threshy,binaryImg ;
    Mat new_img(512, 512, CV_8UC3, Scalar(255, 255, 255));

    
    cvtColor(image1, hsvImg, COLOR_BGR2HSV);

    inRange(hsvImg, Scalar(low_H, low_S, low_V), Scalar(high_H, high_S, high_V), imgThreshold);
    threshold(imgThreshold, binaryImg, 0, 255, THRESH_BINARY);
    
    findContours(imgThreshold, contours, hierarchy, RETR_TREE, CHAIN_APPROX_NONE);
    
    for (int contour = 0; contour < contours.size(); contour++)
    {
        Scalar colour(24 & 0xFF, 255 & 0xFF, 255 & 0xFF);
        drawContours(new_img , contours, contour, colour, FILLED, 8, hierarchy);
    }

    //Mat diff_im = im - im2;
    imshow("new_img", new_img);
    //imshow("Contour Image", image1);
    //imshow("binary", binaryImg);
    //imshow("Hsv Image", hsvImg);
    //imshow("Threshold Image", imgThreshold);
    //imshow("Idf", imgThreshold);
    //Mat diff_im = imgThreshold - image1;
    //imshow("Idd", diff_im);
    Mat gray;
    cvtColor(new_img, gray, COLOR_BGR2GRAY);
    medianBlur(gray, gray, 5);
    vector<Vec3f> circles;
    HoughCircles(gray, circles, HOUGH_GRADIENT, 1, gray.rows / 1,  // change this value to detect circles with different distances to each other
        100, 30, 40, 55 // change the last two parameters
   // (min_radius & max_radius) to detect larger circles
    );
    for (size_t i = 0; i < circles.size(); i++)
    {
        Vec3i c = circles[i];
        Point center = Point(c[0], c[1]);
        // circle center
        circle(new_img, center, 1, Scalar(0, 100, 100), 3, LINE_AA);
        // circle outline
        int radius = c[2];
        circle(new_img, center, radius, Scalar(100, 0, 255), 10, LINE_AA);
    }
    imshow("detected circles", new_img);

    int k = waitKey(0); // Wait for a keystroke in the window

    if (k == 'q') {
        destroyAllWindows();
    }
    return 0;
}