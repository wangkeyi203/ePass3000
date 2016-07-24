//
// Created by 王轲毅 on 16/7/24.
//

// FileOprTest.h: interface for the CFileOprTest class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEOPRTEST_H__A58BBDA5_5F91_41F9_BAF7_AEBFE4F7BF47__INCLUDED_)
#define AFX_FILEOPRTEST_H__A58BBDA5_5F91_41F9_BAF7_AEBFE4F7BF47__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFileOprTest
{
public:
    CFileOprTest();
    virtual ~CFileOprTest();

    /*
    *	创建一个文件。创建文件时要指定文件的名称，大小，以及文件的读写权限
    *	hApplication		[IN]应用句柄
    *	szFileName			[IN]文件名称，长度不得大于32个字节
    *	ulFileSize			[IN]文件大小
    *	ulReadRights		[IN]文件读权限
    *	ulWriteRights		[IN]文件写权限
    */
    BOOL Test_CreateFile ();

    /*
    *	删除指定文件，文件删除后，文件中写入的所有信息将丢失。文件在设备中的占用的空间将被释放。
    *	hApplication		[IN]要删除文件所在的应用句柄
    *	szFileName			[IN]要删除文件的名称
    */
    BOOL Test_DeleteFile ();
    /*
    *	枚举一个应用下存在的所有文件
    *	hApplication		[IN]应用的句柄
    *	szFileList			[OUT]返回文件名称列表，该参数为空，由pulSize返回文件信息所需要的空间大小。每个文件名称以单个'\0'结束，以双'\0'表示列表的结束。
    *	pulSize				[OUT]输入为数据缓冲区的大小，输出为实际文件名称的大小
    */
    BOOL Test_EnumFiles ();

    /*
    *	获取应用文件的属性信息，例如文件的大小、权限等
    *	hApplication		[IN]文件所在应用的句柄
    *	szFileName			[IN]文件名称
    *	pFileInfo			[OUT]文件信息，指向文件属性结构的指针
    */
    BOOL Test_GetFileInfo ();

    /*
    *	读取文件内容
    *	hApplication		[IN]文件所在的应用句柄
    *	szFileName			[IN]文件名
    *	ulOffset			[IN]文件读取偏移位置
    *	ulSize				[IN]要读取的长度
    *	pbOutData			[OUT]返回数据的缓冲区
    *	pulOutLen			[OUT]输入表示给出的缓冲区大小；输出表示实际读取返回的数据大小
    */
    BOOL Test_ReadFile ();

    /*
    *	写数据到文件中
    *	hApplication		[IN]文件所在的应用句柄
    *	szFileName			[IN]文件名
    *	ulOffset			[IN]写入文件的偏移量
    *	pbData				[IN]写入数据缓冲区
    *	ulSize				[IN]写入数据的大小
    */
    BOOL Test_WriteFile ();

protected:
    ULONG GetRights(ULONG uRigts);
};

#endif // !defined(AFX_FILEOPRTEST_H__A58BBDA5_5F91_41F9_BAF7_AEBFE4F7BF47__INCLUDED_)
