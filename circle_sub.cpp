#include<opencv2/opencv.hpp>
#include<iostream>
#include<math.h>

using namespace std;
using namespace cv;

void draw_float_circle(Mat &img, Point2f center, float radius, Scalar color, int thickness = 1, int lineType = 8, int shift = 4) {
		//int factor = 2 * *shift;
		int factor = pow(2,shift);
		center = Point(int(round(center.x * factor)), int(round(center.y * factor)));
		//cout << center << endl;
		radius = int(round(radius * factor));
		//cout << radius << endl;
		circle(img, center, radius, color, thickness, lineType, shift);
}

int main() {
	Mat pix(100, 100, CV_8UC1, Scalar::all(0));
	Mat pix1(100, 100, CV_8UC1, Scalar::all(0));
	Mat sub(100, 100, CV_8UC1, Scalar::all(0));

	circle(pix, Point(51, 51), 25, 255, -1, 1);
	cout << "sumpix :" << sum(pix)[0] << endl;
	draw_float_circle(sub, Point(50, 50), 25.125, 255, -1, 1,3);
	cout << "sumsub" << sum(sub)[0] << endl;
	circle(pix1, Point(50, 50), 26, 255, -1, 1);
	cout << "sumpix1 :" << sum(pix1)[0] << endl;
	imshow("sub", sub);
	imshow("pix", pix);
	imshow("pix1", pix1);
	waitKey(0);

}
