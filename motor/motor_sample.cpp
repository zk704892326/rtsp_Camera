
#if (!defined(WIN32) && !defined(_WIN32_WCE))

#include "NvdcDll.h"
#include "SNError.h"

#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <unistd.h>
//#include <iostream.h>
#include <iostream>

using namespace std;
using namespace NVDC_STRUCT;
using namespace NVDC_FUC;

void getLoginInfo(ST_DeviceInfo* p_pstDeviceInfo)
{
	char szIP[48] = {0};
	char szPort[16] = {0};

	printf("please input the server ip:\n");
	scanf("%s", szIP);
	printf("please input the server port:\n");
	scanf("%s", szPort);

	unsigned short nPort = 0;
	nPort = atoi(szPort);

	memset(p_pstDeviceInfo, 0, sizeof(ST_DeviceInfo));
	p_pstDeviceInfo->nDeviceType = IPCAMERA;

	memcpy(p_pstDeviceInfo->stInetAddr.szHostIP, szIP, strlen(szIP));
	p_pstDeviceInfo->stInetAddr.nPORT = nPort;
	p_pstDeviceInfo->stInetAddr.nIPProtoVer = IPPROTO_V4;
	
	char szUserID[32] = {0};
	char szPassword[32] = {0};
	printf("please input the user name:\n");
	scanf("%s", szUserID);
	printf("please input the password:\n");
	scanf("%s", szPassword);
	

	memcpy(p_pstDeviceInfo->szUserID, szUserID, strlen(szUserID));
	memcpy(p_pstDeviceInfo->szPassword, szPassword, strlen(szPassword));
}

int main()
{
	ST_DeviceInfo stDeviceInfo;
	memset(&stDeviceInfo, 0 ,sizeof(stDeviceInfo));
	//获取设备信息
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
