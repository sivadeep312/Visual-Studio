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
	imshow("Orginal Image", image1);

	if (image1.empty())
	{
		cout << "Could not read the image: " << endl;
		return 1;
	}
	Mat F = image1.clone();
	Mat G = image1.clone();
	vector<int> lower_bound = { 24,255,255 };
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	int low_H = lower_bound[0], low_S = lower_bound[1], low_V = lower_bound[2];
	int high_H = max_value_H, high_S = max_value, high_V = max_value;

	Mat hsvImg, imgThreshold, threshy, binaryImg;

	cvtColor(image1, hsvImg, COLOR_BGR2HSV);

	inRange(hsvImg, Scalar(low_H, low_S, low_V), Scalar(high_H, high_S, high_V), imgThreshold);
	//threshold(imgThreshold, binaryImg, 0, 255, THRESH_BINARY);

	findContours(imgThreshold, contours, hierarchy, RETR_TREE, CHAIN_APPROX_NONE);

	for (int contour = 0; contour < contours.size(); contour++)
	{
		Scalar colour(0 & 0xFF, 0 & 0xFF, 0 & 0xFF);
		drawContours(F, contours, contour, colour, FILLED, 8, hierarchy);
		
	}

	Mat diff = image1 - F;

	Mat imgGray, imgBlur, imgCanny, imgDil, imgErode;
	cvtColor(diff, imgGray, COLOR_BGR2GRAY);
	GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);
	Canny(imgBlur, imgCanny, 25, 75);
	Mat kernel = getStructuringElement(MORPH_RECT, Size(2, 3));
	dilate(imgCanny, imgDil, kernel);
	Mat gray;
	cvtColor(diff, gray, COLOR_BGR2GRAY);

	Mat img(512, 512, CV_8UC3, Scalar(255, 255, 255));


	vector<Vec3f> circles;
	
	
	HoughCircles(imgDil, circles, HOUGH_GRADIENT, 1, imgDil.rows / 1, 100, 30, 20, 55 );
	for (size_t i = 0; i < circles.size(); i++)
	{
		Vec3i c = circles[i];
		Point center = Point(c[0], c[1]);
		// circle center
		//circle(diff, center, 1, Scalar(0, 100, 100), 3, LINE_AA);
		// circle outline
		int radius = c[2];
		circle(diff, center, radius, Scalar(255, 100, 0), 3, LINE_AA);
		circle(img, center, radius, Scalar(0, 0, 0), 8, LINE_AA);
		
		circle(img, center, radius, Scalar(24, 6255, 255), FILLED);
		cout << "circle radius" << radius << "circle center" <<center;
	}

	imshow("Image", diff);
	imshow("New", img);

	int k = waitKey(0); // Wait for a keystroke in the window

	if (k == 'q') {
		destroyAllWindows();
	}
	return 0;
}