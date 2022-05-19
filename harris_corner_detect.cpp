#include <opencv2/opencv.hpp>
#include <iostream>
#include<cmath>


using namespace cv;
using namespace std;

const double pi = 3.14159265358979323846;

int main()
{
	vector<Point> crd;
	Mat image, gray;

	Mat output, output_norm, output_norm_scaled;
	image = imread("Res/Rect.png", IMREAD_COLOR);
	resize(image, image, { 500,500 });
	Mat F = image.clone();
	Mat G = image.clone();
	if (image.empty()) {
		cout << "Error loading image" << endl;
	}
	//imshow("Original image", image);
	cvtColor(image, gray, COLOR_BGR2GRAY);


	/////////////////////////////////## HARRIS CORNER DETECTION ##/////////////////////////////////////////////////
	

	output = Mat::zeros(image.size(), CV_32FC1);
	cornerHarris(gray, output, 2.5, 3, 0.0001, BORDER_DEFAULT);

	normalize(output, output_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
	convertScaleAbs(output_norm, output_norm_scaled);

	
	/////////////////////////////////## DRAWING CORNER POINTS ##/////////////////////////////////////////////////

	for (int j = 0; j < output_norm.rows; j++) {
		for (int i = 0; i < output_norm.cols; i++) {
			if ((int)output_norm.at<float>(j, i) > 100) {
				circle(F, Point(i, j), 4, Scalar(0, 0, 255), 2, 8, 0);
				crd.push_back(Point(i, j));
			}
		}
	}
	//imshow("Output Harris", F);
	
	///////////////////////////////// ## REMOVING CLOSE POINTS ##/////////////////////////////////////////////////

	int k = crd[0].x;
	int l = crd[0].y;
	vector<Point>Coord;
	Coord.push_back(crd[0]);
	for (size_t i = 0; i < crd.size(); i++) {
		if ((abs(k - crd[i].x) > 4) && (abs(l - crd[i].y) > 4)) {
			Coord.push_back(crd[i]);
			k = crd[i].x;
			l = crd[i].y;
		}
	}
	//cout << Coord << "\n";
	for (auto Coords : Coord) {
		G.at<Vec3b>(Coords)[0] = 255;
		G.at<Vec3b>(Coords)[1] = 255;
		G.at<Vec3b>(Coords)[2] = 255;
		//cout << endl << Coords<<endl;
	}

	/////////////////////////////////## SORTING THE POINTS ##/////////////////////////////////////////////////


	for (int i = 0; i < Coord.size(); i++){
		for (int j = i ; j < Coord.size()-1; j++){
			if (Coord[i].y > Coord[j].y){
				Point temp = Coord[i];
				Coord[i] = Coord[j];
				Coord[j] = temp;
			}
		}
	}
	cout << endl;
	//cout << Coord<<endl << endl;

	/////////////////////////////////## FINDING THE ANGLE ## /////////////////////////////////////////////////
	
	double X_crd = Coord[1].x - Coord[0].x;
	double Y_crd = Coord[1].y - Coord[0].y;
	double inv = Y_crd / X_crd;
	double angle = atan(inv) * 180 / pi;

	cout << "\n\n\n\n"<<" The Angle of Rotation is : " << angle << "\n\n\n\n";
	

	/////////////////////////////////## DISPLAYING THE RESULT  ##/////////////////////////////////////////////////
	
	//imshow("Image", F);
	
	waitKey(0);
	return 0;

}