/*
 *          Copyright 2022, Vitali Baumtrok.
 * Distributed under the Boost Software License, Version 1.0.
 *     (See accompanying file LICENSE or copy at
 *        http://www.boost.org/LICENSE_1_0.txt)
 */

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <gl/GL.h>
#include "win32ogl.h"
#include "win32ogl_opengl_t.h"

/* Go functions can not be passed to c directly.            */
/* They can only be called from c.                          */
/* This code is an indirection to call Go callbacks.        */
/* _cgo_export.h is generated automatically by cgo.         */
#include "_cgo_export.h"

#define DUMMY_CLASS_NAME TEXT("win32ogl")

typedef struct {
	HDC dc;
	HGLRC rc;
} context_t;

typedef struct {
	WNDCLASSEX cls;
	HWND hndl;
	context_t ctx;
} window_t;

static void error_set(win32ogl_error_t *const err, int *const err_is, const int err_type, const int err_num, const DWORD err_win32, win32ogl_lpcstr const err_str) {
	err_is[0] = 1;
	err[0].type = err_type;
	err[0].num = err_num;
	err[0].win32 = (win32ogl_ul_t)err_win32;
	err[0].str = err_str;
}

static void dummy_class_init(window_t *const dummy, HINSTANCE const instance, win32ogl_error_t *const err, int *const err_is) {
	dummy[0].cls.cbSize = sizeof(WNDCLASSEX);
	dummy[0].cls.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	dummy[0].cls.lpfnWndProc = DefWindowProc;
	dummy[0].cls.cbClsExtra = 0;
	dummy[0].cls.cbWndExtra = 0;
	dummy[0].cls.hInstance = instance;
	dummy[0].cls.hIcon = NULL;
	dummy[0].cls.hCursor = NULL;
	dummy[0].cls.hbrBackground = NULL;
	dummy[0].cls.lpszMenuName = NULL;
	dummy[0].cls.lpszClassName = TEXT("g2d_dummy");
	dummy[0].cls.hIconSm = NULL;
	if (RegisterClassEx(&dummy[0].cls) == INVALID_ATOM) {
		dummy[0].cls.lpszClassName = NULL;
		error_set(err, err_is, 0, 2, GetLastError(), NULL);
	}
}

static void dummy_window_create(window_t *const dummy, win32ogl_error_t *const err, int *const err_is) {
	if (err_is[0] == 0) {
		dummy[0].hndl = CreateWindow(dummy[0].cls.lpszClassName, TEXT("Dummy"), WS_OVERLAPPEDWINDOW, 0, 0, 1, 1, NULL, NULL, dummy[0].cls.hInstance, NULL);
		if (!dummy[0].hndl)
			error_set(err, err_is, 0, 3, GetLastError(), NULL);
	}
}

static void dummy_context_init(window_t *const dummy, win32ogl_error_t *const err, int *const err_is) {
	if (err_is[0] == 0) {
		dummy[0].ctx.dc = GetDC(dummy[0].hndl);
		if (dummy[0].ctx.dc) {
			int pixelFormat;
			PIXELFORMATDESCRIPTOR pixelFormatDesc;
			ZeroMemory(&pixelFormatDesc, sizeof(PIXELFORMATDESCRIPTOR));
			pixelFormatDesc.nSize = sizeof(PIXELFORMATDESCRIPTOR);
			pixelFormatDesc.nVersion = 1;
			pixelFormatDesc.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;
			pixelFormatDesc.iPixelType = PFD_TYPE_RGBA;
			pixelFormatDesc.cColorBits = 32;
			pixelFormatDesc.cAlphaBits = 8;
			pixelFormatDesc.cDepthBits = 24;
			pixelFormat = ChoosePixelFormat(dummy[0].ctx.dc, &pixelFormatDesc);
			if (pixelFormat) {
				if (SetPixelFormat(dummy[0].ctx.dc, pixelFormat, &pixelFormatDesc)) {
					dummy[0].ctx.rc = wglCreateContext(dummy[0].ctx.dc);
					if (!dummy[0].ctx.rc) {
						error_set(err, err_is, 0, 7, GetLastError(), NULL);
					}
				} else {
					error_set(err, err_is, 0, 6, GetLastError(), NULL);
				}
			} else {
				error_set(err, err_is, 0, 5, GetLastError(), NULL);
			}
		} else {
			error_set(err, err_is, 0, 4, GetLastError(), NULL);
		}
	}
}

static void dummy_destroy(window_t *const dummy, win32ogl_error_t *const err, int *const err_is) {
	if (dummy[0].ctx.rc) {
		if (dummy[0].ctx.rc == wglGetCurrentContext() && !wglMakeCurrent(NULL, NULL) && err_is[0] == 0)
			error_set(err, err_is, 0, 9, GetLastError(), NULL);
		if (!wglDeleteContext(dummy[0].ctx.rc) && err_is[0] == 0)
			error_set(err, err_is, 0, 10, GetLastError(), NULL);
	}
	if (dummy[0].ctx.dc) {
		ReleaseDC(dummy[0].hndl, dummy[0].ctx.dc);
	}
	if (dummy[0].hndl) {
		if (!DestroyWindow(dummy[0].hndl) && err_is[0] == 0)
			error_set(err, err_is, 0, 11, GetLastError(), NULL);
	}
	if (dummy[0].cls.lpszClassName) {
		if (!UnregisterClass(dummy[0].cls.lpszClassName, dummy[0].cls.hInstance) && err_is[0] == 0)
			error_set(err, err_is, 0, 12, GetLastError(), NULL);
	}
	free((void*)dummy);
}

static void *get_proc(LPCSTR const func_name, const int err_num, win32ogl_error_t *const err, int *const err_is) {
	void *proc = NULL;
	if (err_is[0] == 0) {
		// wglGetProcAddress could return -1, 1, 2 or 3 on failure (https://www.khronos.org/opengl/wiki/Load_OpenGL_Functions).
		proc = (void*)wglGetProcAddress(func_name);
		const DWORD err_win32 = GetLastError();
		if (err_win32) {
			proc = NULL;
			error_set(err, err_is, 1, err_num, err_win32, func_name);
		}
	}
	return proc;
}

static void wgl_functions_init(win32ogl_opengl_t *const opengl, win32ogl_error_t *const err, int *const err_is) {
	opengl[0].wglChoosePixelFormatARB    = get_proc("wglChoosePixelFormatARB",    15, err, err_is);
	opengl[0].wglCreateContextAttribsARB = get_proc("wglCreateContextAttribsARB", 15, err, err_is);
	opengl[0].wglSwapIntervalEXT         = get_proc("wglSwapIntervalEXT",         15, err, err_is);
	opengl[0].wglGetSwapIntervalEXT      = get_proc("wglGetSwapIntervalEXT",      15, err, err_is);
}

static void ogl_functions_init(win32ogl_opengl_t *const opengl, win32ogl_error_t *const err, int *const err_is) {
	opengl[0].glCreateShader            = get_proc("glCreateShader",            16, err, err_is);
	opengl[0].glShaderSource            = get_proc("glShaderSource",            16, err, err_is);
	opengl[0].glCompileShader           = get_proc("glCompileShader",           16, err, err_is);
	opengl[0].glGetShaderiv             = get_proc("glGetShaderiv",             16, err, err_is);
	opengl[0].glGetShaderInfoLog        = get_proc("glGetShaderInfoLog",        16, err, err_is);
	opengl[0].glCreateProgram           = get_proc("glCreateProgram",           16, err, err_is);
	opengl[0].glAttachShader            = get_proc("glAttachShader",            16, err, err_is);
	opengl[0].glLinkProgram             = get_proc("glLinkProgram",             16, err, err_is);
	opengl[0].glValidateProgram         = get_proc("glValidateProgram",         16, err, err_is);
	opengl[0].glGetProgramiv            = get_proc("glGetProgramiv",            16, err, err_is);
	opengl[0].glGetProgramInfoLog       = get_proc("glGetProgramInfoLog",       16, err, err_is);
	opengl[0].glGenBuffers              = get_proc("glGenBuffers",              16, err, err_is);
	opengl[0].glGenVertexArrays         = get_proc("glGenVertexArrays",         16, err, err_is);
	opengl[0].glGetAttribLocation       = get_proc("glGetAttribLocation",       16, err, err_is);
	opengl[0].glBindVertexArray         = get_proc("glBindVertexArray",         16, err, err_is);
	opengl[0].glEnableVertexAttribArray = get_proc("glEnableVertexAttribArray", 16, err, err_is);
	opengl[0].glVertexAttribPointer     = get_proc("glVertexAttribPointer",     16, err, err_is);
	opengl[0].glBindBuffer              = get_proc("glBindBuffer",              16, err, err_is);
	opengl[0].glBufferData              = get_proc("glBufferData",              16, err, err_is);
	opengl[0].glGetVertexAttribPointerv = get_proc("glGetVertexAttribPointerv", 16, err, err_is);
	opengl[0].glUseProgram              = get_proc("glUseProgram",              16, err, err_is);
	opengl[0].glDeleteVertexArrays      = get_proc("glDeleteVertexArrays",      16, err, err_is);
	opengl[0].glDeleteBuffers           = get_proc("glDeleteBuffers",           16, err, err_is);
	opengl[0].glDeleteProgram           = get_proc("glDeleteProgram",           16, err, err_is);
	opengl[0].glDeleteShader            = get_proc("glDeleteShader",            16, err, err_is);
	opengl[0].glGetUniformLocation      = get_proc("glGetUniformLocation",      16, err, err_is);
	opengl[0].glUniformMatrix3fv        = get_proc("glUniformMatrix3fv",        16, err, err_is);
	opengl[0].glUniformMatrix4fv        = get_proc("glUniformMatrix4fv",        16, err, err_is);
	opengl[0].glUniformMatrix2x3fv      = get_proc("glUniformMatrix2x3fv",      16, err, err_is);
	opengl[0].glGenerateMipmap          = get_proc("glGenerateMipmap",          16, err, err_is);
	opengl[0].glActiveTexture           = get_proc("glActiveTexture",           16, err, err_is);
}

void win32ogl_error(win32ogl_error_t *const err, int *const err_type, int *const err_num, win32ogl_ul_t *const err_win32, win32ogl_lpcstr *const err_str) {
	err_type[0] = err[0].type;
	err_num[0] = err[0].num;
	err_win32[0] = err[0].win32;
	err_str[0] = err[0].str;
}

void win32ogl_instance(void **const data, win32ogl_error_t *const err, int *const err_is) {
	data[0] = (void*)GetModuleHandle(NULL);
	if (!data[0])
		error_set(err, err_is, 0, 1, GetLastError(), NULL);
}

void win32ogl_opengl(win32ogl_opengl_t *const opengl, win32ogl_error_t *const err, int *const err_is) {
	wgl_functions_init(opengl, err, err_is);
	ogl_functions_init(opengl, err, err_is);
}

void win32ogl_dummy_init(void **const data, void *const instance, win32ogl_error_t *const err, int *const err_is) {
	window_t *const dummy = (window_t*)malloc(sizeof(window_t));
	if (dummy) {
		ZeroMemory((void*)dummy, sizeof(window_t));
		dummy_class_init(dummy, (HINSTANCE)instance, err, err_is);
		dummy_window_create(dummy, err, err_is);
		dummy_context_init(dummy, err, err_is);
		if (err_is[0] == 0)
			data[0] = (void*)dummy;
		else
			dummy_destroy(dummy, err, err_is);
	} else {
		error_set(err, err_is, 0, 14, 0, NULL);
	}
}

void win32ogl_dummy_destroy(void *const data, win32ogl_error_t *const err, int *const err_is) {
	dummy_destroy((window_t*)data, err, err_is);
}

void win32ogl_context(void *const data, void **const dc, void **const rc) {
	window_t *const dummy = (window_t*)data;
	dc[0] = (void*)dummy[0].ctx.dc;
	rc[0] = (void*)dummy[0].ctx.rc;
}

void win32ogl_context_make_current(void *const dc, void *const rc, win32ogl_error_t *const err, int *const err_is) {
	if (!wglMakeCurrent((HDC)dc, (HGLRC)rc))
		error_set(err, err_is, 0, 8, GetLastError(), NULL);
}

void win32ogl_context_release(void *const rc, win32ogl_error_t *const err, int *const err_is) {
	if ((HGLRC)rc == wglGetCurrentContext() && !wglMakeCurrent(NULL, NULL))
		error_set(err, err_is, 0, 9, GetLastError(), NULL);
}

void win32ogl_context_swap_buffers(void *const dc, win32ogl_error_t *const err, int *const err_is) {
	if (!SwapBuffers((HDC)dc))
		error_set(err, err_is, 0, 13, GetLastError(), NULL);
}
