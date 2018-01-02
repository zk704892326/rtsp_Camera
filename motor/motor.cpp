#include "NvdcDll.h"
#include "SNError.h"

#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include "motor.h"

using namespace std;
using namespace NVDC_STRUCT;
using namespace NVDC_FUC;

Motor::Motor() {
	this->device = malloc(sizeof(ST_DeviceInfo));
	this->handle = 0;
	this->state = 0;
	this->speed = 10;
}

Motor::~Motor() {
	if(NULL != this->device) {
		free(this->device);
		this->device = NULL;
	}
}

bool Motor::open(const char *ip, const int port, const char *user, const char *password) {
	if(0 != this->handle) {
		return true;
	}
	this->ip = (char *)ip;
	this->port = port;
	this->user = (char *)user;
	this->password = (char *)password;

	ST_DeviceInfo *device = (ST_DeviceInfo *)this->device;
	long *handle = &this->handle;

	this->setLoginInfo();
	int nRet = Remote_Nvd_Init(handle, device, UDP);
	if (nRet != SN_SUCCESS)
	{
		char szErrorInfo[512] = {0};
		Remote_Nvd_formatMessage(nRet, szErrorInfo, 512);
		printf("%s, %d\n", szErrorInfo, nRet);
		return false;
	}

	int nCameraID = 1;
	nRet = Remote_PTZEx_Open(this->handle, nCameraID);
	if(nRet != SN_SUCCESS)
	{
		char szErrorInfo[512] = {0};
		Remote_Nvd_formatMessage(nRet, szErrorInfo,512);
		printf("Open: %s, %d\n", szErrorInfo, nRet);
		Remote_Nvd_UnInit(this->handle);
		this->handle = 0;
		return false;
	}
	return true;
}

bool Motor::isOpen() {
	if(0 == this->handle) {
		return false;
	}
	return true;
}

void Motor::close() {
	int nRet = Remote_PTZEx_Close(this->handle);
	if(nRet != SN_SUCCESS)
	{
		char szErrorInfo[512] = {0};
		Remote_Nvd_formatMessage(nRet, szErrorInfo,512);
		printf("%s\n", szErrorInfo);
	}
	Remote_Nvd_UnInit(this->handle);
	this->handle = 0;
}

bool Motor::stop() {
	int nRet = Remote_PTZEx_Stop(this->handle);
	if(nRet != SN_SUCCESS)
	{
		char szErrorInfo[512] = {0};
		Remote_Nvd_formatMessage(nRet, szErrorInfo,512);
		printf("%s\n", szErrorInfo);
		return false;
	}
	return true;
}

void Motor::setLoginInfo() {
	ST_DeviceInfo *device = (ST_DeviceInfo *)this->device;
	memset(device, 0, sizeof(ST_DeviceInfo));
	device->nDeviceType = IPCAMERA;

	memcpy(device->stInetAddr.szHostIP, this->ip, strlen(this->ip));
	device->stInetAddr.nPORT = this->port;
	device->stInetAddr.nIPProtoVer = IPPROTO_V4;
	
	memcpy(device->szUserID, this->user, strlen(this->user));
	memcpy(device->szPassword, this->password, strlen(this->password));
}

bool Motor::moveUp() {
	int nRet = Remote_PTZEx_RotateUp(this->handle, speed);
	if(nRet != SN_SUCCESS)
	{
		char szErrorInfo[512] = {0};
		Remote_Nvd_formatMessage(nRet, szErrorInfo,512);
		printf("%s, %d\n", szErrorInfo, nRet);
		Remote_Nvd_UnInit(handle);
		handle = 0;
		return false;
	}
	return true;
}

bool Motor::moveDown() {
	int nRet = Remote_PTZEx_RotateDown(this->handle, speed);
	if(nRet != SN_SUCCESS)
	{
		char szErrorInfo[512] = {0};
		Remote_Nvd_formatMessage(nRet, szErrorInfo,512);
		printf("%s\n", szErrorInfo);
		Remote_Nvd_UnInit(handle);
		handle = 0;
		return nRet;
	}
	return true;
}

bool Motor::moveLeft() {
	int nRet = Remote_PTZEx_RotateLeft(this->handle, speed);
	if(nRet != SN_SUCCESS)
	{
		char szErrorInfo[512] = {0};
		Remote_Nvd_formatMessage(nRet, szErrorInfo,512);
		printf("%s, %d\n", szErrorInfo, nRet);
		Remote_Nvd_UnInit(handle);
		handle = 0;
		return nRet;
	}
}

bool Motor::moveRight() {
	int nRet = Remote_PTZEx_RotateRight(this->handle, speed);
	if(nRet != SN_SUCCESS)
	{
		char szErrorInfo[512] = {0};
		Remote_Nvd_formatMessage(nRet, szErrorInfo,512);
		printf("%s\n", szErrorInfo);
		Remote_Nvd_UnInit(handle);
		handle = 0;
		return nRet;
	}
}

bool Motor::rotateLeftUp() {
	int nRet = Remote_PTZEx_RotateLeftUp(this->handle, speed);
	if(nRet != SN_SUCCESS)
	{
		char szErrorInfo[512] = {0};
		Remote_Nvd_formatMessage(nRet, szErrorInfo,512);
		printf("%s, %d\n", szErrorInfo, nRet);
		Remote_Nvd_UnInit(handle);
		handle = 0;
		return false;
	}
	return true;
}

//long SN_C_API Remote_PTZEx_SetPostion(long p_hHandle, const int p_nType, const float p_nPan, const float p_nTilt, const float p_nZoom);
//long SN_C_API Remote_PTZEx_GetPostion(long p_hHandle, float* p_nPan, float* p_nTilt, float* p_nZoom, int* p_nDirection);


bool Motor::rotateSetPostion(int p_nType,float p_nPan,float p_nTilt,float p_nZoom) {
	int nRet = Remote_PTZEx_SetPostion(this->handle, p_nType,p_nPan,p_nTilt,p_nZoom);
	if(nRet != SN_SUCCESS)
	{
		char szErrorInfo[512] = {0};
		Remote_Nvd_formatMessage(nRet, szErrorInfo,512);
		printf("%s, %d\n", szErrorInfo, nRet);
		Remote_Nvd_UnInit(handle);
		handle = 0;
		return false;
	}
	return true;
}

bool Motor::rotateGetPostion(float *p_nPan,float *p_nTilt,float *p_nZoom,int *p_nDirection) {
	int nRet = Remote_PTZEx_GetPostion(this->handle,p_nPan,p_nTilt,p_nZoom,p_nDirection);
	if(nRet != SN_SUCCESS)
	{
		char szErrorInfo[512] = {0};
		Remote_Nvd_formatMessage(nRet, szErrorInfo,512);
		printf("%s, %d\n", szErrorInfo, nRet);
		Remote_Nvd_UnInit(handle);
		handle = 0;
		return false;
	}
	this->motorX = *p_nPan;
	this->motorY = *p_nTilt;
	this->motorZoom = *p_nZoom;
	this->motorDirection = *p_nDirection;
	return true;
}

#if 0
int main()
{
	ST_DeviceInfo stDeviceInfo;
	memset(&stDeviceInfo, 0 ,sizeof(stDeviceInfo));
	//»ñÈ¡Éè±¸ÐÅÏ¢
	getLoginInfo(&stDeviceInfo);
	
	long hRemoteHandle = NULL;
	
	int nRet = Remote_Nvd_Init(&hRemoteHandle, &stDeviceInfo, UDP);
	if (nRet != SN_SUCCESS)
	{
		char szErrorInfo[512] = {0};
		Remote_Nvd_formatMessage(nRet, szErrorInfo,512);
		printf("%s, %d\n", szErrorInfo, nRet);
		return nRet;
	}

	int nCameraID = 1;
	nRet = Remote_PTZEx_Open(hRemoteHandle, nCameraID);
	if(nRet != SN_SUCCESS)
	{
		char szErrorInfo[512] = {0};
		Remote_Nvd_formatMessage(nRet, szErrorInfo,512);
		printf("Open: %s, %d\n", szErrorInfo, nRet);
		Remote_Nvd_UnInit(hRemoteHandle);
		hRemoteHandle =NULL;
		return nRet;
	}
	
		
	int nSpeed = 60;
	nRet = Remote_PTZEx_RotateLeftUp(hRemoteHandle, nSpeed);
	if(nRet != SN_SUCCESS)
	{
		char szErrorInfo[512] = {0};
		Remote_Nvd_formatMessage(nRet, szErrorInfo,512);
		printf("%s, %d\n", szErrorInfo, nRet);
		Remote_Nvd_UnInit(hRemoteHandle);
		hRemoteHandle =NULL;
		return nRet;
	}
	
	
/*
	nRet = Remote_PTZEx_RotateUp(hRemoteHandle, nSpeed);
	if(nRet != SN_SUCCESS)
	{
		char szErrorInfo[512] = {0};
		Remote_Nvd_formatMessage(nRet, szErrorInfo,512);
		printf("%s, %d\n", szErrorInfo, nRet);
		Remote_Nvd_UnInit(hRemoteHandle);
		hRemoteHandle =NULL;
		return nRet;
	}
	
	nRet = Remote_PTZEx_RotateRightUp(hRemoteHandle, nSpeed);
	if(nRet != SN_SUCCESS)
	{
		char szErrorInfo[512] = {0};
		Remote_Nvd_formatMessage(nRet, szErrorInfo,512);
		printf("%s, %d\n", szErrorInfo, nRet);
		Remote_Nvd_UnInit(hRemoteHandle);
		hRemoteHandle =NULL;
		return nRet;
	}
	
	nRet = Remote_PTZEx_RotateLeft(hRemoteHandle, nSpeed);
	if(nRet != SN_SUCCESS)
	{
		char szErrorInfo[512] = {0};
		Remote_Nvd_formatMessage(nRet, szErrorInfo,512);
		printf("%s, %d\n", szErrorInfo, nRet);
		Remote_Nvd_UnInit(hRemoteHandle);
		hRemoteHandle =NULL;
		return nRet;
	}
	
	nRet = Remote_PTZEx_RotateRight(hRemoteHandle, nSpeed);
	if(nRet != SN_SUCCESS)
	{
		char szErrorInfo[512] = {0};
		Remote_Nvd_formatMessage(nRet, szErrorInfo,512);
		printf("%s\n", szErrorInfo);
		Remote_Nvd_UnInit(hRemoteHandle);
		hRemoteHandle =NULL;
		return nRet;
	}
	
	nRet = Remote_PTZEx_RotateLeftDown(hRemoteHandle, nSpeed);
	if(nRet != SN_SUCCESS)
	{
		char szErrorInfo[512] = {0};
		Remote_Nvd_formatMessage(nRet, szErrorInfo,512);
		printf("%s\n", szErrorInfo);
		Remote_Nvd_UnInit(hRemoteHandle);
		hRemoteHandle =NULL;
		return nRet;
	}
	
	nRet = Remote_PTZEx_RotateDown(hRemoteHandle, nSpeed);
	if(nRet != SN_SUCCESS)
	{
		char szErrorInfo[512] = {0};
		Remote_Nvd_formatMessage(nRet, szErrorInfo,512);
		printf("%s\n", szErrorInfo);
		Remote_Nvd_UnInit(hRemoteHandle);
		hRemoteHandle =NULL;
		return nRet;
	}
	
	nRet = Remote_PTZEx_RotateRightDown(hRemoteHandle, nSpeed);
	if(nRet != SN_SUCCESS)
	{
		char szErrorInfo[512] = {0};
		Remote_Nvd_formatMessage(nRet, szErrorInfo,512);
		printf("%s\n", szErrorInfo);
		Remote_Nvd_UnInit(hRemoteHandle);
		hRemoteHandle =NULL;
		return nRet;
	}
	
	nRet = Remote_PTZEx_FocusNear(hRemoteHandle);
	if(nRet != SN_SUCCESS)
	{
		char szErrorInfo[512] = {0};
		Remote_Nvd_formatMessage(nRet, szErrorInfo,512);
		printf("%s\n", szErrorInfo);
		Remote_Nvd_UnInit(hRemoteHandle);
		hRemoteHandle =NULL;
		return nRet;
	}
	
	nRet = Remote_PTZEx_FocusFar(hRemoteHandle);
	if(nRet != SN_SUCCESS)
	{
		char szErrorInfo[512] = {0};
		Remote_Nvd_formatMessage(nRet, szErrorInfo,512);
		printf("%s\n", szErrorInfo);
		Remote_Nvd_UnInit(hRemoteHandle);
		hRemoteHandle =NULL;
		return nRet;
	}
	
	nRet = Remote_PTZEx_IrisDecrease(hRemoteHandle);
	if(nRet != SN_SUCCESS)
	{
		char szErrorInfo[512] = {0};
		Remote_Nvd_formatMessage(nRet, szErrorInfo,512);
		printf("%s\n", szErrorInfo);
		Remote_Nvd_UnInit(hRemoteHandle);
		hRemoteHandle =NULL;
		return nRet;
	}
	
	nRet = Remote_PTZEx_IrisIncrease(hRemoteHandle);
	if(nRet != SN_SUCCESS)
	{
		char szErrorInfo[512] = {0};
		Remote_Nvd_formatMessage(nRet, szErrorInfo,512);
		printf("%s\n", szErrorInfo);
		Remote_Nvd_UnInit(hRemoteHandle);
		hRemoteHandle =NULL;
		return nRet;
	}
	
	nRet = Remote_PTZEx_ZoomIn(hRemoteHandle);
	if(nRet != SN_SUCCESS)
	{
		char szErrorInfo[512] = {0};
		Remote_Nvd_formatMessage(nRet, szErrorInfo,512);
		printf("%s\n", szErrorInfo);
		Remote_Nvd_UnInit(hRemoteHandle);
		hRemoteHandle =NULL;
		return nRet;
	}
	
	nRet = Remote_PTZEx_ZoomOut(hRemoteHandle);
	if(nRet != SN_SUCCESS)
	{
		char szErrorInfo[512] = {0};
		Remote_Nvd_formatMessage(nRet, szErrorInfo,512);
		printf("%s\n", szErrorInfo);
		Remote_Nvd_UnInit(hRemoteHandle);
		hRemoteHandle =NULL;
		return nRet;
	}
*/

	sleep(10);
		
	nRet = Remote_PTZEx_Stop(hRemoteHandle);
	if(nRet != SN_SUCCESS)
	{
		char szErrorInfo[512] = {0};
		Remote_Nvd_formatMessage(nRet, szErrorInfo,512);
		printf("%s\n", szErrorInfo);
		Remote_Nvd_UnInit(hRemoteHandle);
		hRemoteHandle =NULL;
		return nRet;
	}

	nRet = Remote_PTZEx_Close(hRemoteHandle);
	if(nRet != SN_SUCCESS)
	{
		char szErrorInfo[512] = {0};
		Remote_Nvd_formatMessage(nRet, szErrorInfo,512);
		printf("%s\n", szErrorInfo);
		Remote_Nvd_UnInit(hRemoteHandle);
		hRemoteHandle =NULL;
		return nRet;
	}

	Remote_Nvd_UnInit(hRemoteHandle);
	
	return 0;
}
#endif

