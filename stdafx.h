// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once
#ifdef JOSBUILD

extern "C" {
    #define restrict __restrict
    // #include </home/ytatichno/os/prac/inc/string.h>  // for strnlen
    // #include </home/ytatichno/os/prac/inc/stdio.h>  // for snprintf
    #include </home/ytatichno/os/prac/inc/lib.h>  // for snprintf
}
#endif


// Modify the following defines if you have to target a platform prior to the ones specified below.
// Refer to MSDN for the latest info on corresponding values for different platforms.
#ifndef WINVER				// Allow use of features specific to Windows XP or later.
#define WINVER 0x0501		// Change this to the appropriate value to target other versions of Windows.
#endif

#ifndef _WIN32_WINNT		// Allow use of features specific to Windows XP or later.                   
#define _WIN32_WINNT 0x0501	// Change this to the appropriate value to target other versions of Windows.
#endif						

#ifndef _WIN32_WINDOWS		// Allow use of features specific to Windows 98 or later.
#define _WIN32_WINDOWS 0x0410 // Change this to the appropriate value to target Windows Me or later.
#endif

#ifndef _WIN32_IE			// Allow use of features specific to IE 6.0 or later.
#define _WIN32_IE 0x0600	// Change this to the appropriate value to target other versions of IE.
#endif

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#ifndef JOSBUILD
#include <stdio.h>
#endif
// #include <tchar.h>
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// some CString constructors will be explicit

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers
#endif

#ifndef NULL
#define NULL nullptr
#endif

// #include <afx.h>
// #include <afxwin.h>         // MFC core and standard components
// #include <afxext.h>         // MFC extensions
// #ifndef _AFX_NO_OLE_SUPPORT
// #include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
// #endif
// #ifndef _AFX_NO_AFXCMN_SUPPORT
// #include <afxcmn.h>			// MFC support for Windows Common Controls
// #endif // _AFX_NO_AFXCMN_SUPPORT

// #include <iostream>
#include "JavaClass.h"

void ShowClassInfo(JavaClass* pClass);

// #ifdef DBG_PRINT
// #define DbgPrint wprintf
// #else
// #define DbgPrint TRACE
// #endif
// #include <zlib.h>
// #pragma comment(lib, "zdll.lib")
// TODO: reference additional headers your program requires here







#ifndef MAX_STR_SIZE
#define MAX_STR_SIZE 2048
#endif

#ifndef MAX_PATH
#define MAX_PATH 256
#endif

#ifndef DLOG
#define DLOG(X) printf(">>%s\n", X)
#endif

char * append(char * l, const char * r);
