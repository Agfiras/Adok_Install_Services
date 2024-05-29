// OsAL.h: OS abstraction layer
//
// Project: 		default
// Description:	provides OS abstraction
// Author:			Michael Schanz
// Date:				04-05-2006
//
// $Id: OsAL.h,v 1.1.1.1 2006/04/06 10:23:51 sml Exp $

// WindowsCE
#if defined(UNDER_CE)
#include <windows.h>
#define main(x,y) WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
#endif

// Win32
#if defined(WIN32)
#define _CRT_SECURE_NO_DEPRECATE
#define __report(x,y) printf(x,y)
#endif

// Linux
#if defined(__GNUC__)
#define __report(x,y) fprintf(stdout,x,y)
#endif
