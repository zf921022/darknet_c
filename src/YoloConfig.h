//
// Created by junyi on 4/21/20.
//

#ifndef OBSTACLEDETECTORGPUSDK_YOLOCONFIG_H
#define OBSTACLEDETECTORGPUSDK_YOLOCONFIG_H
#include <vector>
#include <string>

struct YoloConfig {
//    std::string onnxPath = "../engine/yolov3-tiny-416.onnx";
//    std::string enginePath = "../engine/yolov3-tiny-416.engine";
//
//    int IMG_C = 3;
//    int IMG_W = 416;
//    int IMG_H = 416;
//
//
//    int CLASS_NUM = 80;
//    float OBJECT_THRESH = 0.5;
//    float NMS_THRESH = 0.3;
//    int BATCH_SIZE = 1;
//
//    std::vector<int> GRID_BBOX_SIZE{13, 26};
//    std::vector<int> outputBboxSize{BATCH_SIZE * 3 * (4 + 1 + CLASS_NUM) * GRID_BBOX_SIZE[0] * GRID_BBOX_SIZE[0],
//                                    BATCH_SIZE * 3 * (4 + 1 + CLASS_NUM) * GRID_BBOX_SIZE[1] * GRID_BBOX_SIZE[1]};


    std::string cfgfile = "/home/zf/yolo/darknet-master/cfg/yolov4.cfg";
    std::string weightfile = "/home/zf/yolo/darknet-master/yolov4.weights";

    std::string onnxPath = "../engine/yolov3_608_tensorrt6_fp32_x86_64.onnx";
    std::string enginePath = "../engine/yolov3_608_tensorrt6_fp32_x86_64.engine";

    int IMG_C = 3;
    int IMG_W = 608;
    int IMG_H = 608;


    int CLASS_NUM = 80;
    float OBJECT_THRESH = 0.5;
    float NMS_THRESH = 0.3;
    int BATCH_SIZE = 1;

    std::vector<int> GRID_BBOX_SIZE{19, 38, 76};
//    std::vector<int> GRID_BBOX_SIZE{10, 20, 40};
    std::vector<int> outputBboxSize{BATCH_SIZE * 3 * (4 + 1 + CLASS_NUM) * GRID_BBOX_SIZE[0] * GRID_BBOX_SIZE[0],
                                    BATCH_SIZE * 3 * (4 + 1 + CLASS_NUM) * GRID_BBOX_SIZE[1] * GRID_BBOX_SIZE[1],
                                    BATCH_SIZE * 3 * (4 + 1 + CLASS_NUM) * GRID_BBOX_SIZE[2] * GRID_BBOX_SIZE[2]};




    //int grid_index, int k
    std::vector<std::vector<float>> anchorsX{{116.0, 156.0, 373.0},
                                             {30.0,  62.0,  59.0},
                                             {10.0,  16.0,  33.0}};
    std::vector<std::vector<float>> anchorsY{{90.0, 198.0, 326.0},
                                             {61.0, 45.0,  119.0},
                                             {13.0, 30.0,  23.0}};

    std::vector<std::string> classNames{
            "person",
            "bicycle",
            "car",
            "motorbike",
            "aeroplane",
            "bus",
            "train",
            "truck",
            "boat",
            "traffic light",
            "fire hydrant",
            "stop sign",
            "parking meter",
            "bench",
            "bird",
            "cat",
            "dog",
            "horse",
            "sheep",
            "cow",
            "elephant",
            "bear",
            "zebra",
            "giraffe",
            "backpack",
            "umbrella",
            "handbag",
            "tie",
            "suitcase",
            "frisbee",
            "skis",
            "snowboard",
            "sports ball",
            "kite",
            "baseball bat",
            "baseball glove",
            "skateboard",
            "surfboard",
            "tennis racket",
            "bottle",
            "wine glass",
            "cup",
            "fork",
            "knife",
            "spoon",
            "bowl",
            "banana",
            "apple",
            "sandwich",
            "orange",
            "broccoli",
            "carrot",
            "hot dog",
            "pizza",
            "donut",
            "cake",
            "chair",
            "sofa",
            "pottedplant",
            "bed",
            "diningtable",
            "toilet",
            "tvmonitor",
            "laptop",
            "mouse",
            "remote",
            "keyboard",
            "cell phone",
            "microwave",
            "oven",
            "toaster",
            "sink",
            "refrigerator",
            "book",
            "clock",
            "vase",
            "scissors",
            "teddy bear",
            "hair drier",
            "toothbrush"
    };
};
#endif //OBSTACLEDETECTORGPUSDK_YOLOCONFIG_H
