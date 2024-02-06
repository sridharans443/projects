/*MvCameraControl
 * hikv_camera.cpp
 *
 *  Created on: 15-Sep-2019
 *      Author: guna007
 */

#include "hikv_camera.hpp"
unsigned char *mfgname = NULL;

MV_CC_DEVICE_INFO_LIST find_devices()
{
	MV_CC_DEVICE_INFO_LIST stDeviceList;
	memset(&stDeviceList, 0, sizeof(MV_CC_DEVICE_INFO_LIST));

	MV_CC_EnumDevices(MV_GIGE_DEVICE | MV_USB_DEVICE, &stDeviceList);

	return stDeviceList;
}

int list_devices(std::vector<std::string> &devices)
{
	int ret = 0;
	MV_CC_DEVICE_INFO_LIST stDeviceList = find_devices();

	if (stDeviceList.nDeviceNum > 0)
	{
		for (unsigned int i = 0; i < stDeviceList.nDeviceNum; i++)
			devices.push_back(std::string((const char *)stDeviceList.pDeviceInfo[0]->SpecialInfo.stUsb3VInfo.chSerialNumber));
	}
	else
	{
		ret = -1;
	}

	return ret;
}

HIKVCamera::HIKVCamera()
{
	bufPtr = NULL;
	dev_handle = NULL;
	isInitialized = false;
	isTrigged = false;
	format = 0;
	imgSize = 0;
	width = 0;
	height = 0;
	isCapStarted = false;
}

int HIKVCamera::openCamera(int index)
{
	int ret = 0;

	MV_CC_DEVICE_INFO_LIST stDeviceList = find_devices();
	ret = MV_CC_CreateHandle(&dev_handle, stDeviceList.pDeviceInfo[index]);
	if (ret == MV_OK)
	{
		ret = MV_CC_OpenDevice(dev_handle);
		std::cout << "MFG name  :" << stDeviceList.pDeviceInfo[0]->SpecialInfo.stGigEInfo.chManufacturerName << std::endl;
		mfgname = stDeviceList.pDeviceInfo[0]->SpecialInfo.stGigEInfo.chManufacturerName;
	}
	return ret;
}

int HIKVCamera::openCamera(std::string serial_no)
{
	int ret = -1;
	MV_CC_DEVICE_INFO_LIST stDeviceList = find_devices();
	// mfgname = ((char*) stDeviceList.pDeviceInfo[0]->SpecialInfo.stUsb3VInfo.chManufacturerName);
	for (unsigned int i = 0; i < stDeviceList.nDeviceNum; i++)
	{
		if (strcmp((const char *)stDeviceList.pDeviceInfo[i]->SpecialInfo.stUsb3VInfo.chSerialNumber, serial_no.c_str()) == 0)
		{
			ret = MV_CC_CreateHandle(&dev_handle, stDeviceList.pDeviceInfo[i]);
			if (ret == MV_OK)
			{
				ret = MV_CC_OpenDevice(dev_handle);
			}
			break;
		}
	}

	return ret;
}

int HIKVCamera::configureCapture(int capture_mode, uint16_t width, uint16_t height, uint16_t x_offset, uint16_t y_offset, bool ae_mode, float ae_time, bool white_balance, int high_value, int low_value)
{
	int ret = 0;
	assert(dev_handle != NULL);
	float fExposureTime = 1000 * ae_time;
	isTrigged = capture_mode == 1;
	std::cout << "mfg name  :" << mfgname << std::endl;
	ret += MV_CC_SetIntValue(dev_handle, "Width", width);
	ret += MV_CC_SetIntValue(dev_handle, "Height", height);
	ret += MV_CC_SetIntValue(dev_handle, "OffsetX", x_offset);
	ret += MV_CC_SetIntValue(dev_handle, "OffsetY", y_offset);
	ret += MV_CC_SetEnumValue(dev_handle, "PixelFormat", 0x02180015); // RGB8-0x02180014 BayerRG8 - 0x01080009  BGR8 - 0x02180015 
	ret += MV_CC_SetBoolValue(dev_handle, "AcquisitionFrameRateEnable", 0);
	std::string name = "";

	ret += MV_CC_SetFloatValue(dev_handle, "ExposureTime", fExposureTime);
	ret += MV_CC_SetFloatValue(dev_handle, "Gain", 14.0);
	// Gain Value for M35 -14 & M20 -4

	format = CV_8UC3;
	// ret += MV_CC_SetEnumValue(dev_handle, "PixelFormat", 0x0210001F); //YUV422_8_UYVY
	// format = CV_8UC2;
	if (white_balance)
	{
		ret += MV_CC_SetEnumValue(dev_handle, "BalanceWhiteAuto", 1); // Continuous
	}
	else
	{
		ret += MV_CC_SetEnumValue(dev_handle, "BalanceWhiteAuto", 0); // off
	}

	ret += MV_CC_SetEnumValue(dev_handle, "LineSelector", 2); // 1 line 1, 2 line 2
	//	std::cout<<"error value 1  :"<<ret<<std::endl;
	ret += MV_CC_SetEnumValue(dev_handle, "LineMode", 8);	  // input,8-strobe
															  //	std::cout<<"error value 2  :"<<ret<<std::endl;
															  //		ret += MV_CC_SetEnumValue(dev_handle, "LineSource", 0);//Exposuretime
															  //		std::cout<<"error value 3  :"<<ret<<std::endl;
	ret += MV_CC_SetBoolValue(dev_handle, "LineInverter", 1); // Invert the line
	ret += MV_CC_SetBoolValue(dev_handle, "StrobeEnable", 1); // Enable strobe
	//	std::cout<<"error value 4  :"<<ret<<std::endl;
	std::cout << "High value :" << high_value << std::endl;
	std::cout << "Low value :" << low_value << std::endl;
	ret += MV_CC_SetIntValue(dev_handle, "StrobeLineDuration", high_value); // Enable strobe durtion -100
	std::cout << "error value 5  :" << ret << std::endl;
	ret += MV_CC_SetIntValue(dev_handle, "StrobeLineDelay", low_value); // Enable delay 50,
	std::cout << "error value 6  :" << ret << std::endl;

	// Changed to the Basler camera

	if (isTrigged)
	{
		ret += MV_CC_SetEnumValue(dev_handle, "TriggerMode", 1);
		ret += MV_CC_SetEnumValue(dev_handle, "TriggerSource", MV_TRIGGER_SOURCE_LINE0);

		std::cout << "error value  :" << ret << std::endl;
		ret += MV_CC_SetEnumValue(dev_handle, "SensorShutterMode", 1); // Global reset
		std::cout << "error value 5  :" << ret << std::endl;
		//	getchar();
	}
	else
	{
		ret += MV_CC_SetEnumValue(dev_handle, "TriggerMode", 0);
	}

	// For setting line1 high
	ret += MV_CC_SetEnumValue(dev_handle, "LineSelector", 1); // 1 line 1, 2 line 2 ////ITC GooD signal
	//	std::cout<<"error value 1  :"<<ret<<std::endl;
	ret += MV_CC_SetEnumValue(dev_handle, "LineMode", 8);						  // input,8-strobe
	ret += MV_CC_SetBoolValue(dev_handle, "LineInverter", 0);					  // Invert the line
	ret += MV_CC_SetBoolValue(dev_handle, "StrobeEnable", 1);					  // Enable strobe
	ret += MV_CC_SetEnumValue(dev_handle, "LineSource", 5);						  // 5-Software trigger Active
	ret += MV_CC_SetIntValue(dev_handle, "StrobeLineDuration", high_value * 500); // Enable strobe durtion o/p on time

	// For setting line1 high
	ret += MV_CC_SetEnumValue(dev_handle, "LineSelector", 2); // 1 line 1, 2 line 2 //ITC NG?Rejection signal
	//	std::cout<<"error value 1  :"<<ret<<std::endl;
	ret += MV_CC_SetEnumValue(dev_handle, "LineMode", 8);						 // input,8-strobe
	ret += MV_CC_SetBoolValue(dev_handle, "LineInverter", 0);					 // Invert the line
	ret += MV_CC_SetBoolValue(dev_handle, "StrobeEnable", 1);					 // Enable strobe
	ret += MV_CC_SetEnumValue(dev_handle, "LineSource", 5);						 // 5-Software trigger Active
	ret += MV_CC_SetIntValue(dev_handle, "StrobeLineDuration", low_value * 500); // Enable strobe durtion o/p on time

	MVCC_INTVALUE stParam;
	ret += MV_CC_GetIntValue(dev_handle, "PayloadSize", &stParam);
	imgSize = stParam.nCurValue;

	memset(&stImageInfo, 0, sizeof(MV_FRAME_OUT_INFO_EX));
	bufPtr = (unsigned char *)malloc(sizeof(unsigned char) * imgSize);

	isInitialized = true;
	return ret;
}

int HIKVCamera::toggleline2(int timeout)
{
	int ret = 0;
	// set line 2 toggle
	ret += MV_CC_SetEnumValue(dev_handle, "LineSelector", 2);		 // 1 line 1, 2 line 2
	ret += MV_CC_SetCommandValue(dev_handle, "LineTriggerSoftware"); // Software trigger o/p
	return 0;
}
int HIKVCamera::toggleline1(int timeout)
{
	int ret = 0;
	// set line 1 toggle
	ret += MV_CC_SetEnumValue(dev_handle, "LineSelector", 1);		 // 1 line 1, 2 line 2
	ret += MV_CC_SetCommandValue(dev_handle, "LineTriggerSoftware"); // Software trigger o/p
	return 0;
}

int HIKVCamera::startCapture()
{
	assert(isInitialized != false);
	int ret = 0;
	ret = MV_CC_StartGrabbing(dev_handle);
	if (ret == MV_OK)
	{
		isCapStarted = true;
	}
	return ret;
}

int HIKVCamera::stopCapture()
{
	if (!isCapStarted)
	{
		return 0;
	}
	int ret = 0;
	ret = MV_CC_StopGrabbing(dev_handle);
	if (ret == MV_OK)
	{
		isCapStarted = false;
	}
	return ret;
}

int HIKVCamera::closeCamera()
{
	int ret = 0;
	if (bufPtr != NULL)
	{
		free(bufPtr);
		bufPtr = NULL;
	}
	ret = MV_CC_DestroyHandle(dev_handle);
	isInitialized = ret != MV_OK;
	return ret;
}

int HIKVCamera::getImage(Mat &img, int timeout)
{
	int ret = -1;
	assert(isCapStarted != false);

	ret = MV_CC_GetOneFrameTimeout(dev_handle, bufPtr, imgSize, &stImageInfo, 5000);
	if (ret == MV_OK)
	{
		img = Mat(stImageInfo.nHeight, stImageInfo.nWidth, format);
		memcpy(img.data, bufPtr, imgSize);
		ret = 0;
	}
	else
	{
		bool dev_status = MV_CC_IsDeviceConnected(dev_handle);
		if (dev_status)
		{
			printf("Cap timeout..\n");
			ret = 1;
		}
		else
		{
			printf("Device Disconnected..\n");
			ret = -1;
		}
	}
	return ret;
}

HIKVCamera::~HIKVCamera()
{
	stopCapture();
	closeCamera();
}
