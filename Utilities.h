//
// Created by 王轲毅 on 16/7/24.
//

// Utilities.h: interface for the CUtilities class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UTILITIES_H__55B06CBB_65C2_451B_9D77_4AA2594E8FCC__INCLUDED_)
#define AFX_UTILITIES_H__55B06CBB_65C2_451B_9D77_4AA2594E8FCC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CUtilities
{
public:
    CUtilities();
    virtual ~CUtilities();

    void ShowProcess(const char *pszStr, bool bStart);
    void ShowErrInfo(DWORD dwErrInfo);
    void ShowListInfo(const LPSTR pszList);
    void ShowBinHex(unsigned char* pBin, long len);
};

CUtilities &GetUtilities();

class CTestInfo
{
public:
    CTestInfo(const LPSTR pszStr): strName(pszStr)
    {
        GetUtilities().ShowProcess(pszStr, true);
    }

    ~CTestInfo()
    {
        GetUtilities().ShowProcess(strName.c_str(), false);
    }

    string strName;
};

int WaitForUserInput();
int GetInputChar();
void ShowDevManageMenu();
void ShowAuthenticationMenu();
void ShowApplicationMenu();
void ShowFileMenu();
void ShowContainerMenu();
void ShowCryptoMenu();
void ShowMainMenu();

void TestOpenContainer();
void TestAllAuth();

#endif // !defined(AFX_UTILITIES_H__55B06CBB_65C2_451B_9D77_4AA2594E8FCC__INCLUDED_)
