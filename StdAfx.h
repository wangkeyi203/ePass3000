//
// Created by 王轲毅 on 16/7/24.
//

// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__90A8020A_AEE9_4344_96C7_960D587614EA__INCLUDED_)
#define AFX_STDAFX_H__90A8020A_AEE9_4344_96C7_960D587614EA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#include <assert.h>
#if defined(WIN32)
#include <conio.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>

#else
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#endif

#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "SKFAPI.h"

#if defined(WIN32)
#ifdef _DEBUG
#pragma comment(lib,"../../escsp11/3003Debug/ShuttleCsp11_3003.lib")
#else
#pragma comment(lib,"../../escsp11/3003Release/ShuttleCsp11_3003.lib")
#endif
#endif

#define DEVNAME "ES3000GM VCR "
#include "Utilities.h"

#define SHOW_PROCESS(x) \
	CTestInfo tInfo(x);

#define SHOW_ERROR(x) \
	GetUtilities().ShowErrInfo(x);

#define SHOW_ERROR_EX(x, y) \
	printf(x); \
	SHOW_ERROR(y);


// TODO: reference additional headers your program requires here

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__90A8020A_AEE9_4344_96C7_960D587614EA__INCLUDED_)
// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__90A8020A_AEE9_4344_96C7_960D587614EA__INCLUDED_)
#define AFX_STDAFX_H__90A8020A_AEE9_4344_96C7_960D587614EA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#include <assert.h>
#if defined(WIN32)
#include <conio.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>

#else
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#endif

#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "SKFAPI.h"

#if defined(WIN32)
#ifdef _DEBUG
#pragma comment(lib,"../../escsp11/3003Debug/ShuttleCsp11_3003.lib")
#else
#pragma comment(lib,"../../escsp11/3003Release/ShuttleCsp11_3003.lib")
#endif
#endif

#define DEVNAME "ES3000GM VCR "
#include "Utilities.h"

#define SHOW_PROCESS(x) \
	CTestInfo tInfo(x);

#define SHOW_ERROR(x) \
	GetUtilities().ShowErrInfo(x);

#define SHOW_ERROR_EX(x, y) \
	printf(x); \
	SHOW_ERROR(y);


// TODO: reference additional headers your program requires here

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__90A8020A_AEE9_4344_96C7_960D587614EA__INCLUDED_)
