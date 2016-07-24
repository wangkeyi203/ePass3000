//
// Created by 王轲毅 on 16/7/24.
//

// ApplicationTest.h: interface for the CApplicationTest class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_APPLICATIONTEST_H__CE91A321_66BE_42CF_8A1B_57876CD38429__INCLUDED_)
#define AFX_APPLICATIONTEST_H__CE91A321_66BE_42CF_8A1B_57876CD38429__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CApplicationTest
{
public:
    CApplicationTest();
    virtual ~CApplicationTest();

    /*
 *	创建一个应用
 *	hDev					[IN]连接设备时返回的设备句柄
 *	szAppName				[IN]应用名称
 *	szAdminPIN				[IN]管理员PIN
 *	dwAdminPinRetryCount	[IN]管理员PIN最大重试次数
 *	szUserPIN				[IN]用户PIN
 *	dwAdminPinRetryCount	[IN]用户PIN最大重试次数
 *	dwCreateFileRights		[IN]在该应用下创建文件和容器的权限
 *	phApplication			[OUT]应用的句柄
 */
    BOOL Test_CreateApplication();

/*
 *	枚举设备中所存在的所有应用
 *	hDev			[IN]连接设备时返回的设备句柄
 *	szAppName		[OUT]返回应用名称列表, 如果该参数为空，将由pulSize返回所需要的内存空间大小。
 *						 每个应用的名称以单个'\0'结束，以双'\0'表示列表的结束。
 *	pulSize			[IN,OUT]输入参数，输入应用名称的缓冲区长度，输出参数，返回szAppName所占用的的空间大小
 */
    BOOL Test_EnumApplication();
/*
 *	删除指定的应用
 *	hDev			[IN]连接设备时返回的设备句柄
 *	szAppName		[IN]应用名称
 */
    BOOL Test_DeleteApplication();
/*
 *	打开指定的应用
 *	hDev			[IN]连接设备时返回的设备句柄
 *	szAppName		[IN]应用名称
 *	phApplication	[OUT]应用的句柄
 */
    BOOL Test_OpenApplication();
/*
 *	关闭应用并释放应用句柄
 *	hApplication	[IN]应用的句柄
 */
    BOOL Test_CloseApplication();
};

#endif // !defined(AFX_APPLICATIONTEST_H__CE91A321_66BE_42CF_8A1B_57876CD38429__INCLUDED_)
