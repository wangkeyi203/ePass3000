//
// Created by 王轲毅 on 16/7/24.
//

// CryptoTest.h: interface for the CCryptoTest class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CRYPTOTEST_H__3BD7BFB1_79C3_4F44_AC8D_A86105A1DB8C__INCLUDED_)
#define AFX_CRYPTOTEST_H__3BD7BFB1_79C3_4F44_AC8D_A86105A1DB8C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCryptoTest
{
public:
    CCryptoTest();
    virtual ~CCryptoTest();

    BOOL Test_GenRandom();

    BOOL Test_GenExtRSAKey();
    BOOL Test_GenRSAKeyPair();
    BOOL Test_RSAExportSessionKey();
    BOOL Test_RSASignVerifyData();
    BOOL Test_ImportRSAKeyPair();

    BOOL Test_SetSymmKey();
    BOOL Test_EncryptDecrypt();

    BOOL Test_Digest();
    BOOL Test_Mac();

    ///ECC : not implemented.///
    BOOL Test_GenEccKey();
    BOOL Test_ImportEccKeyPair();
    BOOL Test_EccExportSessionKey();
    BOOL Test_EccSignVerify();
    BOOL Test_ExtEccEncrypt();
    BOOL Test_ExtEccSignVerify();

protected:
    HANDLE g_hSessionKey;
};

#endif // !defined(AFX_CRYPTOTEST_H__3BD7BFB1_79C3_4F44_AC8D_A86105A1DB8C__INCLUDED_)
