//
// Created by 王轲毅 on 16/7/24.
//

// DevMgntTest.cpp: implementation of the CDevMgntTest class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "DevMgntTest.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
DEVHANDLE g_hDev = NULL;
CDevMgntTest::CDevMgntTest()
{

}

CDevMgntTest::~CDevMgntTest()
{

}

BOOL CDevMgntTest::Test_WaitForDevEvent()
{
    SHOW_PROCESS("WaitForDevEvent");

    CHAR szDevName[256] = {0};
    ULONG ulDevNamelen = 256;
    ULONG ulEvent = 0;

    ULONG ulReval = SKF_WaitForDevEvent(szDevName, &ulDevNamelen, &ulEvent);
    SHOW_ERROR(ulReval);
    if (SAR_OK == ulReval)
    {
        char szOperation[10] = {0};
        if (1 == ulEvent)
            strcpy(szOperation, "Inserted...");
        if (2 == ulEvent)
            strcpy(szOperation, "Removed...");

        printf("Device name : %s, %s", szDevName, szOperation);
    }

    // Check Arguments

    return (SAR_OK == ulReval);
}

BOOL CDevMgntTest::Test_CancelWaitForDevEvent()
{
    SHOW_PROCESS("CancelWaitForDevEvent");

    ULONG ulReval = SKF_CancelWaitForDevEvent();
    GetUtilities().ShowErrInfo(ulReval);

    return (SAR_OK == ulReval);
}

BOOL CDevMgntTest::Test_EnumDev()
{
    SHOW_PROCESS("EnumDev");

    BOOL bList = TRUE;
    printf("Show present list : 1, Show all list : 0\n");

    ULONG ulBufSize = 0;
    ULONG ulReval = SAR_FAIL;
    for (int i = 0; i < 2; i++)
    {
        if (bList)
            printf("current list");
        else
            printf("support list");

        ulReval = SKF_EnumDev(bList, NULL, &ulBufSize);
        SHOW_ERROR(ulReval);
        printf("%d\n",ulBufSize);
        if (SAR_OK == ulReval)
        {
            vector<char> szNameList(ulBufSize, 0);
            if (SAR_OK == SKF_EnumDev(bList, (LPSTR)&szNameList[0], &ulBufSize))
            {
                GetUtilities().ShowListInfo((LPSTR)&szNameList[0]);
            }
        }
        printf("\n");
        bList = !bList;
    }

    if (ulBufSize == 1)
    {
        printf("no device found\n");
    }

    // Check Arguments

    return (SAR_OK == ulReval);
}

BOOL CDevMgntTest::Test_ConnectDev()
{
    SHOW_PROCESS("ConnectDev");

    ULONG ulBufSize = 0;
    ULONG ulReval = SKF_EnumDev(TRUE, NULL, &ulBufSize);
    printf("Enum Devies...");
    SHOW_ERROR(ulReval);
    if (SAR_OK == ulReval)
    {
        vector<char> szNameList(ulBufSize, 0);
        if (SAR_OK != SKF_EnumDev(TRUE, (LPSTR)&szNameList[0], &ulBufSize))
        {
            SHOW_ERROR(ulReval);
            return FALSE;
        }

        GetUtilities().ShowListInfo(&szNameList[0]);

        ULONG ulSelect = 0;
        printf("Input number to connect!(Example: 1 - "DEVNAME"1)");

        fflush(stdin);
        int ret = scanf("%d", &ulSelect);
        if(ret != 1)
        {
            printf("error input\n");
            return FALSE;
        }

        char szTokenName[20] = {0};
        sprintf(szTokenName, DEVNAME"%d", ulSelect);

        ULONG ulReval = SKF_ConnectDev((LPSTR)szTokenName, &g_hDev);
        printf("\nConnect ...");
        SHOW_ERROR(ulReval);
    }

    // Check Arguments

    return (SAR_OK == ulReval);
}

BOOL CDevMgntTest::Test_DisConnectDev()
{
    SHOW_PROCESS("DisConnectDev");

    if (NULL == g_hDev)
    {
        printf("Please connect to token first!\n");
        return FALSE;
    }

    ULONG ulReval = SKF_DisConnectDev(g_hDev);
    SHOW_ERROR(ulReval);
//	g_hDev = NULL;
    // Check Arguments

    return (SAR_OK == ulReval);
}

BOOL CDevMgntTest::Test_GetDevState()
{
    SHOW_PROCESS("GetDevState");

    char szNameReader[256] = {0};
    char szDevName[256] = {0};

    printf("Input token name to get state!(Example: "DEVNAME"1)");

    fflush(stdin);
    gets(szNameReader);
    sprintf(szDevName,"ES3000GM VCR %c",szNameReader[0]);
    ULONG ulDevState = 0;
//	ULONG ulNameLen = strlen((const char *)szNameReader);
//	ULONG ulReval = SKF_GetDevState((LPSTR)szNameReader, &ulDevState);
    ULONG ulNameLen = strlen((const char *)szDevName);
    ULONG ulReval = SKF_GetDevState((LPSTR)szDevName,&ulDevState);
    SHOW_ERROR(ulReval);
    if (SAR_OK == ulReval)
    {
        switch(ulDevState)
        {
            case DEV_ABSENT_STATE:
                printf("Absent\n");
                break;
            case DEV_PRESENT_STATE:
                printf("Present\n");
                break;
            default:
                printf("Unknown\n");
        }
    }

    // Check Arguments

    return (SAR_OK == ulReval);
}

BOOL CDevMgntTest::Test_SetLabel()
{
    SHOW_PROCESS("SetLabel");
    if (NULL == g_hDev)
    {
        printf("Please connect first!\n");
        return FALSE;
    }

    printf("Input Label:(length <= 32)");
    char szLable[64] = {0};

    ULONG ulReval = SAR_FAIL;

    printf("Length of Lable equal 32\n");
    strcpy(szLable, "123456789_123456789_123456789_32");
    ulReval = SKF_SetLabel(g_hDev, (LPSTR)szLable);
    SHOW_ERROR(ulReval);

    printf("Length of Lable below 32\n");
    memset(szLable, 0, 64);
    strcpy(szLable, "123456789_123456789_22");
    ulReval = SKF_SetLabel(g_hDev, (LPSTR)szLable);
    SHOW_ERROR(ulReval);

    printf("Length of Lable above 32\n");
    memset(szLable, 0, 64);
    strcpy(szLable, "123456789_123456789_123456789_123456789_42");
    ulReval = SKF_SetLabel(g_hDev, (LPSTR)szLable);
    SHOW_ERROR(ulReval);

    // Check Arguments

    return (SAR_OK == ulReval);
}

BOOL CDevMgntTest::Test_GetDevInfo()
{
    SHOW_PROCESS("GetDevInfo");

    if (NULL == g_hDev)
    {
        printf("Please connect first!\n");
        return FALSE;
    }

    DEVINFO devInfo = {0};
    ULONG ulReval = SKF_GetDevInfo(g_hDev, &devInfo);
    SHOW_ERROR(ulReval);

    if (SAR_OK == ulReval)
    {
        printf("Followling is info about the device.\n");
        printf("Version: %d\n", devInfo.Version);
        printf("Manufacturer: %s\n", devInfo.Manufacturer);
        printf("Issuer: %s\n", devInfo.Issuer);
        printf("Label: %s\n", devInfo.Label);
        printf("SerialNumber: %s\n", devInfo.SerialNumber);
        printf("Hardware Version: %d.%d\n", devInfo.HWVersion.major, devInfo.HWVersion.minor);
        printf("Firmware Version: %d.%d\n", devInfo.FirmwareVersion.major, devInfo.FirmwareVersion.minor);
        printf("TotalSpace: %d\n", devInfo.TotalSpace);
        printf("FreeSpace: %d\n\n", devInfo.FreeSpace);

        printf("AlgSymCap : %d\n", devInfo.AlgAsymCap);
        printf("AlgAsymCap : %d\n", devInfo.AlgAsymCap);
        printf("AlgHashCap : %d\n", devInfo.AlgHashCap);
        printf("DevAuthAlgId : %d\n", devInfo.DevAuthAlgId);
        printf("MaxECCBufferSize : %d\n", devInfo.MaxECCBufferSize);
        printf("MaxBufferSize : %d\n", devInfo.MaxBufferSize);
    }

    // Check Arguments

    return (SAR_OK == ulReval);
}

BOOL CDevMgntTest::Test_LockDev()
{
    SHOW_PROCESS("LockDev");
    if (NULL == g_hDev)
    {
        printf("Please connect first!\n");
        return FALSE;
    }

    ULONG ulTime = 0;
    printf("Please input how many times to lock.(Unit: mm).");
    fflush(stdin);
    int ret = scanf("%d", &ulTime);
    if(ret != 1)
    {
        printf("error input\n");
        return FALSE;
    }

    ULONG ulReval = SKF_LockDev(g_hDev, ulTime);
    SHOW_ERROR(ulReval);

    // Check Arguments

    return (SAR_OK == ulReval);
}

BOOL CDevMgntTest::Test_UnlockDev()
{
    SHOW_PROCESS("UnlockDev");
    if (NULL == g_hDev)
    {
        printf("Please connect first!\n");
        return FALSE;
    }

    ULONG ulReval = SKF_UnlockDev(g_hDev);
    SHOW_ERROR(ulReval);

    // Check Arguments

    return (SAR_OK == ulReval);
}
