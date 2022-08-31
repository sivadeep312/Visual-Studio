#include <cstdint>
#include <iostream>
#include <opencv2/opencv.hpp>

//#define TEST_FILE(x) "../" x

template <typename Num>
inline Num sq(Num x) { return x * x; }

cv::Mat convolveDFT(const cv::Mat& image, const cv::Mat& stencil) {
    cv::Mat im;
    cv::Mat tpl;
    cv::Mat result;
    image.convertTo(im, CV_64F);
    stencil.convertTo(tpl, CV_64F);
    cv::flip(tpl, tpl, -1);
    cv::Size dftSize;
    dftSize.width = cv::getOptimalDFTSize(im.cols);
    dftSize.height = cv::getOptimalDFTSize(im.rows);
    cv::Mat tempA(dftSize, im.type(), cv::Scalar::all(0));
    cv::Mat tempB(dftSize, tpl.type(), cv::Scalar::all(0));
    cv::Mat roiA(tempA, cv::Rect(0, 0, im.cols, im.rows));
    im.copyTo(roiA);
    cv::Mat roiB(tempB, cv::Rect(0, 0, tpl.cols, tpl.rows));
    tpl.copyTo(roiB);
    cv::dft(tempA, tempA, 0, im.rows);
    cv::dft(tempB, tempB, 0, tpl.rows);
    cv::mulSpectrums(tempA, tempB, tempA, cv::DFT_COMPLEX_OUTPUT);
    cv::dft(tempA, tempA, cv::DFT_INVERSE | cv::DFT_SCALE, im.rows);
    tempA(cv::Rect(0, 0, im.cols, im.rows)).copyTo(result);
    return result;
}

cv::Mat multipleChannelConvolve(const cv::Mat& im, const cv::Mat& tpl) {

    cv::Mat conv;
    conv = convolveDFT(im, tpl);
    return conv;
}

cv::Rect fastTemplateMatch(const cv::Mat& image, const cv::Mat stencil) {
    auto** sqsum = new int64_t * [image.rows + 1];
    for (int y = 0; y < image.rows + 1; y++)
        sqsum[y] = new int64_t[image.cols + 1];
    std::fill(sqsum[0], sqsum[0] + image.cols + 1, 0);
    for (int y = 1; y < image.rows + 1; y++) {
        int64_t row_sum = sqsum[y][0] = 0;
        for (int x = 1; x < image.cols + 1; x++) {
            uchar vec = image.at<uchar>(y - 1, x - 1);
            row_sum += sq<int64_t>(vec);// +sq<int64_t>(vec[1]) + sq<int64_t>(vec[2]);
            sqsum[y][x] = row_sum + sqsum[y - 1][x];
        }
    }
    auto third_term = [&](int y, int x) {
        return sqsum[y + 1][x + 1]
            - sqsum[y - stencil.rows][x + 1]
            - sqsum[y + 1][x - stencil.cols]
            + sqsum[y - stencil.rows][x - stencil.cols];
    };
    cv::Mat convolved = multipleChannelConvolve(image, stencil);
    double min_diff = std::numeric_limits<double>::max();
    int min_y = 0;
    int min_x = 0;
    for (int y = stencil.rows; y < image.rows; y++) {
        for (int x = stencil.cols; x < image.cols; x++) {
           double u = convolved.at<double>(y, x);
            double diff = -2 * (u ) + static_cast<double>(third_term(y, x));
            if (diff < min_diff) {
                min_diff = diff;
                min_y = y;
                min_x = x;
            }
        }
    }
    for (int y = 0; y < image.rows; y++)
        delete[] sqsum[y];
    delete[] sqsum;
    std::clog << "minimal difference is " << min_diff << '\n';
    std::clog << "x = " << min_x - stencil.cols << ", y = " << min_y - stencil.rows << '\n';
    return cv::Rect{ min_x - stencil.cols, min_y - stencil.rows, stencil.cols, stencil.rows };
}


int main() {


    cv::Mat image = cv::imread("A.png", cv::IMREAD_COLOR);

    cv::Mat cl = image.clone();
    cv::Mat cl2 = image.clone();

    cv::cvtColor(cl, cl, cv::COLOR_BGR2GRAY);
 
    cv::Mat stencil = cv::imread("B.png", 0);
    std::chrono::time_point<std::chrono::system_clock> start, end;

    start = std::chrono::system_clock::now();
    cv::Rect region = fastTemplateMatch(cl, stencil);
    cv::rectangle(image, region, cv::Scalar{ 255, 255, 255 }, 10);

    end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end - start;

    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n" << std::endl<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl << std::endl;;

    cv::namedWindow("Mat", cv::WINDOW_FREERATIO);
    cv::imshow("Mat", image);
    cv::waitKey();


  
    return 0;
}