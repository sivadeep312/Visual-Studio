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
	Mat matImgGray(matImgRGB.size(), CV_32FC1), MatImgThresh;
	if (matImgRGB.channels() == 3) {
		cvtColor(matImgRGB, matImgGray, COLOR_BGR2GRAY);

	}
	else {
		matImgGray = matImgRGB;
	}
	cout << 1;
	int rat = matImgGray.rows * .25;
	double tot1 = 0.0,tot2 = 0.0,tot3 = 0.0,tot4 = 0.0,count=0.0;
	for (int i = 0; i < rat; i++) {
		for (int j = 0; j < rat; j++) {
			tot1 = double(matImgGray.at<uchar>(i, j)) + tot1;
			tot2 = double(matImgGray.at<uchar>((matImgGray.rows - 1) -i, j)) + tot2;
			tot3 = double(matImgGray.at<uchar>(i, (matImgGray.cols-1-j))) + tot3;
			tot4 = double(matImgGray.at<uchar>((matImgGray.rows - 1), (matImgGray.cols - 1 - j))) + tot4;
			count++;
		}
	}
	cout << "Total : "<<tot1 << endl << tot2 << endl << tot3 << endl << tot4 << endl;
	double mean1 = tot1 / count;
	double mean2 = tot2 / count;
	double mean3 = tot3 / count;
	double mean4 = tot4 / count;
	cout <<"Mean : " << mean1 << endl << mean2 << endl << mean3 << endl << mean4 << endl;

	double md1 = 0.0,md2=0.0,md3=0.0,md4=0.0;
	for (int i = 0; i < rat; i++) {
		for (int j = 0; j < rat; j++) {
			md1 = pow((double(matImgGray.at<uchar>(i, j)) - mean1), 2)+md1;
			md2 = pow((double(matImgGray.at<uchar>((matImgGray.rows - 1) - i, j)) - mean2), 2)+md2;
			md3 = pow((double(matImgGray.at<uchar>(i, (matImgGray.cols - 1 - j))) - mean3), 2)+md3;
			md4 = pow((double(matImgGray.at<uchar>((matImgGray.rows - 1) - i, (matImgGray.cols - 1 - j))) - mean4), 2)+md4;
		}
	}
	double sd1 = sqrt(md1 / count);
	double sd2 = sqrt(md2 / count);
	double sd3 = sqrt(md3 / count);
	double sd4 = sqrt(md4 / count);
	cout << "SD : " << sd1 << endl << sd2 << endl << sd3 << endl << sd4 << endl;
	return 0;



}