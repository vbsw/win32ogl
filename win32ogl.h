#ifndef WIN32OGL_H
#define WIN32OGL_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	void *wglChoosePixelFormatARB;
	void *wglCreateContextAttribsARB;
	void *wglSwapIntervalEXT;
	void *wglGetSwapIntervalEXT;
	void *glCreateShader;
	void *glShaderSource;
	void *glCompileShader;
	void *glGetShaderiv;
	void *glGetShaderInfoLog;
	void *glCreateProgram;
	void *glAttachShader;
	void *glLinkProgram;
	void *glValidateProgram;
	void *glGetProgramiv;
	void *glGetProgramInfoLog;
	void *glGenBuffers;
	void *glGenVertexArrays;
	void *glGetAttribLocation;
	void *glBindVertexArray;
	void *glEnableVertexAttribArray;
	void *glVertexAttribPointer;
	void *glBindBuffer;
	void *glBufferData;
	void *glGetVertexAttribPointerv;
	void *glUseProgram;
	void *glDeleteVertexArrays;
	void *glDeleteBuffers;
	void *glDeleteProgram;
	void *glDeleteShader;
	void *glGetUniformLocation;
	void *glUniformMatrix4fv;
	void *glUniformMatrix3fv;
	void *glUniformMatrix2x3fv;
	void *glGenerateMipmap;
	void *glActiveTexture;
} win32ogl_opengl_t;

typedef unsigned long win32ogl_ul_t;
typedef unsigned int win32ogl_ui_t;
typedef const char *win32ogl_lpcstr;
typedef struct { int type; int num; win32ogl_ul_t win32; win32ogl_lpcstr str; } win32ogl_error_t;
extern void win32ogl_error(win32ogl_error_t *err, int *err_type, int *err_num, win32ogl_ul_t *err_win32, win32ogl_lpcstr *err_str);
extern void win32ogl_instance(void **data, win32ogl_error_t *err, int *err_is);
extern void win32ogl_opengl(win32ogl_opengl_t *opengl, win32ogl_error_t *err, int *err_is);
extern void win32ogl_dummy_init(void **data, void *instance, win32ogl_error_t *err, int *err_is);
extern void win32ogl_dummy_destroy(void *data, win32ogl_error_t *err, int *err_is);
extern void win32ogl_context(void *data, void **dc, void **rc);
extern void win32ogl_context_make_current(void *dc, void *rc, win32ogl_error_t *err, int *err_is);
extern void win32ogl_context_release(void *rc, win32ogl_error_t *err, int *err_is);
extern void win32ogl_context_swap_buffers(void *dc, win32ogl_error_t *err, int *err_is);

#ifdef __cplusplus
}
#endif

#endif /* WIN32OGL_H */