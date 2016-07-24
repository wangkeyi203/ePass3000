//
// Created by 王轲毅 on 16/7/24.
//

// ContainerTest.cpp: implementation of the CContainerTest class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "ContainerTest.h"
#include <fstream>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern HANDLE g_hApp;
HANDLE g_hCurContainer = NULL;
CContainerTest::CContainerTest()
{

}

CContainerTest::~CContainerTest()
{

}

BOOL CContainerTest::Test_CreateContainer()
{
    SHOW_PROCESS("CreateContainer");
    if (NULL == g_hApp)
    {
        printf("Open application first!\n");
        return FALSE;
    }

    char szContainerName[1024] = {0};
    printf("Input file name:(<=64)");

    fflush(stdin);
    gets(szContainerName);

    ULONG ulReval = SKF_CreateContainer(g_hApp, (LPSTR)szContainerName, &g_hCurContainer);
    SHOW_ERROR(ulReval);

    return (SAR_OK == ulReval);
}

BOOL CContainerTest::Test_DeleteContainer()
{
    SHOW_PROCESS("DeleteContainer");
    if (NULL == g_hApp)
    {
        printf("Open application first!\n");
        return FALSE;
    }

    char szContainerName[1024] = {0};
    printf("Input file name:(<=64)");

    fflush(stdin);
    gets(szContainerName);

    ULONG ulReval = SKF_DeleteContainer(g_hApp, (LPSTR)szContainerName);
    SHOW_ERROR(ulReval);

    return (SAR_OK == ulReval);
}

BOOL CContainerTest::Test_OpenContainer()
{
    SHOW_PROCESS("OpenContainer");
    if (NULL == g_hApp)
    {
        printf("Open application first!\n");
        return FALSE;
    }

    char szContainerName[1024] = {0};
    printf("Input container name(<=64):");

    fflush(stdin);
    gets(szContainerName);
    if(szContainerName[0] == '\0' || szContainerName[0] == '\r' || szContainerName[0] == '\n')
        gets(szContainerName);

    ULONG ulReval = SKF_OpenContainer(g_hApp, (LPSTR)szContainerName, &g_hCurContainer);
    SHOW_ERROR(ulReval);

    return (SAR_OK == ulReval);
}

BOOL CContainerTest::Test_CloseContainer()
{
    SHOW_PROCESS("CloseContainer");
    if (NULL == g_hApp)
    {
        printf("Open application first!\n");
        return FALSE;
    }

    if (NULL == g_hCurContainer)
    {
        printf("You should open at least one container!\n");
        return FALSE;
    }

    ULONG ulReval = SKF_CloseContainer(g_hCurContainer);
    SHOW_ERROR(ulReval);

    return (SAR_OK == ulReval);
}

BOOL CContainerTest::Test_EnumContainer()
{
    SHOW_PROCESS("EnumContainer");
    if (NULL == g_hApp)
    {
        printf("Open application first!\n");
        return FALSE;
    }

    char szContainerList[1024] = {0};
    ULONG ulSize = 1024;

    ULONG ulReval = SKF_EnumContainer(g_hApp, (LPSTR)szContainerList, &ulSize);
    SHOW_ERROR(ulReval);

    if (SAR_OK == ulReval)
    {
        GetUtilities().ShowListInfo((LPSTR)szContainerList);
    }
    return (SAR_OK == ulReval);
}

BOOL CContainerTest::Test_GetContainerType()
{
    SHOW_PROCESS("GetContainerType");
    ULONG ulContainerType = 0;

    ULONG ulReval = SKF_GetContainerType(g_hCurContainer, &ulContainerType);
    SHOW_ERROR(ulReval);
    if (SAR_OK != ulReval)
        return FALSE;

    switch(ulContainerType)
    {
        case 0 : printf("Empty\n");    break;
        case 1 : printf("RSA type\n");   break;
        case 2 : printf("ECC type\n");   break;
        default: printf("Error type\n"); break;
    }

    return (SAR_OK == ulReval);
}

BOOL CContainerTest::Test_ImportCertificate()
{
    SHOW_PROCESS("ImportCertificate");
    if (NULL == g_hApp)
    {
        printf("Open application first!\n");
        return FALSE;
    }

    if (NULL == g_hCurContainer)
    {
        char szContainerName[1024] = {0};
        printf("Input container name(<=64):");
        fflush(stdin);
        gets(szContainerName);
        if(szContainerName[0] == '\0' || szContainerName[0] == '\r' || szContainerName[0] == '\n')
            gets(szContainerName);
        ULONG ulReval = SKF_OpenContainer(g_hApp, (LPSTR)szContainerName, &g_hCurContainer);
        SHOW_ERROR(ulReval);
    }

    char szCertPath[200] = {0};
    printf("Input the full path of the cert(<200):");
    fflush(stdin);
    gets(szCertPath);

    char* buffer = NULL;
    long filesize = 0;
    long ltemp = 0;
    std::ifstream certfile;
    certfile.open(szCertPath, ios::in|ios::binary);
    ltemp = certfile.tellg();
    certfile.seekg(0, ios::end);
    filesize = certfile.tellg();
    filesize -= ltemp;
    buffer = new char[filesize+1];
    memset(buffer, 0, filesize+1);
    certfile.seekg(0, ios::beg);
    certfile.read(buffer, filesize);
    certfile.close();
    ULONG rv = SKF_ImportCertificate(g_hCurContainer, TRUE, (BYTE*)buffer, filesize);
    SHOW_ERROR(rv);
    return (SAR_OK == rv);
}

BOOL CContainerTest::Test_ExportCertificate()
{
    SHOW_PROCESS("ExportCertificate");
    if (NULL == g_hApp)
    {
        printf("Open application first!\n");
        return FALSE;
    }

    if (NULL == g_hCurContainer)
    {
        char szContainerName[1024] = {0};
        printf("Input container name(<=64):");
        fflush(stdin);
        gets(szContainerName);
        if(szContainerName[0] == '\0' || szContainerName[0] == '\r' || szContainerName[0] == '\n')
            gets(szContainerName);
        ULONG ulReval = SKF_OpenContainer(g_hApp, (LPSTR)szContainerName, &g_hCurContainer);
        SHOW_ERROR(ulReval);
    }
    ULONG ulCertLen = 0;
    ULONG rv = SKF_ExportCertificate(g_hCurContainer, TRUE, NULL, &ulCertLen);
    if(SAR_OK != rv)
        return FALSE;
    BYTE* pCert = NULL;
    pCert = new BYTE[ulCertLen+1];
    memset(pCert, 0, ulCertLen+1);
    rv = SKF_ExportCertificate(g_hCurContainer, TRUE, pCert, &ulCertLen);
    SHOW_ERROR(rv);
    return (SAR_OK == rv);
}
