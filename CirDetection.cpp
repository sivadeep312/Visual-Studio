#include"ColorRangeFinder.h"
#include <chrono>
#include <ctime>

class ZVOutputClass
{
public:
    bool iResult;
    string sErrorCode;
    Point2f PCenter;

    float fCircularity;
    float fRadius;
    int iDistance;
    float fTmplThreshold;



    ZVOutputClass() :iResult(0), sErrorCode("Class Created for Result"), PCenter(-1.0f, -1.0f), fCircularity(0.0f), fRadius(0.0f), iDistance(0), fTmplThreshold(0) {}

    void Assign(bool successFlag, string errorCode)
    {
        iResult = successFlag;
        sErrorCode = errorCode;
    }

};



class CircleFeatures {

public:
    Scalar HSV_;
	Point2f PCenter;
	float fCircularity;
	float fRadius;
	double dArea;
    Mat TmpImages;
    int iConcentricValue;

	CircleFeatures() : PCenter(-1.0f, -1.0f), fCircularity(0.0f), fRadius(0.0f),dArea(0), iConcentricValue(0){}

};


//CircleFeatures TmplCircleFeatures(Mat matTmpImage) {
//
//    Mat matHSVImage;
//    cvtColor(matTmpImage, matHSVImage, COLOR_BGR2HSV);
//    vector<Scalar>vecHSVs = HSVSegments(matHSVImage);
//    float fCircularitymin = -1.f;
//    float fRadiusFinal = -1.0; Point2f PCircleCenter;
//    Scalar HSVFin;
//    for (int i = 0; i < 3; i++) {
//        Scalar HSVRange = vecHSVs[i];
//        Mat matInRange;
//        inRange(matHSVImage, Scalar(HSVRange[0] - 5, HSVRange[1] - 30, HSVRange[2] - 75), Scalar(HSVRange[0] + 5, HSVRange[1] + 40, HSVRange[2] + 75), matInRange);
//        CircleFeatures CircObj;
//
//        vector<vector<Point>>vecContours;
//        findContours(matInRange, vecContours, RETR_LIST, CHAIN_APPROX_NONE);
//       // int iContourMinSize = 0.1*matHSVImage.rows* matHSVImage.cols;
//       int iContourMinSize = 80;
//
//        namedWindow("Win", WINDOW_FREERATIO);
//        imshow("Win", matInRange);
//        waitKey();
//
//        for (int s = 0; s < vecContours.size(); s++) {
//            if (vecContours[s].size() > iContourMinSize) {
//                Mat DrawCon(matInRange.size(), CV_8UC1, Scalar(0));
//                drawContours(DrawCon, vecContours, s, Scalar(255), 1);
//                //namedWindow("Win", WINDOW_FREERATIO);
//                //imshow("Win", DrawCon);
//                //waitKey();
//                double dArea = contourArea(vecContours[s]);
//                Point2f PCircleCeneterContour(-1.0f, -1.0f);
//                float fRadiusCircle = 0;
//                minEnclosingCircle(vecContours[s], PCircleCeneterContour, fRadiusCircle);
//                //circle(matTmpImage, PCircleCenter, fRadiusFinal, Scalar(0, 255), 2);
//                namedWindow("Win", WINDOW_FREERATIO);
//                imshow("Win", matTmpImage);
//                waitKey();*/
//                float fCircularity = 4 * CV_PI * dArea / ((2 * CV_PI * fRadiusCircle) * (2 * CV_PI * fRadiusCircle));
//
//                if (fCircularity >= fCircularitymin) {
//                    fCircularitymin = fCircularity;
//
//                    fRadiusFinal = fRadiusCircle;
//                    PCircleCenter = PCircleCeneterContour;
//                    HSVFin = vecHSVs[i];
//                }
//            }
//
//                
//        }     
//
//    }
//    circle(matTmpImage, PCircleCenter, fRadiusFinal, Scalar(0, 255), 2);
//    namedWindow("Win", WINDOW_FREERATIO);
//    imshow("Win", matTmpImage);
//    waitKey();
//
// 
//    return CircleFeatures();
// }
    
    

int HollowCircleCheck(Mat MatBinaryImage,float iRadius, Point2f PCenter) {


    vector<int>vecWhitePoints;
    int iCircleTopPoint = (int)(PCenter.x - iRadius);
    int iCircleBottomPoint = (int)(PCenter.x + iRadius);

    for (int r = iCircleTopPoint; r < iCircleBottomPoint; r++) {
        int iMatVal = (int)MatBinaryImage.at<uchar>(r, 0);
        if (iMatVal == 255) {
            vecWhitePoints.push_back(r);
        }
    }

    int iAdjacentDistance = 0;
    for (int i = 1; i < vecWhitePoints.size(); i++) {
        int iDistance = vecWhitePoints[i] - vecWhitePoints[i - 1];
        if (iDistance > 3) {

            iAdjacentDistance = iDistance;

        }
    }

    return iAdjacentDistance;


}


    



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
    circle(matCircle, PCircleCenter, fRadiusFinal * 1.1, Scalar::all(255), -1);
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

    //namedWindow("Win", WINDOW_FREERATIO);
    //imshow("Win", MatInRange);
    //waitKey();
    CircObj.iConcentricValue = HollowCircleCheck(MatInRange.col((int)PCircleCenter.x),CircObj.fRadius,CircObj.PCenter);
    bitwise_not(MatInRange, MatInRange);

    cvtColor(MatInRange, MatInRange, COLOR_GRAY2BGR);
    Mat matTemplate;
    bitwise_and(matImage, MatInRange, matTemplate);
    
    //cout << CircObj.HSV_ << CircObj.PCenter;
    circle(matImage, CircObj.PCenter, CircObj.fRadius, Scalar(0, 255), 2);
    //namedWindow("Win", WINDOW_FREERATIO);
    //imshow("Win", matTemplate);
    //waitKey();

    CircObj.TmpImages = matTemplate.clone();
    matImgHSVClone.release();


    return CircObj;

}



ZVOutputClass newFunc(cv::Mat matInputImage, Scalar HSVRange, double dAreaThresholdLower, float fCircularityThreshold, float fRadiusInput,int iConcentricValue, Mat MatTemplateImage = Mat(), float dTempThreshold = 0) {

    ZVOutputClass OutObj;

    try {
        float fradiusContourLower=0.7* fRadiusInput;
        float fradiusContourUpper=1.3*fRadiusInput;
        Mat MatHSVImage, MatRange;
        cvtColor(matInputImage, MatHSVImage, COLOR_BGR2HSV);
        inRange(MatHSVImage, Scalar(HSVRange[0] - 5, HSVRange[1] - 30, HSVRange[2] - 50), Scalar(HSVRange[0] + 5, HSVRange[1] + 30, HSVRange[2] + 50), MatRange);
        if (iConcentricValue == 0) {
            morphologyEx(MatRange, MatRange, MORPH_CLOSE, getStructuringElement(MORPH_RECT, Size(5, 5)));
        }


        vector<vector<Point>>vecContours;
        findContours(MatRange, vecContours, RETR_LIST, CHAIN_APPROX_NONE);

        
        float fTmpMin = dTempThreshold;
        
        for (int j = 0; j < vecContours.size(); j++) {
            if (vecContours[j].size() > 25) {
                double dArea = contourArea(vecContours[j]);

                Point2f pCircleCeneterContour;
                float fradiusContour = 0.0f;

                if (dArea > dAreaThresholdLower) {
                    minEnclosingCircle(vecContours[j], pCircleCeneterContour, fradiusContour);
                    float fCircularity = 4 * CV_PI * dArea / ((2 * CV_PI * fradiusContour) * (2 * CV_PI * fradiusContour));

                    if ((fradiusContour > fradiusContourLower && fradiusContour < fradiusContourUpper) && (fCircularity > fCircularityThreshold)) {


                        int iradiusbuffer = fradiusContour * 1.1;
                        int iX = pCircleCeneterContour.x - iradiusbuffer;
                        int iY = pCircleCeneterContour.y - iradiusbuffer;



                        //int iConcentricCheck = HollowCircleCheck(MatRange(Rect(iX, iY, 2 * iradiusbuffer, 2*iradiusbuffer)), fRadiusInput, pCircleCeneterContour);
                        //namedWindow("Win", WINDOW_FREERATIO);
                        //imshow("Win", MatRange(Rect(pCircleCeneterContour.x, pCircleCeneterContour.y, 0, iradiusbuffer + 10)));
                        //waitKey();



                        if (iX < 0) {
                            iX = 0;
                        }

                        if (iY < 0) {
                            iY = 0;
                        }

                        if (!MatTemplateImage.empty()) {

                            int iTX = pCircleCeneterContour.x - MatTemplateImage.cols / 2;
                            int iTY = pCircleCeneterContour.y - MatTemplateImage.rows / 2;

                            if ((iTX + MatTemplateImage.cols < matInputImage.cols) && (iTY + MatTemplateImage.rows < matInputImage.rows)) {

                                if ((iTX >= 0) && (iTY >= 0)) {

                                    Mat TmpCheck = matInputImage(Rect(iTX, iTY, MatTemplateImage.cols, MatTemplateImage.rows)).clone();
                                    Mat MatMask(TmpCheck.size(), CV_8UC3, Scalar(0, 0, 0));
                                    Mat MatCircle = MatRange(Rect(iTX, iTY, MatTemplateImage.cols, MatTemplateImage.rows)).clone();
                                    bitwise_not(MatCircle, MatCircle);
                                    cvtColor(MatCircle, MatCircle, COLOR_GRAY2BGR);
                                    bitwise_and(TmpCheck, MatCircle, MatMask);

                                    Mat MatResult;
                                    matchTemplate(MatMask, MatTemplateImage, MatResult, TM_CCORR_NORMED);
                                    float fTmpval = MatResult.at<float>(0, 0);


                                    TmpCheck.release();
                                    MatMask.release();
                                    MatCircle.release();
                                    MatResult.release();



                                    if (fTmpval >= fTmpMin) {


                                        if (fTmpMin != dTempThreshold) {

                                            //fCircularityThreshold = fCircularity;
                                        }

                                        fTmpMin = fTmpval;

                                        OutObj.iResult = 1;
                                        OutObj.Assign(true, "No Error");
                                        OutObj.fCircularity = fCircularity;
                                        OutObj.fRadius = fradiusContour;
                                        OutObj.PCenter = pCircleCeneterContour;
                                        OutObj.fTmplThreshold = fTmpval;



                                    }

                                }
                            }
                        }

                        else {
                            fCircularityThreshold = fCircularity;
                            OutObj.iResult = 1;
                            OutObj.Assign(true, "No Error");
                            OutObj.fCircularity = fCircularity;
                            OutObj.fRadius = fradiusContour;
                            OutObj.PCenter = pCircleCeneterContour;

                        }


                    }


                }

            }
        }


        return OutObj;


    }

    catch (...) {

        OutObj.Assign(false, "Error Catched");
        return OutObj;
    }

}




//Add Concentric Circle Check to THIS




int main() {


	//Mat matTmpImage = imread(R"(C:\Users\Sivadeep\Downloads\attachments (1)\IMG_23_Jan_24_15_09_02.019438.bmp)", 1),MatHSVImage;
	//Mat matTmpImage = imread(R"(C:\Users\Sivadeep\Downloads\attachments (1)\IMG_23_Jan_24_15_05_37.973498.bmp)", 1),MatHSVImage;
	Mat matTmpImage = imread(R"(C:\Users\Sivadeep\Downloads\attachments (1)\IMG_23_Feb_07_18_41_32.676450.bmp)", 1),MatHSVImage;
	//Mat matTmpImage = imread(R"(C:\Users\Sivadeep\Downloads\attachments (1)\IMG_23_Feb_07_18_42_06.849854_.bmp)", 1),MatHSVImage;
    std::chrono::time_point<std::chrono::system_clock> start, end;

    start = std::chrono::system_clock::now();
    CircleFeatures TmpFea = TmplCircleFeatures(matTmpImage);
    end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end - start;
    //cout << endl << endl << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl << endl;
    //cout <<"Time   :  "<< elapsed_seconds.count()<<endl;
    //std::time_t end_time = std::chrono::system_clock::to_time_t(end);

  
    
  

   //circle(matTmpImage, TmpFea.PCenter, TmpFea.fRadius, Scalar(0, 0, 0), -1);
	
    vector<string>vecNames,vecNameImg1,vecNameImg2;
   
    glob(R"(C:\Users\Sivadeep\Downloads\attachments\*.bmp)", vecNames);
    char ccheck = '1';
    for (int i = 0; i < vecNames.size(); i++) {

        if (vecNames[i][43] == ccheck) {
            vecNameImg1.push_back(vecNames[i]);
        }
        else {
            vecNameImg2.push_back(vecNames[i]);
        }
    }

    for (int i = 0; i < vecNameImg1.size(); i++) {

        //cout << i << endl;
        //Mat InpImage = imread(R"(C:\Users\Sivadeep\Downloads\attachments\Img11675775512.9944744.bmp)", 1);
        //Mat InpImage = imread(R"(C:\Users\Sivadeep\Downloads\attachments (1)\IMG_23_Jan_24_15_05_02.244911.bmp)", 1);
        //Mat InpImage = imread(R"(C:\Users\Sivadeep\Downloads\attachments (1)\IMG_23_Jan_24_15_05_02.244911.bmp)", 1);
       Mat InpImage = imread(vecNameImg2[i], 1);
        std::chrono::time_point<std::chrono::system_clock> start, end;

        start = std::chrono::system_clock::now();
        ZVOutputClass outobj = newFunc(InpImage, TmpFea.HSV_, TmpFea.dArea * 0.6, TmpFea.fCircularity * 0.6, TmpFea.fRadius,TmpFea.iConcentricValue, TmpFea.TmpImages, 0.75);
        end = std::chrono::system_clock::now();

        std::chrono::duration<double> elapsed_seconds = end - start;
        cout << endl << endl << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl << endl;
        cout << "Time   :  " << elapsed_seconds.count() << endl;

//,matTmpImage,0.75

        if (!outobj.iResult) {
            cout << endl << endl << "###############################" << endl << endl;
            cout << i << "  "<<outobj.sErrorCode<<endl;
        }

        circle(InpImage, outobj.PCenter, outobj.fRadius, Scalar(0, 255), 2);
        circle(InpImage, outobj.PCenter, 1, Scalar(0, 0,255), -1);


        namedWindow("Win", WINDOW_FREERATIO);
        imshow("Win", InpImage);
        waitKey();
    }



 
	return 0;
}