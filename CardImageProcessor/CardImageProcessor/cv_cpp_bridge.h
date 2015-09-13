#ifndef __CVCPPBRIDGE_H
#define __CVCPPBRIDGE_H

#ifdef __cplusplus
#include <opencv2/opencv.hpp>
extern "C" {
#endif
#include <Python.h>

char** process_image(cv::Mat) ;

typedef struct CardInfo CardInfo;

CardInfo *process_image2(char*);
#ifdef __cplusplus
}
#endif
#endif
