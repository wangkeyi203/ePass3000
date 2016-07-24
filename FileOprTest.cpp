//
// Created by 王轲毅 on 16/7/24.
//

// FileOprTest.cpp: implementation of the CFileOprTest class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "FileOprTest.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern HANDLE g_hApp;
CFileOprTest::CFileOprTest()
{

}

CFileOprTest::~CFileOprTest()
{

}

BOOL CFileOprTest::Test_CreateFile()
{
    SHOW_PROCESS("CreateFile");
    if (NULL == g_hApp)
    {
        printf("Open application first!\n");
        return FALSE;
    }

    char szFileName[512] = {0};
    printf("Input file name:(<=32)");

    fflush(stdin);
    gets(szFileName);

    ULONG ulFileSize;
    printf("Input size of file:");

    fflush(stdin);
    int ret = scanf("%lu", &ulFileSize);
    if(ret != 1)
    {
        printf("error input\n");
        return FALSE;
    }

    UINT32 urRights;
    UINT32 uwRights;

    printf("Input read rights: 0:nobody, 1:admin, 2:user, 3:anyone\n");
    ret = scanf("%d", &urRights);
    if(ret != 1)
    {
        printf("error input\n");
        return FALSE;
    }
    urRights = GetRights(urRights);

    printf("Input write rights: 0:nobody, 1:admin, 2:user, 3:anyone\n");
    ret = scanf("%d", &uwRights);
    if(ret != 1)
    {
        printf("error input\n");
        return FALSE;
    }
    uwRights = GetRights(uwRights);

    ULONG ulReval = SKF_CreateFile(g_hApp, (LPSTR)szFileName, ulFileSize, urRights, uwRights);
    SHOW_ERROR(ulReval);

    return (SAR_OK == ulReval);
}

BOOL CFileOprTest::Test_DeleteFile()
{
    SHOW_PROCESS("DeleteFile");
    if (NULL == g_hApp)
    {
        printf("Open application first!\n");
        return FALSE;
    }

    char szFileName[512] = {0};
    printf("Input file name which you wanna delete:(<32)");

    fflush(stdin);
    gets(szFileName);

    ULONG ulReval = SKF_DeleteFile(g_hApp, (LPSTR)szFileName);
    SHOW_ERROR(ulReval);
    return (SAR_OK == ulReval);
}

BOOL CFileOprTest::Test_EnumFiles()
{
    SHOW_PROCESS("EnumFiles");
    if (NULL == g_hApp)
    {
        printf("Open application first!\n");
        return FALSE;
    }

    char szFileList[1024] = {0};
    ULONG ulSize = 1024;

    ULONG ulReval = SKF_EnumFiles(g_hApp, (LPSTR)szFileList, &ulSize);
    SHOW_ERROR(ulReval);

    if (SAR_OK == ulReval)
    {
        GetUtilities().ShowListInfo((LPSTR)szFileList);
    }
    return (SAR_OK == ulReval);
}

BOOL CFileOprTest::Test_GetFileInfo()
{
    SHOW_PROCESS("GetFileInfo");
    if (NULL == g_hApp)
    {
        printf("Open application first!\n");
        return FALSE;
    }

    char szFileName[32] = {0};
    printf("Input file name:(<32)");

    fflush(stdin);
    gets(szFileName);

    FILEATTRIBUTE fileAttr;
    ULONG ulReval = SKF_GetFileInfo(g_hApp, (LPSTR)szFileName, &fileAttr);
    SHOW_ERROR(ulReval);

    if (SAR_OK == ulReval)
    {
        printf("File Name is: %s\n", fileAttr.FileName);
        printf("File Size is: %d\n", fileAttr.FileSize);
        printf("File read rights: %ld\n", fileAttr.ReadRights);
        printf("File write rights: %ld\n", fileAttr.WriteRights);
    }
    return (SAR_OK == ulReval);
}

BOOL CFileOprTest::Test_ReadFile()
{
    SHOW_PROCESS("ReadFile");
    if (NULL == g_hApp)
    {
        printf("Open application first!\n");
        return FALSE;
    }

    char szFileName[32] = {0};
    printf("Input file name:(<32)");

    fflush(stdin);
    gets(szFileName);

    ULONG ulOffset = 0;
    printf("Input offset:");

    fflush(stdin);
    int ret = scanf("%d", &ulOffset);
    if(ret != 1)
    {
        printf("error input\n");
        return FALSE;
    }

    ULONG ulSize = 0;
    printf("Input read length:");

    fflush(stdin);
    ret = scanf("%d", &ulSize);
    if(ret != 1)
    {
        printf("error input\n");
        return FALSE;
    }

    vector<char> pData(ulSize + 1, 0);
    ULONG ulSizeOut;
    ULONG ulReval = SKF_ReadFile(g_hApp, (LPSTR)szFileName, ulOffset, ulSize, (BYTE *)&pData[0], &ulSizeOut);
    SHOW_ERROR(ulReval);

    if (SAR_OK == ulReval)
    {
        GetUtilities().ShowBinHex((unsigned char *)&pData[0], ulSize);
    }

    return (SAR_OK == ulReval);
}

BOOL CFileOprTest::Test_WriteFile()
{
    SHOW_PROCESS("WriteFile");
    if (NULL == g_hApp)
    {
        printf("Open application first!\n");
        return FALSE;
    }

    char szFileName[32] = {0};
    printf("Input file name:(<32)");

    fflush(stdin);
    gets(szFileName);

    ULONG ulOffset = 0;
    printf("Input offset:");

    fflush(stdin);
    int ret = scanf("%d", &ulOffset);
    if(ret != 1)
    {
        printf("error input\n");
        return FALSE;
    }

    ULONG ulSize = 0;
    printf("Input write length:");

    fflush(stdin);
    ret = scanf("%d", &ulSize);
    if(ret != 1)
    {
        printf("error input\n");
        return FALSE;
    }

    vector<char> pData(ulSize + 1, 0x31);
    pData[ulSize] = 0x00;
    ULONG ulReval = SKF_WriteFile(g_hApp, (LPSTR)szFileName, ulOffset, (BYTE *)&pData[0], ulSize);
    SHOW_ERROR(ulReval);

    if (SAR_OK == ulReval)
    {
        GetUtilities().ShowBinHex((unsigned char *)&pData[0], ulSize);
    }
    return (SAR_OK == ulReval);
}

ULONG CFileOprTest::GetRights(ULONG uRigts)
{
    switch (uRigts)
    {
        case 0:
            return SECURE_NEVER_ACCOUNT;
        case 1:
            return SECURE_ADM_ACCOUNT;
        case 2:
            return SECURE_USER_ACCOUNT;
        case 3:
            return SECURE_EVERYONE_ACCOUNT;
        default:
            return 0xffffffff;
    }
}
