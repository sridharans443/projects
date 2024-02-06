/*
 * hikv_camera.hpp
 *
 *  Created on: 15-Sep-2019
 *      Author: guna007
 */

#ifndef HIKV_CAMERA_HPP_
#define HIKV_CAMERA_HPP_

#include <stdint.h>
#include <iostream>
#include <bits/stdc++.h>
#include <opencv2/opencv.hpp>

#include "MvCameraControl.h"

//using namespace std;
using namespace cv;

class HIKVCamera
{

public:
	HIKVCamera();
	~HIKVCamera();
	int openCamera(int idx = 0);
	int openCamera(std::string serial_no);
	int closeCamera();
	int configureCapture(int capture_mode, uint16_t width, uint16_t height, uint16_t x_offset, uint16_t y_offset, bool ae_mode, float ae_time, bool white_balance,
		int high_value, int low_value);
	int startCapture();
	int stopCapture();
	int getImage(Mat& img, int timeout=200);
	int toggleline1(int timeout=200);
	int toggleline2(int timeout=200);

	static int list_devices(std::vector<std::string> &devices);
private:
	uint16_t width;
	uint16_t height;
	uint8_t *bufPtr;
	uint32_t format;
	void *dev_handle;
	bool isInitialized;
	size_t imgSize;
	bool isTrigged;
	bool isCapStarted;
	MV_FRAME_OUT_INFO_EX stImageInfo;
};



#endif /* HIKV_CAMERA_HPP_ */

