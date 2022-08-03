#include <opencv2/opencv.hpp>
#include <iostream>
#include<vector>
#include <algorithm>

using namespace std;
using namespace cv;

typedef Point3_<uint8_t> Pixel;



int main() {
	time_t tstart, tstop;
	Mat matImage = imread("Res/Image.png", IMREAD_COLOR);
	if (matImage.empty())
	{
		cout << "Could not read the image: " << endl;
		return 1;
	}
	Mat matTemp = imread("Res/Template.png", IMREAD_COLOR);
	if (matTemp.empty())
	{
		cout << "Could not read the Template Image: " << endl;
		return 1;
	}
	int itempl = matTemp.rows;
	int itempw = matTemp.cols;
	Mat matresult(matImage.rows - itempl, matImage.rows - itempl, CV_32F);
	time(&tstart);
	double sumim;
	double sumtemp=sum(matTemp)[0]+ sum(matTemp)[1]+ sum(matTemp)[2];
	int forsu = 0;
	int ifsu = 0;
	
	for (int i = 0; i < matImage.rows - itempl; i++) {
		for (int j = 0; j < matImage.cols - itempw; j++) {
			//forsu++;
			Rect roi(j, i, itempl, itempw);
			//sumim=sum(matImage(roi))[0]+ sum(matImage(roi))[1]+ sum(matImage(roi))[2];
			//if (sumim == sumtemp) {
				//cout << "Found" << endl;
				//ifsu++;
			//}
			//matresult.at<float>(i,j)=
		}
	}
	time(&tstop);
	cout<<"Time :"<< double(tstop - tstart)<<endl;
	//cout << forsu << "," << ifsu << endl;
	//matchTemplate();
}