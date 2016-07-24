//
// Created by 王轲毅 on 16/7/24.
//
// ContainerTest.h: interface for the CContainerTest class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONTAINERTEST_H__7FEA27CF_9D8C_4EE0_8A75_7147775B692F__INCLUDED_)
#define AFX_CONTAINERTEST_H__7FEA27CF_9D8C_4EE0_8A75_7147775B692F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CContainerTest
{
public:
    CContainerTest();
    virtual ~CContainerTest();

/*
 *	在应用下建立指定名称的容器并返回容器句柄
 *	hApplication		[IN]应用句柄
 *	szContainerName		[IN]ASCII字符串，表示所建立容器的名称，容器名称的最大长度不能超过64字节
 *	phContainer			[OUT]返回所建立容器的容器句柄
 */
    BOOL Test_CreateContainer ();
/*
 *	在应用下删除指定名称的容器并释放容器相关的资源
 *	hApplication		[IN]应用句柄
 *	szContainerName		[IN]指向删除容器的名称
 */
    BOOL Test_DeleteContainer();

/*
 *	获取容器句柄
 *	hApplication		[IN]应用句柄
 *	szContainerName		[IN]容器名称
 *	phContainer			[OUT]返回所打开容器的句柄
 */
    BOOL Test_OpenContainer();

/*
 *	关闭容器句柄，并释放容器句柄相关资源
 *	hContainer			[OUT]容器句柄
 */
    BOOL Test_CloseContainer();

/*
 *	枚举应用下的所有容器并返回容器名称列表
 *	hApplication		[IN]应用句柄
 *	szContainerName		[OUT]指向容器名称列表缓冲区，如果此参数为NULL时，pulSize表示返回数据所需要缓冲区的长度，如果此参数不为NULL时，返回容器名称列表，每个容器名以单个'\0'为结束，列表以双'\0'结束
 *	pulSize				[OUT]调用前表示szContainerName缓冲区的长度，返回容器名称列表的长度
 */
    BOOL Test_EnumContainer();

/*
	获取容器的类型
	hContainer	[IN] 容器句柄。
	pulContainerType	[OUT] 获得的容器类型。指针指向的值为0表示未定、尚未分配类型或者为空容器，为1表示为RSA容器，为2表示为ECC容器。
*/

    BOOL Test_GetContainerType();

    BOOL Test_ImportCertificate();

    BOOL Test_ExportCertificate();
};

#endif // !defined(AFX_CONTAINERTEST_H__7FEA27CF_9D8C_4EE0_8A75_7147775B692F__INCLUDED_)
