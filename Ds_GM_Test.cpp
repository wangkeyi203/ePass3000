//
// Created by 王轲毅 on 16/7/24.
//

// Ds_GM_Test.cpp : Defines the entry point for the console application.
//

#include "StdAfx.h"
#include "Utilities.h"

int main(int argc, char* argv[])
{
//	SHOW_ERROR(0);
    for (;;)
    {
        ShowMainMenu();
        switch(WaitForUserInput())
        {
            case 'D':
                ShowDevManageMenu();
                break;
            case 'A':
                ShowAuthenticationMenu();
                break;
            case 'P':
                ShowApplicationMenu();
                break;
            case 'F':
                ShowFileMenu();
                break;
            case 'C':
                ShowContainerMenu();
                break;
            case 'Y':
                ShowCryptoMenu();
                break;
            case '1':
                //		TestAllAuth();
                //		break;
                //	case '2':
                TestOpenContainer();
                break;
            case 'X':
                return 0;
                break;
            default:
                break;
        }
    }
    return 0;
}
