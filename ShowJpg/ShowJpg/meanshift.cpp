#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include<cstdio>
#include <iostream>
#include<meanshift.h>
#include<stdafx.h>
using namespace cv;
using namespace std;
static void floodFillPostprocess(Mat& img, const Scalar& colorDiff = Scalar::all(1))
{
	CV_Assert(!img.empty());
	RNG rng = theRNG();
	Mat mask(img.rows + 2, img.cols + 2, CV_8UC1, Scalar::all(0));
	int flag = 0;
	for (int y = 0; y < img.rows; y++)
	{
		for (int x = 0; x < img.cols; x++)
		{
			if (mask.at<uchar>(y + 1, x + 1) == 0)
			{
				if (!flag){
					flag++;
					Scalar newVal(rng(0), rng(0), rng(0));
					floodFill(img, mask, Point(x, y), newVal, 0, colorDiff, colorDiff);
				}
				else{
					Scalar newVal(rng(256), rng(256), rng(256));
					floodFill(img, mask, Point(x, y), newVal, 0, colorDiff, colorDiff);
				}
			}
		}
	}
}
void meanshift::pro(Mat img, Mat res, string w)
{
	Mat ress;
	Mat bimg = res;
	pyrMeanShiftFiltering(img, ress, 75, 75, 1);
	floodFillPostprocess(ress, Scalar::all(2));
	Mat	srcImage2 = bimg;
	Mat srcImage3 = ress;
	threshold(srcImage3, srcImage3, 170, 255, CV_THRESH_BINARY);
	for (int i = 0; i < srcImage3.rows; i++){
		for (int j = 0; j < srcImage3.cols; j++){
			if (srcImage3.at<Vec3b>(i, j)[0] == 0 && srcImage3.at<Vec3b>(i, j)[1] == 0 && srcImage3.at<Vec3b>(i, j)[2] == 0){
				srcImage2.at<Vec3b>(i, j)[0] = srcImage3.at<Vec3b>(i, j)[0];
				srcImage2.at<Vec3b>(i, j)[1] = srcImage3.at<Vec3b>(i, j)[0];
				srcImage2.at<Vec3b>(i, j)[2] = srcImage3.at<Vec3b>(i, j)[0];
			}
		}
	}
	imwrite("C:\\Users\\Administrator\\Desktop\\课程设计\\自然场景下显著目标的提取\\test\\Saliency\\1_" + w + "_MS.jpg", srcImage2);

}
