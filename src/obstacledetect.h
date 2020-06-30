//
// Created by junyi on 4/7/20.
//

#ifndef OBSTACLEDETECT_H
#define OBSTACLEDETECT_H

#include <vector>
#include <memory>

namespace obstacle {
    // 深度图, data[row * width + col]表示第row行第col列的距离, 单位是米(m).
    typedef float *DRIVER_DEPTH_IMAGE;

    typedef u_int8_t *DRIVER_RGB_IMAGE;

    //相机内参
    struct DRIVER_CAMERA_PARAM {
        int width;     /**< Width of the image in pixels */
        int height;    /**< Height of the image in pixels */
        float fX;
        float fY;//Focal length of the image plane,as a mutipe of pixel width
        float fPpx;
        float fPpy;//Horizontal and Vertical coordinate of the principal point of the image
    };
    struct DRIVER_CAMERA_POS_ANGLE {
        //在相机安装在机器人正前方时
        //相机向下倾斜的角度,范围0~pi/2. 相机水平向前为0, 相机垂直朝地面为pi/2.
        float angle;
        //相机原点坐标相对于机器人原点坐标的偏移, 在机器人坐标系下
        float fx, fy, fz;
    };
    struct DRIVER_CAMERA_POS_QUATERNION {
        //在相机相对于机器人坐标任意姿态时, 用四元素表示相机姿态
        //w,x,y,x = 1,0,0,0 时表示相机水平向前
        float qw, qx, qy, qz;
        //相机原点坐标相对于机器人原点坐标的偏移, 在机器人坐标系下
        float fx, fy, fz;
    };

    struct STRU_Point3D {
        float fX = 0;
        float fY = 0;
        float fZ = 0;
    };

    // 以图像左上角为原点的坐标系
    struct STRU_ImageArea {
        unsigned int uiLlefttopRow; //row
        unsigned int uiLlefttopCol; //col
        unsigned int uiHight;
        unsigned int uiWidth;
    };

    // 一个障碍物的信息
    struct STRU_ObstacleData //AI数据
    {
        STRU_ImageArea depthImagePosition; // 障碍物在深度图片中的矩形框
        STRU_ImageArea rgbImagePosition;    // 障碍物在rgb图片中的矩形框
        float angle;                      // 障碍物相对于机器人的角度,左边90度为-pi/2 ,右边90度为pi/2
        float distance;                      // 识别物体距离最近距离
        STRU_Point3D centerPoint3D;
        STRU_Point3D point3Ds[8];         // 机器人坐标系下障碍物晶格8个顶点坐标
        std::string objectType;           //只在gpu版本有用
    };

    class ObstacleDetectorImpl;

    class ObstacleDetector {
    public:
        //第1种构造方式, 传入相机向下倾斜的角度的相机姿态和相机内参(简单情况)
        explicit ObstacleDetector(const DRIVER_CAMERA_POS_ANGLE &pos,
                                  const DRIVER_CAMERA_PARAM &depthParam,
                                  const DRIVER_CAMERA_PARAM &rgbParam);

        //第2种构造方式, 传入相机相对机器人姿态四元素和相机内参(复杂姿态情况)
        explicit ObstacleDetector(const DRIVER_CAMERA_POS_QUATERNION &pos,
                                  const DRIVER_CAMERA_PARAM &depthParam,
                                  const DRIVER_CAMERA_PARAM &rgbParam);

        std::vector<STRU_ObstacleData> detectObstacle(DRIVER_DEPTH_IMAGE &inputDepthImage,
                                                      DRIVER_RGB_IMAGE &inputRgbImage);

    private:
        std::shared_ptr<ObstacleDetectorImpl> detectorImpl;
    };
}

#endif //OBSTACLEDETECT_H
