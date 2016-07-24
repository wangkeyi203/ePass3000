//
// Created by 王轲毅 on 16/7/24.
//

// AuthTest.cpp: implementation of the CAuthTest class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "AuthTest.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern DEVHANDLE g_hDev;
extern HAPPLICATION g_hApp;
CAuthTest::CAuthTest() : m_hSessionKey(NULL)
{

}

CAuthTest::~CAuthTest()
{

}

BOOL CAuthTest::Test_ChangeDevAuthKey()
{
    SHOW_PROCESS("ChangeDevAuthKey");
    if (NULL == g_hDev)
    {
        printf("Please connect first!\n");
        return FALSE;
    }

    BYTE *byKey = (BYTE *)"1234567812345678";
    ULONG ulReval = SKF_ChangeDevAuthKey(g_hDev, byKey, 16);
    SHOW_ERROR(ulReval);
    return (SAR_OK == ulReval);
}

BOOL CAuthTest::Test_DevAuth()
{
    SHOW_PROCESS("DevAuth");

    if (NULL == g_hDev)
    {
        printf("Please connect first!\n");
        return FALSE;
    }

    BYTE random[16] = {0};

    ULONG ulReval = SKF_GenRandom(g_hDev, random, 8);
    SHOW_ERROR_EX("GenRandom", ulReval);
    if (SAR_OK != ulReval)
        return FALSE;

    DEVINFO devInfo;
    ulReval = SKF_GetDevInfo(g_hDev, &devInfo);
    SHOW_ERROR_EX("GetDevInfo", ulReval);
    if (SAR_OK != ulReval)
        return FALSE;

    BYTE devKey[16] = {0};
    memcpy(devKey, (BYTE*)"1234567812345678", 16);
    ulReval = SKF_SetSymmKey(g_hDev, devKey, devInfo.DevAuthAlgId, &m_hSessionKey);
    SHOW_ERROR_EX("SetSymmKey", ulReval);
    if (SAR_OK != ulReval)
        return FALSE;

    BLOCKCIPHERPARAM param = {0};
    ulReval = SKF_EncryptInit(m_hSessionKey, param);
    SHOW_ERROR_EX("EncryptInit", ulReval);
    if (SAR_OK != ulReval)
        return FALSE;

    BYTE devkeyenc[16] = {0};
    DWORD dwResultLen = 16;
    ulReval = SKF_Encrypt(m_hSessionKey, random, 16, devkeyenc, &dwResultLen);
    SHOW_ERROR_EX("Encrypt", ulReval);
    if (SAR_OK != ulReval)
        return FALSE;

    ulReval = SKF_DevAuth(g_hDev, devkeyenc, 16);
    SHOW_ERROR(ulReval);

    return (SAR_OK == ulReval);
}

BOOL CAuthTest::Test_ChangePIN()
{
    SHOW_PROCESS("ChangePIN");
    if (NULL == g_hApp)
    {
        printf("OPen application first!\n");
        return  FALSE;
    }

    int szBuf;
    ULONG nAccountType = 0;
    printf("Input 0: administrator, 1:User\n");

    fflush(stdin);
//	szBuf = getchar();
    szBuf = GetInputChar();

    if (szBuf == '0')
        nAccountType = 0;
    else if (szBuf == '1')
        nAccountType = 1;
    else
        return FALSE;

    char szOldPIN[256] = {0};
    char szNewPIN[256] = {0};
    ULONG nRetryNum = 0;

    printf("Input Old PIN:\n");
    fflush(stdin);
    gets(szOldPIN);

    printf("Input New PIN:\n");
    fflush(stdin);
    gets(szNewPIN);

    ULONG ulReval = SKF_ChangePIN(g_hApp, nAccountType, (LPSTR)szOldPIN, (LPSTR)szNewPIN, &nRetryNum);
    SHOW_ERROR(ulReval);

    return (SAR_OK == ulReval);
}

BOOL CAuthTest::Test_GetPINInfo()
{
    SHOW_PROCESS("GetPINInfo");
    if (NULL == g_hApp)
    {
        printf("OPen application first!\n");
        return FALSE;
    }

    int szBuf;
    ULONG nAccountType = 0;
    printf("Input 0: administrator, 1:User\n");

    fflush(stdin);
//	szBuf = getchar();
    szBuf = GetInputChar();

    if (szBuf == '0')
        nAccountType = 0;
    else if (szBuf == '1')
        nAccountType = 1;
    else
        return FALSE;

    ULONG ulMaxRetryCount = 0;
    ULONG ulRemainRetryCount = 0;
    BOOL DefaultPin = FALSE;

    ULONG ulReval = SKF_GetPINInfo(g_hApp, nAccountType, &ulMaxRetryCount, &ulRemainRetryCount, &DefaultPin);
    SHOW_ERROR(ulReval);
    if (SAR_OK == ulReval)
    {
        printf("Max retry count is : %d\n", ulMaxRetryCount);
        printf("Remain retry count is: %d\n", ulRemainRetryCount);
        printf("is Default PIN: %d\n", DefaultPin);
    }

    return (SAR_OK == ulReval);
}

BOOL CAuthTest::Test_VerifyPIN()
{
    SHOW_PROCESS("VerifyPIN");
    if (NULL == g_hApp)
    {
        printf("OPen application first!\n");
        return FALSE;
    }

    int szBuf;
    ULONG nAccountType = 0;
    printf("Input 0: administrator, 1:User\n");

    fflush(stdin);
//	szBuf = getchar();
    szBuf = GetInputChar();

    if (szBuf == '0')
        nAccountType = 0;
    else if (szBuf == '1')
        nAccountType = 1;
    else
        return FALSE;

    printf("Input PIN:\n");
    char szPIN[256] = {0};

    fflush(stdin);
    gets(szPIN);

    ULONG ulRetryCount = 0;
    ULONG ulReval = SKF_VerifyPIN(g_hApp, nAccountType, (LPSTR)szPIN, &ulRetryCount);
    SHOW_ERROR(ulReval);

    return (SAR_OK == ulReval);
}

BOOL CAuthTest::Test_UnblockPIN()
{
    SHOW_PROCESS("UnblockPIN");
    if (NULL == g_hApp)
    {
        printf("OPen application first!\n");
        return FALSE;
    }

    char szSoPIN[256] = {0};
    printf("Input administrator's PIN\n");

    fflush(stdin);
    gets(szSoPIN);


    char szNewUserPIN[256] = {0};
    printf("Input new user's PIN\n");

    fflush(stdin);
    gets(szNewUserPIN);

    ULONG ulRetryCount = 0;
    ULONG ulReval = 0;
    do
    {
        ulReval = SKF_UnblockPIN(g_hApp, (LPSTR)szSoPIN, (LPSTR)szNewUserPIN, &ulRetryCount);
        SHOW_ERROR(ulReval);
        if (SAR_PIN_INCORRECT == ulReval)
        {
            printf("Wrong PIN!\n");
            break;
        }

        if (SAR_PIN_INVALID == ulReval)
        {
            printf("Invalid PIN!\n");
            break;
        }

        if (SAR_PIN_LEN_RANGE == ulReval)
        {
            printf("Wrong PIN Length!\n");
            break;
        }

        if (SAR_PIN_LOCKED == ulReval)
        {
            printf("Your PIN has been locked!\n");
            break;
        }
    } while (0);

    return (SAR_OK == ulReval);
}

BOOL CAuthTest::Test_ClearSecureState()
{
    SHOW_PROCESS("ClearSecureState");
    if (NULL == g_hApp)
    {
        printf("OPen application first!\n");
        return FALSE;
    }

    ULONG ulReval = SKF_ClearSecureState(g_hApp);
    SHOW_ERROR(ulReval);

    return (SAR_OK == ulReval);
}
