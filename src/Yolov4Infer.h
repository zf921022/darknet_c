//
// Created by zf on 2020/5/12.
//

#ifndef YOLO_YOLOV4INFER_H
#define YOLO_YOLOV4INFER_H

#include "obstacledetect.h"
#include "YoloConfig.h"
#include<opencv2/opencv.hpp>
#include "darknet.h"

using namespace cv;

struct YoloDetectObject {
    float objectProb;
    float maxclassProb;
    int maxProbClassIndex;
    std::string maxProbClassName;
    int left;//pixel index
    int right;//pixel index
    int top;//pixel index
    int bot;//pixel index
    int width;//pixel index
    int height;//pixel index
};



class Yolov4Infer {
public:

    void yolov4infer(cv::Mat &inputRgbImage, int width, int height,
                     std::vector<YoloDetectObject> &dets);

private:
    YoloConfig m_param;
    network net = *load_network((char*)m_param.cfgfile.c_str(),(char*)m_param.weightfile.c_str(),0);
};



#endif //YOLO_YOLOV4INFER_H
