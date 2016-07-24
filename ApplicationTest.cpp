//
// Created by 王轲毅 on 16/7/24.
//

// ApplicationTest.cpp: implementation of the CApplicationTest class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "ApplicationTest.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern HANDLE g_hDev;
HAPPLICATION g_hApp;
CApplicationTest::CApplicationTest()
{

}

CApplicationTest::~CApplicationTest()
{

}

BOOL CApplicationTest::Test_CreateApplication()
{
    SHOW_PROCESS("CreateApplication");
    if (NULL == g_hDev)
    {
        printf("Please connect first!\n");
        return FALSE;
    }

    printf("Input Application Name:\n");
    char szAppName[256] = {0};
    fflush(stdin);
    gets(szAppName);

    printf("Input Administrator PIN:(len>=6)\n");
    char szSoPIN[256] = {0};
    fflush(stdin);
    gets(szSoPIN);

    printf("Input user PIN:(len>=6)\n");
    char szUserPIN[256] = {0};
    fflush(stdin);
    gets(szUserPIN);

    DWORD dwSoRetryCount = 0;
    DWORD dwUserRegryCount = 0;

    printf("Input Max count for administrator PIN(6-15)\n");
    fflush(stdin);
    int ret = scanf("%d", &dwSoRetryCount);
    if(ret != 1)
    {
        printf("error input\n");
        return FALSE;
    }

    printf("Input Max count for user PIN(6-15)\n");
    fflush(stdin);
    ret = scanf("%d", &dwUserRegryCount);
    if(ret != 1)
    {
        printf("error input\n");
        return FALSE;
    }

    ULONG ulReval = SKF_CreateApplication(g_hDev, (LPSTR)szAppName, (LPSTR)szSoPIN, dwSoRetryCount, (LPSTR)szUserPIN,
                                          dwUserRegryCount, SECURE_USER_ACCOUNT, &g_hApp);

    SHOW_ERROR(ulReval);
    return (SAR_OK == ulReval);
}

BOOL CApplicationTest::Test_EnumApplication()
{
    SHOW_PROCESS("EnumApplication");
    if (NULL == g_hDev)
    {
        printf("Please connect first!\n");
        return FALSE;
    }

    char szAppNames[256] = {0};
    ULONG ulSize = 256;

    ULONG ulReval = SKF_EnumApplication(g_hDev, (LPSTR)szAppNames, &ulSize);
    SHOW_ERROR(ulReval);

    if (SAR_OK == ulReval)
    {
        GetUtilities().ShowListInfo((LPSTR)szAppNames);
    }

    return (SAR_OK == ulReval);
}

BOOL CApplicationTest::Test_DeleteApplication()
{
    SHOW_PROCESS("DeleteApplication");
    if (NULL == g_hDev)
    {
        printf("Please connect first!\n");
        return FALSE;
    }

    char szAppNames[256] = {0};
    printf("Input apps name to delete!\n");

    fflush(stdin);
    gets(szAppNames);

    ULONG ulReval = SKF_DeleteApplication(g_hDev, (LPSTR)szAppNames);
    SHOW_ERROR(ulReval);
    g_hApp = NULL;

    return (SAR_OK == ulReval);
}

BOOL CApplicationTest::Test_OpenApplication()
{
    SHOW_PROCESS("OpenApplication");
    if (NULL == g_hDev)
    {
        printf("Please connect first!\n");
        return FALSE;
    }

    char szAppNames[256] = {0};
    printf("Input apps name to open!\n");

    fflush(stdin);
    gets(szAppNames);

    ULONG ulReval = SKF_OpenApplication(g_hDev, (LPSTR)szAppNames, &g_hApp);
    SHOW_ERROR(ulReval);

    return (SAR_OK == ulReval);
}

BOOL CApplicationTest::Test_CloseApplication()
{
    SHOW_PROCESS("CloseApplication");
    if (NULL == g_hApp)
    {
        printf("Open application first!\n");
        return FALSE;
    }

    ULONG ulReval = SKF_CloseApplication(g_hApp);
    SHOW_ERROR(ulReval);
    g_hApp = NULL;

    return (SAR_OK == ulReval);
}
