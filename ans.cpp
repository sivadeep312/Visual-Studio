#include "opencv2/opencv.hpp"
#include <iostream>
#include <opencv2/features2d.hpp>


using namespace cv;
using namespace std;

const int max_value_H = 180;
const int max_value = 255;


int main()
{

	string image_path1 = "Res/Input.png";
	Mat img, di,F;
	img = imread(image_path1, IMREAD_COLOR);
	resize(img, img, { 500,500 });
	imshow("Orginal Image", img);
	F = img.clone();

	cvtColor(img, di, COLOR_BGR2GRAY);

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



	// Storage for blobs
	vector<KeyPoint> keypoints;

	// Set up detector with params
	Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create(params);

	// Detect blobs
	detector->detect(di, keypoints);

	//the total no of blobs detected are:
	size_t x = keypoints.size();
	cout << "total no of circles detected are:" << x << endl;

	Mat im_with_keypoints;
	drawKeypoints(img, keypoints, im_with_keypoints, Scalar(0, 0, 255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
	//drawContours(img, keypoints, Scalar(0, 0, 255), FILLED, 8);
	//drawContours(F, keypoints, Scalar(0, 0, 255), FILLED, 8);

	// Show blobs
	imshow("keypoints", im_with_keypoints);

	waitKey();
	return 0;
}