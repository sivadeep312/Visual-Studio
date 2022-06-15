#include <opencv2/opencv.hpp>
#include <iostream>
#include<vector>
#include <string>

using namespace std;
using namespace cv;

double getOrientation(const vector<Point>& pts, double& angle)
{
	int sz = static_cast<int>(pts.size());
	Mat data_pts = Mat(sz, 2, CV_64F);
	for (int i = 0; i < data_pts.rows; i++)
	{
		data_pts.at<double>(i, 0) = pts[i].x;
		data_pts.at<double>(i, 1) = pts[i].y;
	}


	PCA pca_analysis(data_pts, Mat(), PCA::DATA_AS_ROW);

	Point cntr = Point(static_cast<int>(pca_analysis.mean.at<double>(0, 0)),
		static_cast<int>(pca_analysis.mean.at<double>(0, 1)));


	vector<Point2d> eigen_vecs(2);
	vector<double> eigen_val(2);
	for (int i = 0; i < 2; i++)
	{
		eigen_vecs[i] = Point2d(pca_analysis.eigenvectors.at<double>(i, 0),
			pca_analysis.eigenvectors.at<double>(i, 1));

		eigen_val[i] = pca_analysis.eigenvalues.at<double>(i);
	}


	angle = atan2(eigen_vecs[0].y, eigen_vecs[0].x);
	angle = angle * (180 / 3.14159265);
	return angle;
}

double get_angle(Mat& matImgThresh, double& angle1) {

	vector<vector<Point>> vecContours;
	vector<Vec4i> vecHierarchy;
	findContours(matImgThresh, vecContours, vecHierarchy, RETR_TREE, CHAIN_APPROX_NONE);

	vector<double>angles;
	for (int i = 0; i < vecContours.size(); i++) {
		double angle;
		getOrientation(vecContours[i], angle);
		angles.push_back(angle);
	}

	double angle_sum = 0;
	sort(angles.begin(), angles.end());
	for (int i = 0; i < angles.size(); i++) {
		angle_sum = angle_sum + angles[i];
	}
	angle1 = angle_sum / angles.size();
	//angle1 = (angle1-90);
	
	cout << angles[angles.size()-1]<<endl;
	cout << angles[0]<<endl;
	cout << angle1 << endl;
	return angle1;
}


int main()
{
	Mat matImg = imread("Res/TestImage1.png", IMREAD_COLOR);
	Mat matImgGray, matMaskRed, matImgThresh;
	Mat matImagepad;
	Point Pdiff;
	copyMakeBorder(matImg, matImagepad, 50, 50, 50, 50, BORDER_CONSTANT, Scalar(0));

	if (matImagepad.channels() == 3) {
		cvtColor(matImagepad, matImgGray, COLOR_BGR2GRAY);
	}

	threshold(matImgGray, matImgThresh, 40, 255, 0);
	
	vector<vector<Point> > vecContours;
	vector<Vec4i> vecHierarchy;
	findContours(matImgThresh, vecContours, vecHierarchy, RETR_TREE, CHAIN_APPROX_NONE);
	Mat matImgThreshcl = matImgThresh.clone();

	Mat Z = Mat::zeros(matImgThreshcl.size(), CV_8UC1);
	
	for (int i = 0; i < vecContours.size() - 1; i++) {
		for (int j = i + 1; j < vecContours.size(); j++) {
			for (int k = 0; k < vecContours[i].size(); k++) {
				if (k < vecContours[j].size()) {
					if (abs((vecContours[i][k].y - vecContours[j][k].y) < 4) && abs((vecContours[i][k].x - vecContours[j][k].x) < matImg.rows)) {
						line(Z, vecContours[i][k], vecContours[j][k], Scalar::all(255), 1, LINE_AA);
					}
				}
			}
		}
	}
	imshow("sd", Z);
	double angle;
	get_angle(Z, angle);

	Point2f center((matImagepad.cols - 1) / 2.0, (matImagepad.rows - 1) / 2.0);
	Mat rotation_matix = getRotationMatrix2D(center, angle, 1.0);
	Mat matImgrotated;
	warpAffine(matImagepad, matImgrotated, rotation_matix, matImagepad.size());
	warpAffine(matImgThresh, matImgThresh, rotation_matix, matImgThresh.size());


	vector<vector<Point>>vecContours1;
	findContours(matImgThresh, vecContours1, RETR_TREE, CHAIN_APPROX_NONE);


	vector<Point>pts;

	if(angle>0){
		for (int i = 0; i < vecContours1.size(); ++i) {
			pts.push_back(vecContours1[i][0]);
		}
		vector<vector<Point>> vecOuter;
		vector<Point> vecInner;

		for (int i = 0; i < pts.size() - 1; i++) {
			vecInner.push_back(pts[i]);
			if (abs(pts[i].y - pts[i + 1].y) > 2) {
				vecOuter.push_back(vecInner);
				vecInner.clear();
			}
			if (i == pts.size() - 2) {
				vecInner.push_back(pts[i + 1]);
				vecOuter.push_back(vecInner);
				vecInner.clear();
			}
		}
		vector<Point>vecitr;
		for (int i = 0; i < vecOuter.size(); i++) {
			for (int j = 0; j < vecOuter[i].size(); j++) {
				vecitr.push_back(vecOuter[i][j]);
			}
		}
		cout << vecitr.size() << endl << endl;

		for (int i = 0; i < vecitr.size(); ++i) {

			int k = vecitr.size() - i;
			putText(matImgrotated, to_string(k), vecitr[i], FONT_ITALIC, .5, Scalar(255, 255, 255), 1, 8);

		}
	}

	else {
		for (int i = 0; i < vecContours1.size(); ++i) {
			pts.push_back(vecContours1[i][0]);
		}
		vector<vector<Point>> vecOuter;
		vector<Point> vecInner;

		for (int i = 0; i < pts.size() - 1; i++) {
			vecInner.push_back(pts[i]);
			if (abs(pts[i].y - pts[i + 1].y) > 2) {
				vecOuter.push_back(vecInner);
				vecInner.clear();
			}
			if (i == pts.size() - 2) {
				vecInner.push_back(pts[i + 1]);
				reverse(vecInner.begin(), vecInner.end());
				vecOuter.push_back(vecInner);
				vecInner.clear();
			}
		}
		vector<Point>vecitr;
		for (int i = 0; i < vecOuter.size(); i++) {
			for (int j = 0; j < vecOuter[i].size(); j++) {
				vecitr.push_back(vecOuter[i][j]);
			}
		}
		cout << vecitr.size() << endl << endl;

		for (int i = 0; i < vecitr.size(); ++i) {

			int k = vecitr.size() - i;
			putText(matImgrotated, to_string(k), vecitr[i], FONT_ITALIC, .5, Scalar(255, 255, 255), 1, 8);

		}
	}



	Point2f center1((matImgrotated.cols - 1) / 2.0, (matImgrotated.rows - 1) / 2.0);
	rotation_matix = getRotationMatrix2D(center, -angle, 1.0);
	warpAffine(matImgrotated, matImgrotated, rotation_matix, matImgrotated.size());
	namedWindow("Orginal Image", WINDOW_FULLSCREEN);
	imshow("Orginal Image", matImgrotated);
	
	/*Mat matCropped_image = matImgrotated(Range(25, icol + 50), Range(25, irow + 50));

	namedWindow("Orginal Image", WINDOW_FULLSCREEN);
	imshow("Orginal Image", matCropped_image);*/


	waitKey(0);
	return 0;
}




