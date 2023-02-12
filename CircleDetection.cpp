#include"ColorRangeFinder.h"


class CircleFeatures {

public:
	Scalar HSV_;
	pair<Scalar, Scalar> HSVRange_;
	Point2f PCenter;
	float fCircularity;
	float fRadius;
	double dArea;
	Mat TmpImages;

	CircleFeatures() : PCenter(-1.0f, -1.0f), fCircularity(0.0f), fRadius(0.0f), dArea(0) {}

};


CircleFeatures TmplCircleFeatures(cv::Mat matImage) {

    cv::Mat MatImgHSV, MatInRange;
    cvtColor(matImage, MatImgHSV, COLOR_BGR2HSV);
    Mat matImgHSVClone = MatImgHSV.clone();

    float fCircularitymin = -1.f;
    float fRadiusFinal = -1.0; Point2f PCircleCenter;
    CircleFeatures CircObj;
    for (int i = 0; i < 3; i++) {

        cv::Scalar maxvals = HSVSegment(MatImgHSV);
        inRange(MatImgHSV, Scalar(maxvals[0] - 5, maxvals[1] - 80, maxvals[2] - 90), Scalar(maxvals[0] + 5, maxvals[1] + 80, maxvals[2] + 90), MatInRange);

        morphologyEx(MatInRange, MatInRange, MORPH_CLOSE, getStructuringElement(MORPH_RECT, Size(4, 4)));
        vector<vector<Point>>vecContours;
        findContours(MatInRange, vecContours, RETR_LIST, CHAIN_APPROX_NONE);


        if (vecContours.size() != 0) {
            for (int j = 0; j < vecContours.size(); j++) {

                if (vecContours[j].size() > 25) {
                    double dArea = contourArea(vecContours[j]);
                    Point2f PCircleCeneterContour(-1.0f, -1.0f);
                    float fRadiusCircle = 0;
                    minEnclosingCircle(vecContours[j], PCircleCeneterContour, fRadiusCircle);
                    float fCircularity = 4 * CV_PI * dArea / ((2 * CV_PI * fRadiusCircle) * (2 * CV_PI * fRadiusCircle));

                    if (fCircularity >= fCircularitymin) {
                        fCircularitymin = fCircularity;

                        fRadiusFinal = fRadiusCircle;
                        PCircleCenter = PCircleCeneterContour;

                    }
                }
            }
            vecContours.clear();
        }
        else {
            MatInRange.release();
            break;
        }


        bitwise_not(MatInRange, MatInRange);
        cvtColor(MatInRange, MatInRange, COLOR_GRAY2BGR);
        bitwise_and(MatImgHSV, MatInRange, MatImgHSV);

        MatInRange.release();

    }
    MatInRange.release();
    MatImgHSV.release();

    Mat matCircle(matImage.size(), CV_8UC3, Scalar::all(0));
    circle(matCircle, PCircleCenter, fRadiusFinal*1.1, Scalar::all(255), -1);
    //namedWindow("Win", WINDOW_FREERATIO);
    //imshow("Win", matImgHSVClone);
    //waitKey();
    bitwise_and(matImgHSVClone, matCircle, matImgHSVClone);
    matCircle.release();

    Scalar SNewHSV = HSVSegment(matImgHSVClone);
    inRange(matImgHSVClone, Scalar(SNewHSV[0] - 5, SNewHSV[1] - 40, SNewHSV[2] - 50), Scalar(SNewHSV[0] + 5, SNewHSV[1] + 40, SNewHSV[2] + 50), MatInRange);
    //namedWindow("Win", WINDOW_FREERATIO);
    //imshow("Win", matImgHSVClone);
    //waitKey();
    vector<vector<Point>>vecContours;

    findContours(MatInRange, vecContours, RETR_LIST, CHAIN_APPROX_NONE);
    fCircularitymin = -1.0f;
    for (int j = 0; j < vecContours.size(); j++) {
        if (vecContours[j].size() > 25) {

            double dArea = contourArea(vecContours[j]);
            Point2f PCircleCeneterContour(-1.0f, -1.0f);
            float fRadiusCircle = 0;
            minEnclosingCircle(vecContours[j], PCircleCeneterContour, fRadiusCircle);
            float fCircularity = 4 * CV_PI * dArea / ((2 * CV_PI * fRadiusCircle) * (2 * CV_PI * fRadiusCircle));

            if (fCircularity >= fCircularitymin) {
                fCircularitymin = fCircularity;

                CircObj.fRadius = fRadiusCircle;
                CircObj.PCenter = PCircleCeneterContour;
                CircObj.dArea = dArea;
                CircObj.fCircularity = fCircularity;

            }
        }
    }

    CircObj.HSV_ = SNewHSV;

    bitwise_not(MatInRange, MatInRange);
    cvtColor(MatInRange, MatInRange, COLOR_GRAY2BGR);
    Mat matTemplate;
    bitwise_and(matImage, MatInRange, matTemplate);
    cout << CircObj.HSV_ << CircObj.PCenter;
    circle(matImage, CircObj.PCenter, CircObj.fRadius, Scalar(0, 255), 2);
    namedWindow("Win", WINDOW_FREERATIO);
    imshow("Win", matTemplate);
    waitKey();

    CircObj.TmpImages = matTemplate.clone();
    matImgHSVClone.release();


    return CircObj;

    
}

int main() {

	//Mat matTmpImage = imread(R"(C:\Users\Sivadeep\Downloads\attachments (1)\IMG_23_Feb_07_18_41_32.676450.bmp)", 1), MatHSVImage;
    //Mat matTmpImage = imread(R"(C:\Users\Sivadeep\Downloads\attachments (1)\IMG_23_Feb_07_18_42_06.849854_.bmp)", 1), MatHSVImage;
    //Mat matTmpImage = imread(R"(C:\Users\Sivadeep\Downloads\attachments (1)\IMG_23_Jan_24_15_09_02.019438.bmp)", 1), MatHSVImage;
    Mat matTmpImage = imread(R"(C:\Users\Sivadeep\Downloads\attachments (1)\IMG_23_Jan_24_15_05_37.973498.bmp)", 1), MatHSVImage;

    TmplCircleFeatures(matTmpImage);

	//cvtColor(matTmpImage, MatHSVImage, COLOR_BGR2HSV);






	return 0;
}