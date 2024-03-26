//
// Created by admin on 2021/7/7.
//几何变换
#include <opencv2/opencv.hpp>

using namespace std;
//https://blog.csdn.net/y601500359/article/details/100096813

int main(){
    cv::Mat img = cv::imread("/Users/bijh/Documents/gaoshan.jpg");
    cv::Mat dst;
    cv::cvtColor(img,dst,cv::COLOR_BGR2GRAY);
    cv::imshow("src",img);
    cv::imshow("dst",dst);
    cv::waitKey(0);
    cv::destroyAllWindows();
}
