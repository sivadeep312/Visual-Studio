#include <iostream>
#include <vector>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;


int main() {

    Mat  imgCircles, detectImgCircles;
    string path = "Res/Input.png";

    imgCircles = imread(path);
    if (imgCircles.empty()) {
    cout << "failed to open img.jpg";}
    else {
        cout << "img.jpg loaded OK";
        imgCircles.copyTo(detectImgCircles);
        Mat gray;
        cvtColor(imgCircles, gray, COLOR_RGB2GRAY);

        medianBlur(gray, gray, 5);

        vector<Vec3f> circles;
        HoughCircles(gray, circles, HOUGH_GRADIENT, 1, gray.rows / 16, 100, 30, 200, 500);

        for (size_t i = 0; i < circles.size(); i++)
        {
            Vec3i c = circles[i];
            Point center = Point(c[0], c[1]);
            // circle center
            circle(detectImgCircles, center, 1, Scalar(0, 100, 100), 3, LINE_AA);
            // circle outline
            int radius = c[2];

            circle(detectImgCircles, center, radius, Scalar(255, 0, 255), 3, LINE_AA);
        }

        imshow("Original Circle Image", imgCircles);
        imshow("Circle Detection", detectImgCircles);
        waitKey(0);

    }
    


    return 0;
}