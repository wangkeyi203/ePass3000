//
// Created by 王轲毅 on 16/7/24.
//

// DevMgntTest.h: interface for the CDevMgntTest class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEVMGNTTEST_H__28DE5DD8_D2A0_4D03_AB6E_888C6A2D6327__INCLUDED_)
#define AFX_DEVMGNTTEST_H__28DE5DD8_D2A0_4D03_AB6E_888C6A2D6327__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDevMgntTest
{
public:
    CDevMgntTest();
    virtual ~CDevMgntTest();

    /*
    *	等待设备的插拔事件
    *	szDevName		[OUT]返回发生事件的设备名称
    *	pulDevNameLen	[IN,OUT]输入/输出参数，当输入时表示缓冲区长度，输出时表示设备名称的有效长度,长度包含字符串结束符
    *	pulEvent		[OUT]事件类型。1表示插入，2表示拔出
    *	备注: 该函数是阻塞调用的
    */
    BOOL Test_WaitForDevEvent();
    BOOL Test_CancelWaitForDevEvent();

    /*
    *	获得当前系统中的设备列表
    *	bPresent		[IN]为TRUE表示取当前设备状态为存在的设备列表。为FALSE表示取当前驱动支持的设备列表
    *	szNameList		[OUT]设备名称列表。如果该参数为NULL，将由pulSize返回所需要的内存空间大小。每个设备的名称以单个'\0'结束，以双'\0'表示列表的结束
    *	pulSize			[IN,OUT]输入参数，输入设备名称列表的缓冲区长度，输出参数，返回szNameList所需要的空间大小
    */
    BOOL Test_EnumDev();
    /*
    *	通过设备名称连接设备，返回设备的句柄
    *	szName		[IN]设备名称
    *	phDev		[OUT]返回设备操作句柄
    */
    BOOL Test_ConnectDev ();
    /*
    *	断开一个已经连接的设备，并释放句柄。
    *	hDev		[IN]连接设备时返回的设备句柄
    */
    BOOL Test_DisConnectDev ();
    /*
    *	获取设备是否存在的状态
    *	szDevName	[IN]连接名称
    *	pulDevState	[OUT]返回设备状态
    */
    BOOL Test_GetDevState();
    /*
    *	设置设备标签
    *	hDev		[IN]连接设备时返回的设备句柄
    *	szLabel		[OUT]设备标签字符串。该字符串应小于32字节
    */
    BOOL Test_SetLabel ();
    /*
    *	获取设备的一些特征信息，包括设备标签、厂商信息、支持的算法等
    *	hDev		[IN]连接设备时返回的设备句柄
    *	pDevInfo	[OUT]返回设备信息
    */
    BOOL Test_GetDevInfo ();
    /*
    *	获得设备的独占使用权
    *	hDev		[IN]连接设备时返回的设备句柄
    *	ulTimeOut	[IN]超时时间，单位为毫秒。如果为0xFFFFFFFF表示无限等待
    */
    BOOL Test_LockDev ();
    /*
    *	释放对设备的独占使用权
    *	hDev		[IN]连接设备时返回的设备句柄
    */
    BOOL Test_UnlockDev ();

};

#endif // !defined(AFX_DEVMGNTTEST_H__28DE5DD8_D2A0_4D03_AB6E_888C6A2D6327__INCLUDED_)
