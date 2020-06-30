//
// Created by zf on 2020/5/7.
//

#ifndef DARKENET_C_IMGPROCESS_H
#define DARKENET_C_IMGPROCESS_H


#include<opencv2/opencv.hpp>

void imgConvert(const cv::Mat& img, float* dst);

void imgResize(float* src, float* dst,int srcWidth,int srcHeight,int dstWidth,int dstHeight);

void resizeInner(float *src, float* dst,int srcWidth,int srcHeight,int dstWidth,int dstHeight);


#endif //DARKENET_C_IMGPROCESS_H
