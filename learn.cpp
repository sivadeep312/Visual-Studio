#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;



int main()
{

    string image_path1 = "Res/Input.png";

    Mat gray;// Create a Matrix for storing coordinates and pixel values

    Mat ima = imread(image_path1, IMREAD_COLOR);
    resize(ima, ima, { 500,500 });
    imshow("image", ima);

    cvtColor(ima, gray, COLOR_BGR2GRAY);
 
    //Columns and Rows
    int y = ima.cols; //No of columns
    int x = ima.rows; //No of rows
    
    //Pixel values
    
    int b= ima.at<Vec3b>(0, 0)[0];//blue pixel value at (0,0)
    int g= ima.at<Vec3b>(0, 0)[1];//green pixel value at (0,0)
    int r = ima.at<Vec3b>(0, 0)[2];//red pixel value at (0,0)

    Scalar c ;//4 variable array but only three is needed
    c[0] = r;
    c[1] = g;
    c[2] = b;
    cout << "color" << c;
   


    cout << "No of rows :" << x<<" / n";
    cout <<"No of coloumns :"<< y;

    cout << "Red pixel value" << r;
    cout << "Green Pixel value" << g;
    cout << "blue pixel value" << b;
    waitKey(0);

   
  
    
    return 0;
}