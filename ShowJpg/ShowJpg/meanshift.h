#include<cv.h>
#include<cstdio>
#include<stdafx.h>
#ifndef MEANSHIFT_H
#define MEANSHIFT_H
class meanshift{
public:
	void pro(cv::Mat img, cv::Mat res, std::string w);
};

#endif