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


namespace MathHelper {
	inline float findDistance(D3DXVECTOR2 p1, D3DXVECTOR2 p2)
	{
		return sqrt(abs(pow(p1.x - p2.x, 2)) + abs(pow(p1.y - p2.y, 2)));
	}
}

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

inline std::wstring s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}

// For memory leak detection
#if defined(DEBUG) | defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>  
#define DBG_NEW new( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
#define DBG_NEW new
#endif