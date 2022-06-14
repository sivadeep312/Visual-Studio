#include <opencv2/opencv.hpp>
#include <iostream>
#include<vector>
#include <string>

using namespace std;
using namespace cv;




int main()
{
	Mat matImg = imread("Res/TestImage2.png", IMREAD_COLOR);
	Mat matImgClo = matImg.clone();

	Mat matImgGray, matMaskRed, matImgThresh;
	Mat image_pad;
	copyMakeBorder(matImg, image_pad, 50, 50, 50, 50, BORDER_CONSTANT, Scalar(0));
	//imshow("pad", image_pad);

	double angle = 7;
	Point2f center((image_pad.cols - 1) / 2.0, (image_pad.rows - 1) / 2.0);
	Mat rotation_matix = getRotationMatrix2D(center, angle, 1.0);
	Mat matImgrotated;
	warpAffine(image_pad, matImgrotated, rotation_matix, image_pad.size());
	

	if (matImgrotated.channels() == 3) {
		cvtColor(matImgrotated, matImgGray, COLOR_BGR2GRAY);
	}

	threshold(matImgGray, matImgThresh, 40, 255, 0);
	Mat matKernel = getStructuringElement(MORPH_RECT, Size(4, 4));
	dilate(matImgThresh, matImgThresh, matKernel);
	vector<vector<Point> > vecContours;
	vector<Vec4i> vecHierarchy;
	findContours(matImgThresh, vecContours, vecHierarchy, RETR_TREE, CHAIN_APPROX_NONE);


	vector<Point>pts;
	reverse(vecContours.begin(), vecContours.end());

	for (int i = 0; i < vecContours.size(); ++i) {
		pts.push_back(vecContours[i][0]);
	}
	


	//vector<vector<Point>> vecOuter;
	//vector<Point> vecInner;

	//for (int i = 0; i < pts.size() - 1; i++) {
	//	vecInner.push_back(pts[i]);
	//	if (abs(pts[i].y - pts[i + 1].y) > 2) {
	//		if(i!=0){
	//			reverse(vecInner.begin(), vecInner.end());
	//		}
	//		vecOuter.push_back(vecInner);
	//		vecInner.clear();
	//	}
	//	if (i == pts.size() - 2) {
	//		//vecInner.push_back(pts[i]);
	//		vecInner.push_back(pts[i + 1]);
	//		//reverse(vecInner.begin(), vecInner.end());
	//		vecOuter.push_back(vecInner);
	//		vecInner.clear();
	//	}
	//}
	//vector<Point>vecitr;
	//for (int i = 0; i < vecOuter.size(); i++) {
	//	for (int j = 0; j < vecOuter[i].size(); j++) {
	//		vecitr.push_back(vecOuter[i][j]);
	//	}
	//}
	//cout << vecitr.size() << endl << endl;
	for (int i = 0; i < pts.size(); ++i) {

		int k = pts.size() - i;
		putText(matImgrotated, to_string(i+1), pts[i], FONT_HERSHEY_COMPLEX_SMALL, .5, Scalar(255, 255, 255), .1, LINE_AA);

	}



	rotation_matix = getRotationMatrix2D(center, -8, 1.0);
	warpAffine(matImgrotated, matImgrotated, rotation_matix, matImgrotated.size());
	namedWindow("Orginal Image", WINDOW_FULLSCREEN);
	imshow("Orginal Image", matImgrotated);
	




	waitKey(0);
	return 0;
}





