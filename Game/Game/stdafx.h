// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// reference additional headers your program requires here
#include <d3d9.h>
#include <d3dx9.h>
#include <memory>

#include <string>
#include <string.h>
#include <signal.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>

#include <dinput.h>


namespace DebugHelper {
	inline void DebugOut(const wchar_t *fmt, ...)
	{
		va_list argp;
		va_start(argp, fmt);
		wchar_t dbg_out[4096];
		vswprintf_s(dbg_out, fmt, argp);
		va_end(argp);
		OutputDebugString(dbg_out);
	}
}