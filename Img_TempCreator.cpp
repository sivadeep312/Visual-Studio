#include <opencv2/opencv.hpp>
#include <iostream>
#include<vector>
#include <algorithm>

using namespace std;
using namespace cv;

typedef Point3_<uint8_t> Pixel;


void op(Pixel &pixel,const int* position) {

	int x1 = position[0] / 10;
	int y1 = position[1] / 10;
	if ((x1%2==0) &&(y1%2==0)) {
		pixel.x = 212;
		pixel.y = 46;
		pixel.z =190;
	}
	else {
		pixel.x =43;
		pixel.y = 56;
		pixel.z =124;
	}
	/*if ((position[0] % 10 == 0) || (position[1] % 10 == 0)) {
		pixel.x = 0;
		pixel.y = 0;
		pixel.z = 0;
	}*/
}

int main() {

	/*Mat matImage = imread("Res/chess.png", IMREAD_COLOR);
	if (matImage.empty())
	{
		cout << "Could not read the image: " << endl;
		return 1;
	}
	Mat matTemp = imread("Res/pawn.png", IMREAD_COLOR);
	if (matTemp.empty())
	{
		cout << "Could not read the Template Image: " << endl;
		return 1;
	}*/

	Mat MatimgA(50, 50, CV_8UC3, Scalar::all(255));
	MatimgA.forEach<Pixel>(&op);
	imwrite("Res/Image.png", MatimgA);
	imshow("A", MatimgA);
	//waitKey();

	Mat MatimgB(10, 10, CV_8UC3, Scalar(43,56,124));
	//MatimgA.forEach<Pixel>(&op);
	imshow("B", MatimgB);
	imwrite("Res/Template.png", MatimgB);
	waitKey();

}