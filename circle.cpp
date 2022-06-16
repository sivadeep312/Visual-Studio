#include <opencv2/opencv.hpp>
#include <iostream>
#include<vector>
#include <cmath>

using namespace std;
using namespace cv;



int main() {
	string name = "coloredChips.png";
	int num = 26;
	int t = 0;
	Mat I = imread("Res/" + name);
	if (I.empty())
	{
		cout << "Could not read the image: " << endl;
		return 1;
	}
	Mat B = I.clone();
	Mat matImgGray, matImgThresh, matImgBlur;
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
	int x=20,y=100;
	 do{
		HoughCircles(matImgGray, veccircles, HOUGH_GRADIENT, 1, matImgGray.rows / x,y, 30, 20, 28);
		x++;
		y--;
		cout << veccircles.size()<<endl;
	 }
	 while ((veccircles.size() !=num) && (y > 30) && (x < matImgGray.rows));
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
	
	
	 imshow("matImg", B);
	
	waitKey(0);
	return 0;
}