#include <opencv2/opencv.hpp>
#include <iostream>
#include<vector>

using namespace std;
using namespace cv;

bool ObjectDetectionTM(Mat& mat_Input, Mat& mat_Temp, double dthreshold, bool bmultipledetection = false) {

	Mat matImgClone = mat_Input.clone();
	int iresult_cols = mat_Input.cols - mat_Temp.cols + 1;
	int iresult_rows = mat_Input.rows - mat_Temp.rows + 1;
	Mat matResult(iresult_rows, iresult_cols, CV_32FC1);
	Mat matS(mat_Input.rows, mat_Input.cols, CV_8UC1,Scalar::all(0));
	matchTemplate(mat_Input, mat_Temp, matResult, TM_CCORR_NORMED);
	double minVal=0, maxVal=0, threshold;
	Point minLoc; Point maxLoc;
	minMaxLoc(matResult, &minVal, &maxVal, &minLoc, &maxLoc);
	normalize(matResult, matResult, 0, 1, NORM_MINMAX, -1, Mat());

	vector<vector<Point>>vecContours;
	vector<double>per;
	double avg=0;
	double sum=0;
	int count = 0;
	for (int i = 0; i < matResult.rows; i++) {
		for (int j = 0; j < matResult.cols; j++) {
			if (matResult.at<float>(i, j) > dthreshold) {
				per.push_back((matResult.at<float>(i, j)));
				sum = (matResult.at<float>(i, j)) + sum;
				count++;
				Point A = Point(j, i);
				Point B = Point(j+ mat_Temp.cols, i+ mat_Temp.rows);
				if (B.y > matS.rows) {
					B.y = matS.rows;
				}
				if (B.x > matS.cols) {
					B.x = matS.cols;
				}
				rectangle(matImgClone, A, B, Scalar(0,255), 2, 16, 0);
				matS.at<uchar>(i, j) = 255;
			}
		}
	}
	avg = sum / count;
	cout << "Average Matching : " << endl;
	findContours(matS, vecContours, RETR_LIST, CHAIN_APPROX_NONE);
	cout << "No of Matchings : " << vecContours.size() << endl;

	namedWindow("Matchings", WINDOW_GUI_NORMAL);
	imshow("Matchings", matImgClone);
	waitKey(0);		//Enter value

	if (vecContours.size() > 0) {
		return true;
	}
	else {
		return false;
	}
}

int main() {

	Mat matImage = imread("Res/chess.png", IMREAD_COLOR);
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
	}

	cout << boolalpha;
	bool bsuccess = ObjectDetectionTM(matImage, matTemp, 0.95);
	cout << "Multiple Matching : " << bsuccess << endl;

}