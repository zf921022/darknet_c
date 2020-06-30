//
// Created by zf on 2020/5/7.
//
#include<iostream>
#include<opencv4/opencv2/opencv.hpp>
#include "darknet.h"
#include "Yolov4Infer.h"
#include <time.h>

using namespace std;
using namespace cv;

float colors[6][3] = { {1,0,1}, {0,0,1},{0,1,1},{0,1,0},{1,1,0},{1,0,0} };

float get_color(int c, int x, int max){
    float ratio = ((float)x/max)*5;
    int i = floor(ratio);
    int j = ceil(ratio);
    ratio -= i;
    float r = (1-ratio) * colors[i][c] + ratio*colors[j][c];
    return r;
}

int main(){
    VideoCapture capture(0);
//    VideoCapture capture("/home/zf/yolo/darknet-master/data/dog.jpg");
    Mat frame;
    Mat rgbImg;
    bool stop= false;
    clock_t start, end;
    double dur;

    Yolov4Infer yolov4Infer;

    while(!stop){
        if (!capture.read(frame)){
            printf("fail to read.\n");
            return 0;
        }
        cvtColor(frame, rgbImg, cv::COLOR_BGR2RGB);
    start = clock();
    std::vector<YoloDetectObject> dets;
    yolov4Infer.yolov4infer(rgbImg, rgbImg.cols, rgbImg.rows,
                dets);
    for(auto& det:dets){
        cout << det.maxProbClassName << endl;
        int offset = det.maxProbClassIndex*123457 % 1;
        float red = 255*get_color(2,offset,1);
        float green = 255*get_color(1,offset,1);
        float blue = 255*get_color(0,offset,1);
        Rect box(det.left, det.top, fabs(det.left - det.right), fabs(det.top - det.bot));
        rectangle(frame,box,Scalar(blue,green,red),2);

        String label = det.maxProbClassName;
        int baseLine = 0;
        Size labelSize = getTextSize(label, FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
        putText(frame, label, Point(box.x, box.y + labelSize.height),
                FONT_HERSHEY_SIMPLEX, 1, Scalar(red, blue, green),2);
    }
    namedWindow("video", 0);
    imshow("video",frame);
    cout << "inference done..." << endl;
    end = clock();
    dur = (double) (end - start);
    cout << "inference Time:" << (dur/CLOCKS_PER_SEC *1000) << "ms" << endl;
        int c=waitKey(10);
        if((char)c==27)
            break;
        else if(c>=0)
            waitKey(0);
    }
    capture.release();
    return 1;
}