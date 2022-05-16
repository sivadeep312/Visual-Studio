
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;


int main()
{

	Mat img = imread("C:/Users/sivadeep.p/source/repos/images/Input.png", IMREAD_COLOR);
	resize(img, img, { 500,500 });
	Mat F = img.clone();
	Mat G = img.clone();
	Mat newimg(500, 500, CV_8UC3, Scalar(0, 0, 0));

	if (img.empty())
	{
		cout << "Could not read the image: " << endl;
		return 1;
	}
	Mat imgGray, imgBlur, imgCanny, imgDil, imgErode, difgray, imgThreshold, binaryImg;
	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);
	Canny(imgBlur, imgCanny, 25, 75);
	Mat kernel = getStructuringElement(MORPH_RECT, Size(2, 3));
	dilate(imgCanny, imgDil, kernel);
	Mat gray;
	cvtColor(img, gray, COLOR_BGR2GRAY);

	vector<Vec3f> circles;
	HoughCircles(gray, circles, HOUGH_GRADIENT, 1, gray.rows / 10, 100, 30, 40, 55);
	for (size_t i = 0; i < circles.size(); i++)
	{
		Vec3i c = circles[i];
		Point center = Point(c[0], c[1]);
		int radius = c[2];
		circle(F, center, radius, Scalar(0, 0, 0), FILLED);
	}
	Mat diff = img - F;
	//Mat add = newimg + diff;
	imshow("Orginal Image", diff);

	cvtColor(diff, difgray, COLOR_BGR2HSV);
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	inRange(difgray, Scalar(0, 255, 255), Scalar(180, 255, 255), imgThreshold);
	//threshold(imgThreshold, binaryImg, 0, 255, THRESH_BINARY);

	findContours(imgThreshold, contours, hierarchy, RETR_TREE, CHAIN_APPROX_NONE);

	for (int contour = 0; contour < contours.size(); contour++)
	{
		Scalar colour(0 & 0xFF, 0 & 0xFF, 0 & 0xFF);
		drawContours(G, contours, contour, colour, FILLED, 8, hierarchy);

	}



	Mat ng = diff - G;
	imshow("Op", ng);
	

	int k = waitKey(0); // Wait for a keystroke in the window

	if (k == 'q') {
		destroyAllWindows();
	}
	return 0;
}