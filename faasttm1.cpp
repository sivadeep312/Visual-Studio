#include <cstdint>
#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>

//#define TEST_FILE(x) "../" x

using namespace cv;
using namespace std;

template <typename Num>
inline Num sq(Num x) { return x * x; }


cv::Mat convolveDFT(const cv::Mat& MatImage, const cv::Mat& matTemplate) {
	cv::Mat matImage64;
	cv::Mat matTemplate64;
	//cv::Mat result;
	//GaussianBlur(MatImage, matImage64, Size(3, 3), 0, 0);
	MatImage.convertTo(matImage64, CV_64F);
	matTemplate.convertTo(matTemplate64, CV_64F);
	flip(matTemplate64, matTemplate64, -1);
	cv::Size dftSize;
	dftSize.width = cv::getOptimalDFTSize(matImage64.cols);
	dftSize.height = cv::getOptimalDFTSize(matImage64.rows);
	cv::Mat tempA(dftSize, matImage64.type(), cv::Scalar::all(0));
	cv::Mat tempB(dftSize, matTemplate64.type(), cv::Scalar::all(0));
	matImage64.copyTo(tempA(Rect(0,0, matImage64.cols, matImage64.rows)));
	matTemplate64.copyTo(tempB(Rect(0, 0, matTemplate64.cols, matTemplate64.rows)));
	//cv::Mat roiA(tempA, cv::Rect(0, 0, matImage64.cols, matImage64.rows));
	//matImage64.copyTo(roiA);
	//cv::Mat roiB(tempB, cv::Rect(0, 0, matTemplate64.cols, matTemplate64.rows));
	//matTemplate64.copyTo(roiB);
	dft(tempA, tempA, 0, matImage64.rows);
	dft(tempB, tempB, 0, matTemplate64.rows);
	mulSpectrums(tempA, tempB, tempA, cv::DFT_COMPLEX_OUTPUT);
	dft(tempA, tempA, cv::DFT_INVERSE | cv::DFT_SCALE, matImage64.rows);
	//tempA(cv::Rect(0, 0, matImage64.cols, matImage64.rows)).copyTo(result);
	return tempA(cv::Rect(0, 0, matImage64.cols, matImage64.rows));
}

Rect FFTTemplateMatching(
	/*INOUT*/	Mat& matReferenceImage,
	/*INOUT*/	Mat& matTemplateImage,
	/*INOUT*/	float& fMatchLocX,
	/*INOUT*/   float& fMatchLocY,
	/*OUT*/		double& dMatchingScore) {


	if (matReferenceImage.empty() || matTemplateImage.empty()) {

		return Rect();
	}

	if (matReferenceImage.channels() > 3)
	{
		cvtColor(matReferenceImage, matReferenceImage, COLOR_BGRA2GRAY);
	}
	else if (matReferenceImage.channels() == 3)
	{
		cvtColor(matReferenceImage, matReferenceImage, COLOR_BGR2GRAY);
	}
	if (matTemplateImage.channels() > 3)
	{
		cvtColor(matTemplateImage, matTemplateImage, COLOR_BGRA2GRAY);



	}
	else if (matTemplateImage.channels() == 3)
	{
		cvtColor(matTemplateImage, matTemplateImage, COLOR_BGR2GRAY);
	}





	//matReferenceImage = matReferenceImage - mean(matReferenceImage)[0];
	//matTemplateImage = matTemplateImage - mean(matTemplateImage)[0];

	int refrows = matReferenceImage.rows;
	int refcols = matReferenceImage.cols;
	int tmprows = matTemplateImage.rows;
	int tmpcols = matTemplateImage.cols;

	Mat matRowsum;
	reduce(matReferenceImage, matRowsum, 1, REDUCE_SUM, CV_32SC1);
	matRowsum=matRowsum.mul(matRowsum);
	vector<vector<int64_t>>sqsum(refrows, std::vector<int64_t>(refcols, 0));

	//int64_t** sqsum = new int64_t * [matReferenceImage.rows + 1];



//#pragma omp parallel for
//	for (int y = 0; y < refrows + 1; y++)
//		sqsum[y] = new int64_t[refcols + 1];
//
//	fill(sqsum[0], sqsum[0] + refcols + 1, 0);
//
//	int64_t row_sum;

	for (int y = 0; y < refrows; y++) {
		sqsum[y + 1][0] = 0;
		uchar* uptr = matReferenceImage.ptr<uchar>(y);
		for (int x = 0; x < matReferenceImage.cols; x++) {
			sqsum[y + 1][x + 1] = matRowsum.at<int>(y,x) + sqsum[y][x + 1];
		}
	}
	//Note down execution time with and without omp
	//Make it block and Report which block taking more exexcution time

	auto third_term = [&](int y, int x) {
		return sqsum[y + 1][x + 1]				//sqsum[tmprows+1][tmpcols+1]
			- sqsum[y - tmprows][x + 1]			//-sqsum[0][tmpcols+1]
			- sqsum[y + 1][x - tmpcols]			//-sqsum[tmprows+1][0]
			+ sqsum[y - tmprows][x - tmpcols];	//+sqsum[0][0]
	};




	Mat matconvolved = convolveDFT(matReferenceImage, matTemplateImage);



	//Mat dummy = matReferenceImage.clone();
	Point minP, maxP;
	double minv, maxv;
	minMaxLoc(matconvolved,&minv,&dMatchingScore,&minP,&maxP);
	//if (dummy.channels() < 3) {
	//	cvtColor(dummy, dummy, COLOR_GRAY2BGR);
	//}
	//rectangle(dummy, Rect(1568, 1572, 1248, 1744), Scalar(255, 255), 10, 16);
	//circle(dummy, minP, 10, 255, 5, 16);
	//circle(dummy, maxP, 10,Scalar(0,0 ,255), 5, 16);
	//circle(dummy, Point(maxP.x - 1248, maxP.y - 1744), 10, Scalar(0, 255, 255), -1);
	//namedWindow("Dummy", WINDOW_FREERATIO);
	//imshow("Dummy", dummy);
	//waitKey();
	//double min_diff = std::numeric_limits<double>::max();


	double min_diff = INFINITY;
	int min_y = 0;
	int min_x = 0;


	for (int y = tmprows; y < refrows; y++) {
		double* dptr = matconvolved.ptr<double>(y);
		for (int x = tmpcols; x < refcols; x++) {
			double u = matconvolved.at<double>(y, x);
			dMatchingScore = -2 * (dptr[x]) + static_cast<double>(third_term(y, x));
			if (dMatchingScore < min_diff) {
				min_diff = dMatchingScore;
				min_y = y;
				min_x = x;
			}
		}
	}


//#pragma omp parallel for	
//	for (int y = 0; y < refrows; y++)
//		delete[] sqsum[y];
//	delete[] sqsum;

	fMatchLocX = min_x - matTemplateImage.cols; //maxP.x; //min_x - matTemplateImage.cols;
	fMatchLocY = min_y - matTemplateImage.rows;// maxP.y;// min_y - matTemplateImage.rows;
	Rect region(fMatchLocX- matTemplateImage.cols, fMatchLocY- matTemplateImage.rows, matTemplateImage.cols, matTemplateImage.rows);
	return(region);
}


int main() {
	/*INOUT*/	float fMatchLocX;
	/*INOUT*/   float fMatchLocY;
	/*OUT*/		double dMatchingScore;

    cv::Mat refimage = cv::imread("Wafer_X=10_Y=10.jpeg", cv::IMREAD_COLOR);
    cv::Mat image = cv::imread("Wafer.jpeg", cv::IMREAD_COLOR);
	cv::Mat stencil = refimage(cv::Rect(1848, 1752, 1560, 1176));
	cvtColor(stencil, stencil, COLOR_BGR2GRAY);
	
	cv::Mat cl = image.clone();
    cv::Mat cl3 = image.clone();
    cv::Mat cl2 = image.clone();

    cv::cvtColor(cl, cl, cv::COLOR_BGR2GRAY);
 
	Mat clcl = cl.clone();

	
	
	//Mat matResult;// (cl.size() - stencil.size(), CV_32FC1);

	std::chrono::time_point<std::chrono::system_clock> start1, end1;
	start1 = std::chrono::system_clock::now();
	cv::Rect region = FFTTemplateMatching(cl, stencil, fMatchLocX, fMatchLocY, dMatchingScore);
	
	end1 = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end1 - start1;
	std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
	
	//
	//std::chrono::time_point<std::chrono::system_clock> start, end;
	//start = std::chrono::system_clock::now();
	//int iresult_cols = clcl.cols - stencil.cols + 1;
	//int iresult_rows = clcl.rows - stencil.rows + 1;
	//Mat matResult(iresult_rows, iresult_cols, CV_32FC1);
	//matchTemplate(clcl, stencil, matResult, 2);
	//Point minP(0,0), maxP(0,0);
	//double minv=0, maxv=0;
	//minMaxLoc(matResult, &minv, &maxv, &minP, &maxP);
	//end = std::chrono::system_clock::now();
	//std::chrono::duration<double> elapsed_seconds1 = end - start;
	//std::cout << "elapsed time: " << elapsed_seconds1.count() << "s\n";

	/*
	cv::rectangle(cl3, Rect(maxP.x, maxP.y, stencil.cols, stencil.rows), cv::Scalar{ 0, 255, 255 }, 10);
	cv::namedWindow("Mat", cv::WINDOW_FREERATIO);
	cv::imshow("Mat", cl3);
	cv::waitKey();*/


   
    
    std::fstream fout;
    fout.open("time.csv", std::ios::out | std::ios::app);
    fout << elapsed_seconds.count() << std::endl;

    fout.clear();
    fout.close();
	
	
	cv::rectangle(image, region, cv::Scalar{ 255 }, 10);
    cv::namedWindow("Mat", cv::WINDOW_FREERATIO);
    cv::imshow("Mat", image);
    cv::waitKey();


  
    return 0;
}