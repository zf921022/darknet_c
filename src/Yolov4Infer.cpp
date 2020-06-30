//
// Created by zf on 2020/5/12.
//

#include "Yolov4Infer.h"
#include "imgprocess.h"
#include "darknet.h"



//network * Yolov4Infer::loadNetwork(char* cfgfile, char* weightfile){
//    network *net=load_network((char*) cfgfile,(char*) weightfile,0);
//    return net;
//}

void Yolov4Infer::yolov4infer(cv::Mat &inputRgbImage, int width, int height,
                          std::vector<YoloDetectObject> &dets){

//    network *net=load_network((char*)m_param.cfgfile.c_str(),(char*)m_param.weightfile.c_str(),0);
//    network *net = Yolov4Infer::loadNetwork((char*)m_param.cfgfile.c_str(), (char*)m_param.weightfile.c_str());
    float* srcImg;
    float* resizeImg;
    size_t srcSize=width*height*3*sizeof(float);
    srcImg=(float*)malloc(srcSize);
    imgConvert(inputRgbImage,srcImg);//将图像转为yolo形式

    size_t resizeSize=net.w*net.h*3*sizeof(float);
    resizeImg=(float*)malloc(resizeSize);
    imgResize(srcImg,resizeImg,inputRgbImage.cols,inputRgbImage.rows,net.w,net.h);//缩放图像

    network_predict(net,resizeImg);//网络推理
    int nboxes=0;
    detection *dets1= get_network_boxes(&net, inputRgbImage.cols, inputRgbImage.rows, m_param.OBJECT_THRESH, 0.5, 0, 1, &nboxes,1);
    do_nms_sort(dets1,nboxes,m_param.CLASS_NUM, m_param.NMS_THRESH);

//    std::cout << nboxes << std::endl;

    YoloDetectObject det;

    for (int i = 0; i < nboxes; i++){
        bool flag=0;
        det.maxclassProb = 0;
        for(int j=0;j<m_param.CLASS_NUM;j++){
//            std::cout << dets1[i].prob[j] << std::endl;
            if(dets1[i].prob[j]>m_param.OBJECT_THRESH){
                if(!flag){
                    flag=1;
                    if(dets1[i].prob[j]> det.maxclassProb) {
                        det.maxProbClassName = m_param.classNames[j];
                        det.maxProbClassIndex = j;
                        det.maxclassProb = dets1[i].prob[j];
                        det.objectProb = dets1[i].objectness;
                    }
                }
            }
        }
        if(flag){
            det.left = (dets1[i].bbox.x - dets1[i].bbox.w / 2.)*inputRgbImage.cols;
            det.right = (dets1[i].bbox.x + dets1[i].bbox.w / 2.)*inputRgbImage.cols;
            det.top = (dets1[i].bbox.y - dets1[i].bbox.h / 2.)*inputRgbImage.rows;
            det.bot = (dets1[i].bbox.y + dets1[i].bbox.h / 2.)*inputRgbImage.rows;

            if (det.left < 0)
                det.left = 0;
            if (det.right > inputRgbImage.cols - 1)
                det.right = inputRgbImage.cols - 1;
            if (det.top < 0)
                det.top = 0;
            if (det.bot > inputRgbImage.rows - 1)
                det.bot = inputRgbImage.rows - 1;

//            Rect box(left, top, fabs(left - right), fabs(top - bot));
            det.width = det.right - det.left;
            det.height = det.bot - det.top;
        }
        if (det.maxclassProb > m_param.OBJECT_THRESH)
            dets.push_back(det);
    }

    free_detections(dets1, nboxes);
    free(srcImg);
    free(resizeImg);
//    free_network(*net);
}
