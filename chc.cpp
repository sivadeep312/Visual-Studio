#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main() {



	string image_path1 = "Res/Input.png";
	Mat img = imread(image_path1, IMREAD_COLOR);
	resize(img, img, { 500,500 });
	//imshow("Orginal Image", img);
	Mat thr, gray;
	cvtColor(img, gray, COLOR_BGR2GRAY);
	inRange(gray, Scalar(0, 255, 255), Scalar(180, 255, 255), thr);
	threshold(imgThreshold, binaryImg, 0, 255, THRESH_BINARY);
	threshold(gray, thr, 100, 255, THRESH_BINARY);
	//imshow("gray Image", gray);
	//imshow("thresh Image", thr);
	Moments m = moments(thr, true);
	Point p(m.m10 / m.m00, m.m01 / m.m00);
	// coordinates of centroid
	cout << Mat(p) <<endl;
	// show the image withapoint mark at the centroid
	circle(img, p, 5, Scalar(128, 0, 0), -1);
	imshow("Image with center", img);


	//blob centers multiple

	Mat canny_output;
	vector<vector<Point>>contours;
	vector<Vec4i> hierarchy;
	// detect edges using canny
	Canny(gray, canny_output, 50, 150, 3);
	// find contours
	findContours(canny_output, contours, hierarchy, RETR_TREE,
		CHAIN_APPROX_SIMPLE, Pointe, e) );
		// get the moments
		vector<Moments> mu(contours.size());
		for (inti = 0; i < contours.size(); i++)
		{
			mu[i] = moments(contours[i], false);
		}
		// get the centroid of figures.
		vector<Point2f> mc(contours.size());
		for (inti = 0; iccontours.size(); i++)
		{
			mc[i] = Point2f(mu[i].m10 / mu[i].m@e, mu[i].m@1 / mu[i].mee);
		}
		// draw contours
		Mat drawing(canny_output.size(), CV_8UC3, Scalar(255, 255, 255));
		for (inti = 0; i < contours.size(); i++)
		{
			Scalar color = Scalar(167, 151, 0); //BGR values
			drawContours(drawing, contours, i, color, 2, 8, hierarchy, e, Point());
			circle(drawing, mc[i], 4, color, -1, 8, e);
		}
		// show the resultant image
		namedwindow("Contours", WINDOW_AUTOSIZE);
		imshow("Contours", drawing);
		waitkey(0);
	waitKey(0);
	return 0;
}