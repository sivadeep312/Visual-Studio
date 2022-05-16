#include "opencv2/opencv.hpp"
#include <iostream>
#include <opencv2/features2d.hpp>


using namespace cv;
using namespace std;

const int max_value_H = 180;
const int max_value = 255;


int main()
{

	string image_path1 = "C:/Users/sivadeep.p/source/repos/images/Input.png";
	Mat image1 = imread(image_path1, IMREAD_COLOR);
	resize(image1, image1, { 500,500});
	imshow("Orginal Image", image1);

	if (image1.empty())
	{
		cout << "Could not read the image: " << endl;
		return 1;
	}
	Mat F = image1.clone();
	vector<int> lower_bound = { 24,255,255 };
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	int low_H = lower_bound[0], low_S = lower_bound[1], low_V = lower_bound[2];
	int high_H = max_value_H, high_S = max_value, high_V = max_value;

	Mat hsvImg, imgThreshold, threshy, binaryImg;

	cvtColor(image1, hsvImg, COLOR_BGR2HSV);

	inRange(hsvImg, Scalar(low_H, low_S, low_V), Scalar(high_H, high_S, high_V), imgThreshold);
	threshold(imgThreshold, binaryImg, 0, 255, THRESH_BINARY);

	findContours(imgThreshold, contours, hierarchy, RETR_TREE, CHAIN_APPROX_NONE);

	for (int contour = 0; contour < contours.size(); contour++)
	{
		Scalar colour(0 & 0xFF, 0 & 0xFF, 0 & 0xFF);
		drawContours(F, contours, contour, colour, FILLED, 8, hierarchy);

	}

	Mat diff = image1 - F;



	/*cvtColor(diff, di, COLOR_BGR2GRAY);
	
	// Setup SimpleBlobDetector parameters.
	SimpleBlobDetector::Params params;

	// Change thresholds
	params.minThreshold = 10;
	params.maxThreshold = 256;

	// Filter by Area.
	params.filterByArea = true;
	params.minArea = 4000;
	params.maxArea = 50000;


	// Filter by Circularity
	params.filterByCircularity = true;
	params.minCircularity = 0.9;


	//Scalar blobcolor;
	//blobcolor[0] = 24;
	//blobcolor[1] = 255;
	//blobcolor[2] = 255;
	
	//params.filterByColor = true;
	//params.filterByColor = true;
	//params.blobColor;
	//int high_H = max_value_H, high_S = max_value, high_V = max_value;
	//inRange(img, Scalar(24, 255, 255), Scalar(high_H, high_S, high_V), thresh);
	
	


	// Storage for blobs
	vector<KeyPoint> keypoints;



	// Set up detector with params
	Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create(params);

	// Detect blobs
	detector->detect(di, keypoints);

	//the total no of blobs detected are:
	size_t x = keypoints.size();
	cout << "total no of circles detected are:" << x << endl;


	


	// Draw detected blobs as red circles.
	// DrawMatchesFlags::DRAW_RICH_KEYPOINTS flag ensures
	// the size of the circle corresponds to the size of blob

	Mat im_with_keypoints;
	drawKeypoints(img, keypoints, im_with_keypoints, Scalar(0, 0, 255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

	// Show blobs
	imshow("keypoints", im_with_keypoints);*/
	
	imshow("keyp", diff);
	waitKey();
	return 0;
}