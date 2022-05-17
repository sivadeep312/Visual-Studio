#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

const int max_value_H = 180;
const int max_value = 255;

int main()
{

	string image_path1 = "Res/Input.png";
	Mat img = imread(image_path1, IMREAD_COLOR);
	resize(img, img, { 500,500 });
	imshow("Orginal Image", img);

	if (img.empty())
	{
		cout << "Could not read the image: " << endl;
		return 1;
	}
	Mat F = img.clone();
	Mat G = img.clone();
	Mat H = img.clone();

	//////////////////////////////////////// YELLOW SEGMENTATION ////////////////////////////////////////////////////////////////////
	   

	vector<int> lower_bound = { 24,255,255 };
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	int low_H = lower_bound[0], low_S = lower_bound[1], low_V = lower_bound[2];
	int high_H = max_value_H, high_S = max_value, high_V = max_value;
	Mat hsvImg, mask_yellow;
	cvtColor(img, hsvImg, COLOR_BGR2HSV);
	inRange(hsvImg, Scalar(low_H, low_S, low_V), Scalar(high_H, high_S, high_V), mask_yellow);
	findContours(mask_yellow, contours, hierarchy, RETR_TREE, CHAIN_APPROX_NONE);

	for (int contour = 0; contour < contours.size(); contour++)
	{
		Scalar colour(0 & 0xFF, 0 & 0xFF, 0 & 0xFF);
		drawContours(F, contours, contour, colour, FILLED, 8, hierarchy);
		
	}
	Mat yellow_seg = img - F;


	/////////////////////////////////////// DETECTING CIRCLES //////////////////////////////////////////////////////////////////////


	Mat imgGray, imgBlur, imgCanny, imgDil, imgErode, difgray, imgThreshold, binaryImg, gn;
	cvtColor(yellow_seg, imgGray, COLOR_BGR2GRAY);
	GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);
	Canny(imgBlur, imgCanny, 25, 75);
	Mat kernel = getStructuringElement(MORPH_RECT, Size(2, 3));
	dilate(imgCanny, imgDil, kernel);

	vector<Vec3f> circles;
	HoughCircles(imgDil, circles, HOUGH_GRADIENT, 1, imgDil.rows / 10, 100, 30, 40, 55);
	Point new1, new2;
	for (size_t i = 0; i < circles.size(); i++)
	{
		Vec3i c = circles[i];
		int x1 = c[0];
		int y1 = c[1];
		Point center = Point(c[0], c[1]);
		int radius = c[2];
		circle(G, center, radius, Scalar(0, 0, 0), FILLED);
		new1 = Point(x1 - radius - 20, y1 - radius - 20);
		new2 = Point((x1 + radius+ 20), y1 + radius + 20);
		
	}
	Mat one_cir = img - G;
	//imshow("ONE CIRCLE", one_cir);
	rectangle(one_cir, new1, new2, Scalar(0, 255, 255), FILLED);
	
	////////////////// MASKING THE LOCATION OF CIRCLE ///////////////////////////
  

	Mat Hhsv, new_mask;
	cvtColor(one_cir, Hhsv, COLOR_BGR2HSV);
	inRange(Hhsv, Scalar(low_H, low_S, low_V), Scalar(max_value_H, max_value, max_value), new_mask);
	//imshow("new_mask", new_mask);

	for (int i = 0; i < new_mask.cols; i++) {
		for (int j = 0; j < new_mask.rows; j++) {
			if (new_mask.at<uchar>(j, i) != 255) {
				img.at<Vec3b>(j, i)[0] = 255;
				img.at<Vec3b>(j, i)[1] = 255;
				img.at<Vec3b>(j, i)[2] = 255;
				
			}
		
		}

	}

	/////////////////////////////// FINAL IMAGE /////////////////////////////
		
		
	imshow("Processed Image", img);
	
	waitKey(0); 
	return 0;
}