#include<opencv2/opencv.hpp>

using namespace cv;

double MidPoint2CenterAngle(Point2f PMidPoint, Point2f PCenter) {
    double Mid2CenterAngle = atan2(PCenter.y - PMidPoint.y, PCenter.x - PMidPoint.x);
    Mid2CenterAngle = Mid2CenterAngle * 180 / CV_PI;
    return Mid2CenterAngle;
}


double FindSlopeAngle(Point2f P1, Point2f P2, bool& bTop) {
    double dslope = (P1.y - P2.y) / (P1.x - P2.x);
    double dSlopeAngle = atan2(P1.y - P2.y, P1.x - P2.x);
    dSlopeAngle = dSlopeAngle * 180 / CV_PI;

    if (dslope > 0) {
        bTop = true;
    }  
    else { bTop = false; }
    return dSlopeAngle;

}





void ZVAlignmentTrain(Point2f P1, Point2f P2, Point2f PROICenter, double& dIntialSlopeAngle, double& dROIMidPointDistance, double& dIntaialROIMidPointAngle,bool &bTop) {
   
    Point2f PMidPointLine = (P1 + P2) / 2;
   
    dIntialSlopeAngle = FindSlopeAngle(P1, P2, bTop);
    dROIMidPointDistance = norm(PMidPointLine - PROICenter);
    dIntaialROIMidPointAngle = MidPoint2CenterAngle(PMidPointLine, PROICenter);

 
}

void ZVROIAlignment(Point2f P1, Point2f P2,  double dIntialSlopeAngle, double dROIMidPointDistance, double dROIMidPointAngleIntial, bool bTop, Point2f& PRoiCenterPoint, double& dRotationAngle) {

    bool bTop_ = false;
    double dFinalSlopeAngle = FindSlopeAngle(P1, P2, bTop_);



    
    double dROIMidPointAngleFinal = (dFinalSlopeAngle - dIntialSlopeAngle) + dROIMidPointAngleIntial;

    if (bTop != bTop_) {
        dROIMidPointAngleFinal += 180;
    }
    Point2f PMidPointFinal = (P1 + P2) / 2;

    PRoiCenterPoint;
    PRoiCenterPoint.x = PMidPointFinal.x + dROIMidPointDistance * cos(dROIMidPointAngleFinal * CV_PI / 180);
    PRoiCenterPoint.y = PMidPointFinal.y + dROIMidPointDistance * sin(dROIMidPointAngleFinal * CV_PI / 180);

   dRotationAngle =  dROIMidPointAngleIntial- dROIMidPointAngleFinal;

    //py::tuple new_tuple = py::make_tuple(make_tuple(PRoiCenterPoint.x, PRoiCenterPoint.y), dRotationAngle);
    //return new_tuple;

}

int main() {


    Point A(10, 2);
    Point B(4, 4);
    Point C(10,8);
 
    double dIntialSlopeAngle, dROIMidPointDistance, dIntaialROIMidPointAngle;
    bool bcal = false;
    ZVAlignmentTrain(A, B, C, dIntialSlopeAngle, dROIMidPointDistance, dIntaialROIMidPointAngle,bcal);

    Point2f D(3.9, 2.6);
   // Point2f E(9.5,5);
    Point2f E(10.1,3.4);
   
    Point2f PRoiCenterPoint; double dRotationAngle;
    ZVROIAlignment(D, E, dIntialSlopeAngle, dROIMidPointDistance, dIntaialROIMidPointAngle, bcal, PRoiCenterPoint, dRotationAngle);

    return 0;
}