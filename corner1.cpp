#include <iostream>
#include<vector>
#include <opencv2/opencv.hpp>
//#include <opencv2/highgui.hpp>



using namespace std;
using namespace cv;

int main() {

	Mat matImgRGB = imread("Res/input.png", IMREAD_COLOR);
	if (matImgRGB.empty())
	{
		cout << "Could not read the image: " << endl;
		return 1;
	}
	imshow("img", matImgRGB);
	Mat matImgGray(matImgRGB.size(), CV_32FC1), MatImgThresh;
	if (matImgRGB.channels() == 3) {
		cvtColor(matImgRGB, matImgGray, COLOR_BGR2GRAY);

	}
	else {
		matImgGray = matImgRGB;
	}
	
	int rat = matImgGray.rows * .25;

	Mat matsec1 = matImgGray(Rect(0, 0, rat, rat));
	Mat matsec2 = matImgRGB(Rect((matImgGray.cols - 1) - rat, 0, rat, rat));
	Mat matsec3 = matImgRGB(Rect(0, (matImgGray.rows - 1) - rat, rat, rat));
	Mat matsec4 = matImgGray(Rect((matImgGray.cols - 1) - rat, (matImgGray.rows - 1) - rat, rat , rat));
	double s1 = sum(matsec1)[0];
	double s2 = sum(matsec2)[0];
	double s3 = sum(matsec3)[0];
	double s4 = sum(matsec4)[0];
	cout << "Sum : " <<s1 << endl << s2 << endl << s3 << endl << s4 << endl;
	double size = matsec1.rows * matsec1.cols;

	double mean1 = s1 / size;
	double mean2 = s2 / size;
	double mean3 = s3 / size;
	double mean4 = s4 / size;
	cout << "Mean : " << mean1 << endl << mean2 << endl << mean3 << endl << mean4 << endl;
	double md1 = 0.0, md2 = 0.0, md3 = 0.0, md4 = 0.0;
	for (int i = 0; i < rat; i++) {
		for (int j = 0; j < rat; j++) {
			md1 = pow((double(matImgGray.at<uchar>(i, j)) - mean1), 2) + md1;
			md2 = pow((double(matImgGray.at<uchar>((matImgGray.rows - 1) - i, j)) - mean2), 2) + md2;
			md3 = pow((double(matImgGray.at<uchar>(i, (matImgGray.cols - 1 - j))) - mean3), 2) + md3;
			md4 = pow((double(matImgGray.at<uchar>((matImgGray.rows - 1) - i, (matImgGray.cols - 1 - j))) - mean4), 2) + md4;
		}
	}
	double sd1 = sqrt(md1 / size);
	double sd2 = sqrt(md2 / size);
	double sd3 = sqrt(md3 / size);
	double sd4 = sqrt(md4 / size);
	cout << "SD : " << sd1 << endl << sd2 << endl << sd3 << endl << sd4 << endl;
	return 0;



}