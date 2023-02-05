#include<iostream>
#include<opencv2/opencv.hpp>


using namespace std;
using namespace cv;

int main() {

	Mat MatInputImage,MatHSV;

	cvtColor(MatInputImage, MatHSV, COLOR_BGR2HSV);

	vector<int>veciH(180,0);
	for (int i = 0; i < MatHSV.rows; i++) {
		for (int j = 0; j < MatHSV.cols; j++) {			
			veciH[(int)MatHSV.at<Vec3b>(i,j)[0]]++;
		}
	}
	int iHmax=0;
	for (int i = 0; i < 180; i++) {
		if (veciH[i] > iHmax)
			iHmax = i;
	}

	int iHRangemin = 190, iHRangeMax = 0;
	int iHRangemin1 = 190, iHRangeMax1 = 0;
	int iSRangemin = 260, iSRangeMax = 0;
	int iVRangemin = 260, iVRangeMax = 0;
	for (int i = 0; i < MatHSV.rows; i++) {
		for (int j = 0; j < MatHSV.cols; j++) {
			int iHval = (int)MatHSV.at<Vec3b>(i, j)[0];
			int iHmin_ = iHmax - 5;
			int iHmax_ = iHmax + 5;

			//if (iHmin_ < 0) {
			//	if ((0 <= iHval) && (iHval<iHmax_)) {
			//		iHRangemin
			//	}

			//	else if ((180 + iHmin_ < iHmax) && (iHmax>180)) {

			//	}

			}
			
			//if(iHval-5>)


		}
	}



}