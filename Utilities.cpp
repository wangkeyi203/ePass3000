//
// Created by 王轲毅 on 16/7/24.
//

// Utilities.cpp: implementation of the CUtilities class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "AuthTest.h"
#include "ApplicationTest.h"
#include "ContainerTest.h"
#include "CryptoTest.h"
#include "DevMgntTest.h"
#include "FileOprTest.h"

#include "Utilities.h"
extern HANDLE g_hDev;
extern HANDLE g_hApp;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUtilities::CUtilities()
{

}

CUtilities::~CUtilities()
{

}

void CUtilities::ShowErrInfo(DWORD dwErrInfo)
{
    printf("\n");
    switch(dwErrInfo)
    {
        case SAR_OK						    :  printf("succeed	\n");	break;
        case SAR_FAIL					    :  printf("failed               \n");	break;
        case SAR_UNKNOWNERR				    :  printf("unexpected error            \n");	break;
        case SAR_NOTSUPPORTYETERR		    :  printf("unsupport service        \n");	break;
        case SAR_FILEERR					:  printf("file error        \n");	break;
        case SAR_INVALIDHANDLEERR		    :  printf("invalid handle          \n");	break;
        case SAR_INVALIDPARAMERR			:  printf("invalid params          \n");	break;
        case SAR_READFILEERR				:  printf("read file error          \n");	break;
        case SAR_WRITEFILEERR			    :  printf("write file error          \n");	break;
        case SAR_NAMELENERR				    :  printf("invalid file name length        \n");	break;
        case SAR_KEYUSAGEERR				:  printf("key usage error        \n");	break;
        case SAR_MODULUSLENERR			    :  printf("modulus len error        \n");	break;
        case SAR_NOTINITIALIZEERR		    :  printf("not initialize            \n");	break;
        case SAR_OBJERR					    :  printf("object error            \n");	break;
        case SAR_MEMORYERR				    :  printf("memory error            \n");	break;
        case SAR_TIMEOUTERR				    :  printf("time out                \n");	break;
        case SAR_INDATALENERR			    :  printf("invalid inputdata len    \n");	break;
        case SAR_INDATAERR				    :  printf("invalid inputdata       \n");	break;
        case SAR_GENRANDERR				    :  printf("gen rand error      \n");	break;
        case SAR_HASHOBJERR				    :  printf("hash object error          \n");	break;
        case SAR_HASHERR					:  printf("hash failed        \n");	break;
        case SAR_GENRSAKEYERR			    :  printf("gen rsa key pair failed       \n");	break;
        case SAR_RSAMODULUSLENERR		    :  printf("invalid rsa modulus len     \n");	break;
        case SAR_CSPIMPRTPUBKEYERR		    :  printf("CSP service import key failed \n");	break;
        case SAR_RSAENCERR				    :  printf("RSA encrypt failed         \n");	break;
        case SAR_RSADECERR				    :  printf("RSA decrypt failed         \n");	break;
        case SAR_HASHNOTEQUALERR			:  printf("HASH value not equal        \n");	break;
        case SAR_KEYNOTFOUNTERR			    :  printf("not found key          \n");	break;
        case SAR_CERTNOTFOUNTERR			:  printf("not found cert          \n");	break;
        case SAR_NOTEXPORTERR			    :  printf("export object failed          \n");	break;
        case SAR_DECRYPTPADERR			    :  printf("padding of decrypt error    \n");	break;
        case SAR_MACLENERR				    :  printf("invalid MAC len         \n");	break;
        case SAR_BUFFER_TOO_SMALL		    :  printf("buffer too small          \n");	break;
        case SAR_KEYINFOTYPEERR			    :  printf("invalid key type        \n");	break;
        case SAR_NOT_EVENTERR			    :  printf("no event     \n");	break;
        case SAR_DEVICE_REMOVED			    :  printf("device removed          \n");	break;
        case SAR_PIN_INCORRECT			    :  printf("PIN incorrect           \n");	break;
        case SAR_PIN_LOCKED				    :  printf("PIN locked           \n");	break;
        case SAR_PIN_INVALID				:  printf("PIN invalid             \n");	break;
        case SAR_PIN_LEN_RANGE			    :  printf("PIN len range         \n");	break;
        case SAR_USER_ALREADY_LOGGED_IN	    :  printf("user already logged in        \n");	break;
        case SAR_USER_PIN_NOT_INITIALIZED   :  printf("pin not initialized  \n");	break;
        case SAR_USER_TYPE_INVALID		    :  printf("invalid PIN type         \n");	break;
        case SAR_APPLICATION_NAME_INVALID   :  printf("invalid application name        \n");	break;
        case SAR_APPLICATION_EXISTS		    :  printf("application exists        \n");	break;
        case SAR_USER_NOT_LOGGED_IN		    :  printf("user not logged in        \n");	break;
        case SAR_APPLICATION_NOT_EXISTS	    :  printf("application not exists          \n");	break;
        case SAR_FILE_ALREADY_EXIST		    :  printf("file already exist        \n");	break;
        case SAR_NO_ROOM					:  printf("no enough space            \n");	break;
        default								:  printf("unknown error        \n");  	break;
    }
}

void CUtilities::ShowListInfo(const LPSTR pszList)
{
    if(NULL == pszList)
        return;
    LPSTR pszTemp = pszList;

    while (*pszTemp != '\0')
    {
        printf("%s\n", pszTemp);
        pszTemp += strlen((const char *)pszTemp) + 1;
    }
}

void CUtilities::ShowBinHex(unsigned char* pBin, long len)
{
    // Show 16 bytes each line.
    long lLines = len / 16;
    long lCharInLastLine = 0;
    if(0 != len % 16)
    {
        lCharInLastLine = len - lLines * 16;
        //		++lLines;
    }
    long i = 0;
    int j = 0;
    for(i = 0; i < lLines; i++)
    {
        for(j = 0; j < 16; j++)
        {
            printf("%02X ", pBin[16 * i + j]);

            if(j == 7)
                printf("- ");
        }

        printf("    ");

        for(j = 0; j < 16; j++)
        {
            if(isprint(pBin[16 * i + j]))
                printf("%c", pBin[16 * i + j]);
            else
                printf(".");
        }

        printf("\n");
    }

    if(0 != lCharInLastLine)
    {
        for(int j = 0; j < lCharInLastLine; ++j)
        {
            printf("%02X ", pBin[16 * i + j]);

            if(j == 7 && lCharInLastLine > 8)
                printf("- ");
        }

        int k = 0;

        k += ((16 - lCharInLastLine) * 3);

        if(lCharInLastLine <= 8)
        {
            k += 2;
        }

        for(int kk = 0; kk < k; ++kk)
            printf(" ");

        printf("    ");

        for(j = 0; j < lCharInLastLine; ++j)
        {
            if(isprint(pBin[16 * i + j]))
                printf("%c", pBin[16 * i + j]);
            else
                printf(".");
        }

        printf("\n");
    }

    printf("\n");
}

void CUtilities::ShowProcess(const char *pszStr, bool bStart)
{
    assert(NULL != pszStr);
    if (bStart)
        printf("\n====== Test %s Begin ======\n", pszStr);
    else
        printf("\n====== Test %s End ======\n", pszStr);
}

CUtilities & GetUtilities()
{
    static CUtilities util;
    return util;
}

int WaitForUserInput()
{
    printf("\nInput selection:");
    int ic = 0;
    int itemp = 0;
    while(1)
    {
        itemp = getchar();
        if (itemp == '\r' || itemp == '\n')
        {
            break;
        }
        else
        {
            ic = itemp;
        }
    }
//	printf("---%c---\n",ic);
    return toupper(ic);
//	return toupper(GetInputChar());
}

int GetInputChar()
{
    fflush(stdin);
    int ic = 0;
    while(1)
    {
        int it = getchar();
        if(it == '\r' || it =='\n')
        {
            break;
        }
        else
        {
            ic = it;
        }
    }
    return ic;
}

int WaitForUserInput2()
{
    int nSelect = 0;
    int ch;

    do
    {
        char tBuf[32] = {0};
        fflush(stdin);
        gets(tBuf);
        ch = sscanf(tBuf,"%d",&nSelect);

        if (0 == ch)
            getchar();

    } while (nSelect < 1 || nSelect > 99);

    return nSelect;
}

void ShowDevManageMenu()
{
    CDevMgntTest devTest;
    while(1)
    {
        printf("\n\nDev Manage Menu:\n");
        printf(	"  [W]aitForDevEvent    [E]numDev        [C]onnectDev \n"
                           "  [D]isconnectDev      GetDev[S]tate    SetL[A]bel \n"
                           "  GetDev[I]nfo         [L]ockDev        [U]nlockDev \n"
                           "  E[X]it \n");

        switch(WaitForUserInput())
        {

            case 'W':
                devTest.Test_WaitForDevEvent();
                break;
            case 'E':
                devTest.Test_EnumDev();
                break;
            case 'C':
                devTest.Test_ConnectDev();
                break;
            case 'D':
                devTest.Test_DisConnectDev();
                break;
            case 'S':
                devTest.Test_GetDevState();
                break;
            case 'A':
                devTest.Test_SetLabel();
                break;
            case 'I':
                devTest.Test_GetDevInfo();
                break;
            case 'L':
                devTest.Test_LockDev();
                break;
            case 'U':
                devTest.Test_UnlockDev();
                break;
            case 'X':
                return;
            default:
                break;
        }
    }
}

void ShowAuthenticationMenu()
{
    CAuthTest authenTest;
    while(1)
    {
        printf("\n\nAuthentication Menu:\n");
        printf("-------------------------------------------------------------\n");
        printf(	"  [C]hangeDevAuthKey    Dev[A]uth      Change[P]IN \n"
                           "  [G]etPINInfo          [V]erifyPIN    [U]nblockPIN \n"
                           "  Clear[S]ecueState     E[X]it \n");
        switch(WaitForUserInput())
        {
            case 'C':
                authenTest.Test_ChangeDevAuthKey();
                break;
            case 'A':
                authenTest.Test_DevAuth();
                break;
            case 'P':
                authenTest.Test_ChangePIN();
                break;
            case 'G':
                authenTest.Test_GetPINInfo();
                break;
            case 'V':
                authenTest.Test_VerifyPIN();
                break;
            case 'U':
                authenTest.Test_UnblockPIN();
                break;
            case 'S':
                authenTest.Test_ClearSecureState();
                break;
            case 'X':
                return;
        }
    }
}

void ShowApplicationMenu()
{
    CApplicationTest appTest;
    while(1)
    {
        printf("\n\nApplication Menu:\n");
        printf("-------------------------------------------------------------\n");
        printf(	"  Create[A]pplication    [E]numApplication        [D]eleteApplication \n"
                           "  [O]penApplication      [C]loseApplication       E[X]it \n");
        switch(WaitForUserInput())
        {
            case 'A':
                appTest.Test_CreateApplication();
                break;
            case 'E':
                appTest.Test_EnumApplication();
                break;
            case 'D':
                appTest.Test_DeleteApplication();
                break;
            case 'O':
                appTest.Test_OpenApplication();
                break;
            case 'C':
                appTest.Test_CloseApplication();
                break;
            case 'X':
                return;
        }
    }
}

void ShowFileMenu()
{
    CFileOprTest fileTest;
    while(1)
    {
        printf("\n\nFile Menu:\n");
        printf("-------------------------------------------------------------\n");
        printf(	"  [C]reateFile     [D]eleteFile    [E]numFiles \n"
                           "  [G]etFileInfo    [R]eadFile      [W]riteFile \n"
                           "  E[X]it\n");
        switch(WaitForUserInput())
        {
            case 'C':
                fileTest.Test_CreateFile();
                break;
            case 'D':
                fileTest.Test_DeleteFile();
                break;
            case 'E':
                fileTest.Test_EnumFiles();
                break;
            case 'G':
                fileTest.Test_GetFileInfo();
                break;
            case 'R':
                fileTest.Test_ReadFile();
                break;
            case 'W':
                fileTest.Test_WriteFile();
                break;
            case 'X':
                return;
        }
    }
}

void ShowContainerMenu()
{
    CContainerTest containerTest;
    while(1)
    {
        printf("\n\nContainer Menu:\n");
        printf("-------------------------------------------------------------\n");
        printf(	"  [C]reateContainer    [D]eleteContainer    [E]numContainer \n"
                           "  [O]penContainer      Clo[s]eContainer     Container[T]ype\n"
                           "  [I]mportCert		Ex[p]ortCert	     E[X]it\n");
        switch(WaitForUserInput())
        {
            case 'C':
                containerTest.Test_CreateContainer();
                break;
            case 'D':
                containerTest.Test_DeleteContainer();
                break;
            case 'E':
                containerTest.Test_EnumContainer();
                break;
            case 'O':
                containerTest.Test_OpenContainer();
                break;
            case 'S':
                containerTest.Test_CloseContainer();
                break;
            case 'T':
                containerTest.Test_GetContainerType();
                break;
            case 'I':
                containerTest.Test_ImportCertificate();
                break;
            case 'P':
                containerTest.Test_ExportCertificate();
                break;
            case 'X':
                return;
        }
    }
}
/*
[1]Encrypt & Decrypt
[2]Digest
[3]Mac
*/
void ShowCryptoMenu()
{
    CCryptoTest cryptoTest;
    while(1)
    {
        printf("\n\nCryptographic Menu:\n");
        printf("-------------------------------------------------------------\n");
        printf(	"[1]GenRandom\n"
                           "[2]GenExtRSAKey & ExtRSAPubKeyOper & ExtRSAPriKeyOper\n"
                           "[3]GenRSAKeyPair\n"
                           "[4]ImportRSAKeyPair\n"
                           "[5]RSASignData & RSAVerify\n"
                           "[6]RSAExportSessionKey\n"
                           "[7]SetSymmKey\n"
                           "[8]Encrypt & Decrypt (init Update final)\n"
                           "[9]Digest (init Update final)\n"
                           "[10]Mac (init Update final)\n"
                           "[11]GenEccSignKeyPair\n"
                           "[12]ImportEccKeyPair\n"
                           "[13]ECCExportSessionKey\n"
                           "[14]ECCSign & ECCVerify\n"
                           "[15]ExtEccOper\n"
                           "[16]ExtEccSignVerify\n"
                           "[99]Exit\n");
        switch(WaitForUserInput2())
        {
            case 1:
                cryptoTest.Test_GenRandom();
                break;
            case 2:
                cryptoTest.Test_GenExtRSAKey();
                break;
            case 3:
                cryptoTest.Test_GenRSAKeyPair();
                break;
            case 4:
                cryptoTest.Test_ImportRSAKeyPair();
                break;
            case 5:
                cryptoTest.Test_RSASignVerifyData();
                break;
            case 6:
                cryptoTest.Test_RSAExportSessionKey();
                break;
            case 7:
                cryptoTest.Test_SetSymmKey();
                break;
            case 8:
                cryptoTest.Test_EncryptDecrypt();
                break;
            case 9:
                cryptoTest.Test_Digest();
                break;
            case 10:
                cryptoTest.Test_Mac();
                break;
            case 11:
                cryptoTest.Test_GenEccKey();
                break;
            case 12:
                cryptoTest.Test_ImportEccKeyPair();
                break;
            case 13:
                cryptoTest.Test_EccExportSessionKey();
                break;
            case 14:
                cryptoTest.Test_EccSignVerify();
                break;
            case 15:
                cryptoTest.Test_ExtEccEncrypt();
                break;
            case 16:
                cryptoTest.Test_ExtEccSignVerify();
                break;
            case 99:
                return;
        }
    }
}

void TestAllAuth()
{
    printf("Verify Dev...");

    printf("Create app1(so:rockey, user:12341234, 15, 15......");
    ULONG ulReval = SKF_CreateApplication(g_hDev, (LPSTR)"app1", (LPSTR)"rockey", 6, (LPSTR)"12341234",
                                          6, SECURE_USER_ACCOUNT, &g_hApp);
    SHOW_ERROR_EX("CreateApplication", ulReval);
    if (SAR_OK != ulReval)
        return;

    printf("Open app1.....");
    ulReval = SKF_OpenApplication(g_hDev, (LPSTR)"app1", &g_hApp);
    SHOW_ERROR_EX("OpenApplication", ulReval);
    if (SAR_OK != ulReval)
        return;

    printf("Verify user.....");
    ULONG ulRetryCount = 0;
    ulReval = SKF_VerifyPIN(g_hApp, 1, (LPSTR)"12341234", &ulRetryCount);
    SHOW_ERROR_EX("VerifyPIN", ulReval);
    if (SAR_OK != ulReval)
        return;

    CAuthTest Atest;
    Atest.Test_DevAuth();

    printf("OK!\n");
}

void TestOpenContainer()
{
    CDevMgntTest dTest;
    dTest.Test_ConnectDev();
// 	printf("Connect 0.....");
// 	ULONG ulReval = SKF_ConnectDev((LPSTR)DEVNAME"1", &g_hDev);
// 	SHOW_ERROR_EX("ConnectDev", ulReval);

    printf("Open app1.....");
    ULONG ulReval = SKF_OpenApplication(g_hDev, (LPSTR)"ENTERSAFE-ESPK", &g_hApp);
    SHOW_ERROR_EX("OpenApplication", ulReval);
    if (SAR_OK != ulReval)
        return;

    printf("Verify user.....");
    ULONG ulRetryCount = 0;
    ulReval = SKF_VerifyPIN(g_hApp, 1, (LPSTR)"12341234", &ulRetryCount);
    SHOW_ERROR_EX("VerifyPIN", ulReval);
// 	if (SAR_OK != ulReval)
// 		return;

    CContainerTest cTest;
    cTest.Test_EnumContainer();
    cTest.Test_OpenContainer();

    printf("OK!\n");
}

void ShowMainMenu()
{
    printf("\n\nMain Menu:\n");
    printf("===========================================================\n");
    printf(	"[D]evMenu     [A]uthenticationMenu    A[p]plicationMenu\n"
                       "[F]ileMenu    [C]ontainerMenu         Cr[Y]ptoMenu\n"
                       "E[x]it\n"
                       "===========the following are the batch operation===========\n"
//		"[1] VerifyDev & Createapp1 & OpenApp1 & VerifyUser \n"
                       "[1] Connect 0 & Open ENTERSAFE-ESPK & VerifyUser & Open Container \n");
}

