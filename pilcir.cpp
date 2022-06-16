#include <opencv2/opencv.hpp>
#include <iostream>
#include<vector>
#include <cmath>

using namespace std;
using namespace cv;



int main() {
	string name = "pillsetc.png";
	int num = 4;
	int t = 0;
	Mat I = imread("Res/" + name);
	if (I.empty())
	{
		cout << "Could not read the image: " << endl;
		return 1;
	}
	Mat B = I.clone();
	Mat matImgGray, matImgBlur,matHough,matImgCanny;
	GaussianBlur(I, matImgBlur, Size(3, 3), 1, 0);
	if (I.channels() == 3) {
		t = 100;
		cvtColor(I, matImgGray, COLOR_BGR2GRAY);
	}
	else {
		matImgGray = I;
	}
	
	
	vector<Point>vecCen;
	vector<int>vecrad;
	vector<Vec3f> veccircles;
	int h = 10, l = 15;
	
	do{
		Canny(matImgGray, matImgCanny, h,l);
		matHough = matImgCanny;
		cout << veccircles.size() << endl;
		HoughCircles(matHough, veccircles, HOUGH_GRADIENT, 1, matHough.rows /20 , 100, 30, 15, 55);
		h=h+5;
		l = l + 5;
	
		
	}
	while( (veccircles.size()> num)&&(h<255)&&(l<255));
	
	for (size_t i = 0; i < veccircles.size(); i++) {
		Vec3f c = veccircles[i];
		Point center = Point(round(c[0]), round(c[1]));
		vecCen.push_back(center);
		float radius = c[2];
		vecrad.push_back(round(radius));
		Scalar Col;
		if (t == 100) {
			Col = Scalar(169, 125, 68);
		}
		else {
			Col = Scalar::all(0);
		}
		circle(B, center, radius, Col, 3, LINE_AA);
	}
	while (veccircles.size() < num);
	imshow("detected circles", B);
	cout << " Centers are : ";
	for (size_t i = 0; i < vecCen.size(); i++) {
		cout << vecCen[i] << ",";
	}
	cout << "\b ";
	cout << endl;
	cout << " Radius are : ";
	for (size_t i = 0; i < vecrad.size(); i++) {
		cout << vecrad[i] << ",";
	}
	cout << "\b ";

	imshow("matImg", B);

	waitKey(0);
	return 0;
}