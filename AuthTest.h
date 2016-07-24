//
// Created by 王轲毅 on 16/7/24.
//

// AuthTest.h: interface for the CAuthTest class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AUTHTEST_H__2B6BDBFB_E677_4D11_A505_289F8AB52271__INCLUDED_)
#define AFX_AUTHTEST_H__2B6BDBFB_E677_4D11_A505_289F8AB52271__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CAuthTest
{
public:
    CAuthTest();
    virtual ~CAuthTest();

    /*
    *	更改设备认证密钥
    *	hDev		[IN]连接时返回的设备句柄
    *	pbKeyValue	[IN]密钥值
    *	ulKeyLen	[IN]密钥长度
    */
    BOOL Test_ChangeDevAuthKey ();

    /*
    *	设备认证是设备对应用程序的认证
    *	hDev			[IN]连接时返回的设备句柄
    *	pbAuthData		[IN]认证数据
    *	ulLen			[IN]认证数据的长度
    */
    BOOL Test_DevAuth ();
    /*
    *	修改PIN，可以修改Admin和User的PIN，如果原PIN错误，返回剩余重试次数，当剩余次数为0时，表示PIN已经被锁死
    *	hApplication	[IN]应用句柄
    *	ulPINType		[IN]PIN类型，可以为ADMIN_TYPE=0，或USER_TYPE=1
    *	szOldPIN		[IN]原PIN值
    *	szNewPIN		[IN]新PIN值
    *	pulRetryCount	[OUT]出错后重试次数
    */
    BOOL Test_ChangePIN ();

    /*
    *	获取PIN码信息，包括最大重试次数、当前剩余重试次数，以及当前PIN码是否为出厂默认PIN码
    *	hApplication		[IN]应用句柄
    *	ulPINType			[IN]PIN类型
    *	pulMaxRetryCount	[OUT]最大重试次数
    *	pulRemainRetryCount	[OUT]当前剩余重试次数，当为0时表示已锁死
    *	pbDefaultPin		[OUT]是否为出厂默认PIN码
    */
    BOOL Test_GetPINInfo();

    /*
    *	校验PIN码。校验成功后，会获得相应的权限，如果PIN码错误，会返回PIN码的重试次数，当重试次数为0时表示PIN码已经锁死
    *	hApplication	[IN]应用句柄
    *	ulPINType		[IN]PIN类型，可以为ADMIN_TYPE=0，或USER_TYPE=1
    *	szPIN			[IN]PIN值
    *	pulRetryCount	[OUT]出错后返回的重试次数
    */
    BOOL Test_VerifyPIN ();
    /*
    *	当用户的PIN码锁死后，通过调用该函数来解锁用户PIN码。
    *	解锁后，用户PIN码被设置成新值，用户PIN码的重试次数也恢复到原值。
    *	hApplication	[IN]应用句柄
    *	szAdminPIN		[IN]管理员PIN码
    *	szNewUserPIN	[IN]新的用户PIN码
    *	pulRetryCount	[OUT]管理员PIN码错误时，返回剩余重试次数
    */
    BOOL Test_UnblockPIN ();

    /*
    *	清除应用当前的安全状态
    *	hApplication	[IN]应用句柄
    */
    BOOL Test_ClearSecureState ();

protected:
    HANDLE m_hSessionKey;
};

#endif // !defined(AFX_AUTHTEST_H__2B6BDBFB_E677_4D11_A505_289F8AB52271__INCLUDED_)
