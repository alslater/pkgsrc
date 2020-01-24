/**********************************************************
**
** This header file handles the shared library conventions
** needed by Windows and not needed by Solaris.
**
**********************************************************/

#ifndef STU_platform_H
#define STU_platform_H

/* for WIN32 */
#ifdef _WIN32
#define STDCALL __stdcall

#ifdef MAKE_DLL
#define LINKDLL __declspec(dllexport)
#else
#define LINKDLL __declspec(dllimport)
#endif

#else
/* for UNIX */
#define STDCALL

#ifdef MAKE_DLL
#define LINKDLL
#else
#define LINKDLL
#endif

#endif

#endif // STU_platform_H
