#include <opencv2/opencv.hpp>
#include <iostream>
#include<vector>


using namespace std;
using namespace cv;

const double pi = 3.14159265358979323846;

int main() {
	int i_t = 0;
	int rmin = 20, rmax = 28;		//////////// rmin and rmax

	//////////////////CALLING MATRIX

	string str_name = "coloredChips.png";										//////// name
	Mat I = imread("Res/" + str_name);
	cout << "sf" << endl;
	if (I.empty())
	{
		cout << "Could not read the image: " << endl;
		return 1;
	}
	//imshow("Orginal", I);

	Mat IC = I.clone();
;

	////////////////PREPROCESSING

	Mat matImgGray, matImgBlur, matImgCanny, matImgThresh;
	Mat blur_sharp, sharpgr, sharpcan;//
	GaussianBlur(I, matImgBlur, Size(5, 5), 1, 0);
	

	if (I.channels() == 3) {
		cvtColor(matImgBlur, matImgGray, COLOR_BGR2GRAY);
	}
	else {
		matImgGray = I;
	}

	//	////////////////////// CANNY /////////////////////////////////////////////////////////

	Canny(matImgGray, matImgCanny, 100, 30);
	Mat kernel = getStructuringElement(MORPH_RECT, Size(2, 2));
	dilate(matImgCanny, matImgCanny, kernel);
	imshow("canny", matImgCanny);




	Mat A(I.size(), CV_8UC1, Scalar::all(0));
	Mat B = A.clone();
	Mat C = A.clone();
	Mat D = A.clone();
	Mat E = A.clone();

	

	vector<Point>crd;
	for (int i = 0; i < matImgCanny.rows; i++) {
		for (int j = 0; j < matImgCanny.cols; j++) {
			if (matImgCanny.at<uchar>(i, j) == 255) {
				crd.push_back(Point(i, j));
			}
		}
	}
	cout << "brfore " << crd.size() << endl;
	vector<int>Line_Pos;
	for (int i = 0; i <= crd.size() - 3; i++) {
		int t = 0;
		Point A = crd[i] - crd[i + 1];
		double X = A.x;
		double Y = A.y;
		double ang;
		if  (Y != 0) {
			ang = Y / X;
		}
		else { ang = 90; }

		for (int j = i + 2; j < crd.size(); j++) {
			Point B = crd[i] - crd[j];
			double X1 = B.x;
			double Y1 = B.y;
			double ang1;
			if  (Y1 != 0) {
				ang1 = Y1 / X1;
			}
			else {
				ang1 = 90;
			}
			if (ang1 == ang) {

				//Line_Pos.push_back(j);

			}
			else {
				t++;
			}
		}
		if (t != 0) {

			Line_Pos.push_back(i);
			Line_Pos.push_back(i + 1);

		}
	}

	sort(Line_Pos.begin(), Line_Pos.end());
	Line_Pos.erase(unique(Line_Pos.begin(), Line_Pos.end()), Line_Pos.end());
	reverse(Line_Pos.begin(), Line_Pos.end());

	for (int m = 0; m < crd.size(); m++) {
		crd.erase(crd.begin() + (Line_Pos[m]));
	}

	cout << "aftr" << crd.size() << endl;


	for (int i = 0; i < crd.size(); i++) {
		D.at<uchar>(crd[i].x, crd[i].y) = 255;
	}

	imshow("D", D);

	E = D + B;
	kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(E, E, kernel);
	//imshow("E", E);

	for (int i = 0; i < IC.cols; i++) {
		for (int j = 0; j < IC.rows; j++) {
			if (E.at<uchar>(j, i) == 255) {
				IC.at<Vec3b>(j, i)[0] = 201;
				IC.at<Vec3b>(j, i)[1] = 145;
				IC.at<Vec3b>(j, i)[2] = 76;

			}
		}
	}

	imshow("IC", IC);


	waitKey(0);
	return 0;
}