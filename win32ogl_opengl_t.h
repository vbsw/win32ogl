// from wgl.h
#define WGL_SAMPLE_BUFFERS_ARB            0x2041
#define WGL_SAMPLES_ARB                   0x2042
#define WGL_DRAW_TO_WINDOW_ARB            0x2001
#define WGL_SWAP_METHOD_ARB               0x2007
#define WGL_SUPPORT_OPENGL_ARB            0x2010
#define WGL_DOUBLE_BUFFER_ARB             0x2011
#define WGL_PIXEL_TYPE_ARB                0x2013
#define WGL_TYPE_RGBA_ARB                 0x202B
#define WGL_ACCELERATION_ARB              0x2003
#define WGL_FULL_ACCELERATION_ARB         0x2027
#define WGL_SWAP_EXCHANGE_ARB             0x2028
#define WGL_SWAP_COPY_ARB                 0x2029
#define WGL_SWAP_UNDEFINED_ARB            0x202A
#define WGL_COLOR_BITS_ARB                0x2014
#define WGL_ALPHA_BITS_ARB                0x201B
#define WGL_DEPTH_BITS_ARB                0x2022
#define WGL_STENCIL_BITS_ARB              0x2023
#define WGL_CONTEXT_MAJOR_VERSION_ARB     0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB     0x2092
#define WGL_CONTEXT_PROFILE_MASK_ARB      0x9126
#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB  0x00000001

#define WGL_SWAP_METHOD_EXT               0x2007
#define WGL_SWAP_EXCHANGE_EXT             0x2028
#define WGL_SWAP_COPY_EXT                 0x2029
#define WGL_SWAP_UNDEFINED_EXT            0x202A

/* from wglext.h */
typedef BOOL(WINAPI *PFNWGLCHOOSEPIXELFORMATARBPROC) (HDC hdc, const int *piAttribIList, const FLOAT *pfAttribFList, UINT nMaxFormats, int *piFormats, UINT *nNumFormats);
typedef HGLRC(WINAPI *PFNWGLCREATECONTEXTATTRIBSARBPROC) (HDC hDC, HGLRC hShareContext, const int *attribList);
typedef BOOL(WINAPI *PFNWGLSWAPINTERVALEXTPROC) (int interval);
typedef int (WINAPI *PFNWGLGETSWAPINTERVALEXTPROC) (void);

// from glcorearb.h
typedef char GLchar;
typedef ptrdiff_t GLsizeiptr;
typedef GLuint(APIENTRY *PFNGLCREATESHADERPROC) (GLenum type);
typedef void (APIENTRY *PFNGLSHADERSOURCEPROC) (GLuint shader, GLsizei count, const GLchar *const*string, const GLint *length);
typedef void (APIENTRY *PFNGLCOMPILESHADERPROC) (GLuint shader);
typedef void (APIENTRY *PFNGLGETSHADERIVPROC) (GLuint shader, GLenum pname, GLint *params);
typedef void (APIENTRY *PFNGLGETSHADERINFOLOGPROC) (GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
typedef GLuint(APIENTRY *PFNGLCREATEPROGRAMPROC) (void);
typedef void (APIENTRY *PFNGLATTACHSHADERPROC) (GLuint program, GLuint shader);
typedef void (APIENTRY *PFNGLLINKPROGRAMPROC) (GLuint program);
typedef void (APIENTRY *PFNGLVALIDATEPROGRAMPROC) (GLuint program);
typedef void (APIENTRY *PFNGLGETPROGRAMIVPROC) (GLuint program, GLenum pname, GLint *params);
typedef void (APIENTRY *PFNGLGETPROGRAMINFOLOGPROC) (GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
typedef void (APIENTRY *PFNGLGENBUFFERSPROC) (GLsizei n, GLuint *buffers);
typedef void (APIENTRY *PFNGLGENVERTEXARRAYSPROC) (GLsizei n, GLuint *arrays);
typedef GLint(APIENTRY *PFNGLGETATTRIBLOCATIONPROC) (GLuint program, const GLchar *name);
typedef void (APIENTRY *PFNGLBINDVERTEXARRAYPROC) (GLuint array);
typedef void (APIENTRY *PFNGLENABLEVERTEXATTRIBARRAYPROC) (GLuint index);
typedef void (APIENTRY *PFNGLVERTEXATTRIBPOINTERPROC) (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer);
typedef void (APIENTRY *PFNGLBINDBUFFERPROC) (GLenum target, GLuint buffer);
typedef void (APIENTRY *PFNGLBUFFERDATAPROC) (GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage);
typedef void (APIENTRY *PFNGLGETVERTEXATTRIBPOINTERVPROC) (GLuint index, GLenum pname, GLvoid **pointer);
typedef void (APIENTRY *PFNGLUSEPROGRAMPROC) (GLuint program);
typedef void (APIENTRY *PFNGLDELETEVERTEXARRAYSPROC) (GLsizei n, const GLuint *arrays);
typedef void (APIENTRY *PFNGLDELETEBUFFERSPROC) (GLsizei n, const GLuint *buffers);
typedef void (APIENTRY *PFNGLDELETEPROGRAMPROC) (GLuint program);
typedef void (APIENTRY *PFNGLDELETESHADERPROC) (GLuint shader);
typedef GLint(APIENTRY *PFNGLGETUNIFORMLOCATIONPROC) (GLuint program, const GLchar *name);
typedef void (APIENTRY *PFNGLUNIFORMMATRIX4FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRY *PFNGLUNIFORMMATRIX3FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRY *PFNGLUNIFORMMATRIX2X3FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRY *PFNGLACTIVETEXTUREPROC) (GLenum texture);
typedef void (APIENTRY *PFNGLGENERATEMIPMAPPROC) (GLenum target);

#if defined(WIN32OGL_OPENGL_FUNCS)
static PFNWGLCHOOSEPIXELFORMATARBPROC    wglChoosePixelFormatARB    = NULL;
static PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = NULL;
static PFNWGLSWAPINTERVALEXTPROC         wglSwapIntervalEXT         = NULL;
static PFNWGLGETSWAPINTERVALEXTPROC      wglGetSwapIntervalEXT      = NULL;

static PFNGLCREATESHADERPROC             glCreateShader             = NULL;
static PFNGLSHADERSOURCEPROC             glShaderSource             = NULL;
static PFNGLCOMPILESHADERPROC            glCompileShader            = NULL;
static PFNGLGETSHADERIVPROC              glGetShaderiv              = NULL;
static PFNGLGETSHADERINFOLOGPROC         glGetShaderInfoLog         = NULL;
static PFNGLCREATEPROGRAMPROC            glCreateProgram            = NULL;
static PFNGLATTACHSHADERPROC             glAttachShader             = NULL;
static PFNGLLINKPROGRAMPROC              glLinkProgram              = NULL;
static PFNGLVALIDATEPROGRAMPROC          glValidateProgram          = NULL;
static PFNGLGETPROGRAMIVPROC             glGetProgramiv             = NULL;
static PFNGLGETPROGRAMINFOLOGPROC        glGetProgramInfoLog        = NULL;
static PFNGLGENBUFFERSPROC               glGenBuffers               = NULL;
static PFNGLGENVERTEXARRAYSPROC          glGenVertexArrays          = NULL;
static PFNGLGETATTRIBLOCATIONPROC        glGetAttribLocation        = NULL;
static PFNGLBINDVERTEXARRAYPROC          glBindVertexArray          = NULL;
static PFNGLENABLEVERTEXATTRIBARRAYPROC  glEnableVertexAttribArray  = NULL;
static PFNGLVERTEXATTRIBPOINTERPROC      glVertexAttribPointer      = NULL;
static PFNGLBINDBUFFERPROC               glBindBuffer               = NULL;
static PFNGLBUFFERDATAPROC               glBufferData               = NULL;
static PFNGLGETVERTEXATTRIBPOINTERVPROC  glGetVertexAttribPointerv  = NULL;
static PFNGLUSEPROGRAMPROC               glUseProgram               = NULL;
static PFNGLDELETEVERTEXARRAYSPROC       glDeleteVertexArrays       = NULL;
static PFNGLDELETEBUFFERSPROC            glDeleteBuffers            = NULL;
static PFNGLDELETEPROGRAMPROC            glDeleteProgram            = NULL;
static PFNGLDELETESHADERPROC             glDeleteShader             = NULL;
static PFNGLGETUNIFORMLOCATIONPROC       glGetUniformLocation       = NULL;
static PFNGLUNIFORMMATRIX4FVPROC         glUniformMatrix4fv         = NULL;
static PFNGLUNIFORMMATRIX3FVPROC         glUniformMatrix3fv         = NULL;
static PFNGLUNIFORMMATRIX2X3FVPROC       glUniformMatrix2x3fv       = NULL;
static PFNGLGENERATEMIPMAPPROC           glGenerateMipmap           = NULL;
static PFNGLACTIVETEXTUREPROC            glActiveTexture            = NULL;

void win32ogl_funcs_set(win32ogl_opengl_t *const opengl) {
	PFNWGLCHOOSEPIXELFORMATARBPROC    wglChoosePixelFormatARB    = (PFNWGLCHOOSEPIXELFORMATARBPROC)    opengl[0].wglChoosePixelFormatARB;
	PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC) opengl[0].wglCreateContextAttribsARB;
	PFNWGLSWAPINTERVALEXTPROC         wglSwapIntervalEXT         = (PFNWGLSWAPINTERVALEXTPROC)         opengl[0].wglSwapIntervalEXT;
	PFNWGLGETSWAPINTERVALEXTPROC      wglGetSwapIntervalEXT      = (PFNWGLGETSWAPINTERVALEXTPROC)      opengl[0].wglGetSwapIntervalEXT;

	PFNGLCREATESHADERPROC             glCreateShader             = (PFNGLCREATESHADERPROC)             opengl[0].glCreateShader;
	PFNGLSHADERSOURCEPROC             glShaderSource             = (PFNGLSHADERSOURCEPROC)             opengl[0].glShaderSource;
	PFNGLCOMPILESHADERPROC            glCompileShader            = (PFNGLCOMPILESHADERPROC)            opengl[0].glCompileShader;
	PFNGLGETSHADERIVPROC              glGetShaderiv              = (PFNGLGETSHADERIVPROC)              opengl[0].glGetShaderiv;
	PFNGLGETSHADERINFOLOGPROC         glGetShaderInfoLog         = (PFNGLGETSHADERINFOLOGPROC)         opengl[0].glGetShaderInfoLog;
	PFNGLCREATEPROGRAMPROC            glCreateProgram            = (PFNGLCREATEPROGRAMPROC)            opengl[0].glCreateProgram;
	PFNGLATTACHSHADERPROC             glAttachShader             = (PFNGLATTACHSHADERPROC)             opengl[0].glAttachShader;
	PFNGLLINKPROGRAMPROC              glLinkProgram              = (PFNGLLINKPROGRAMPROC)              opengl[0].glLinkProgram;
	PFNGLVALIDATEPROGRAMPROC          glValidateProgram          = (PFNGLVALIDATEPROGRAMPROC)          opengl[0].glValidateProgram;
	PFNGLGETPROGRAMIVPROC             glGetProgramiv             = (PFNGLGETPROGRAMIVPROC)             opengl[0].glGetProgramiv;
	PFNGLGETPROGRAMINFOLOGPROC        glGetProgramInfoLog        = (PFNGLGETPROGRAMINFOLOGPROC)        opengl[0].glGetProgramInfoLog;
	PFNGLGENBUFFERSPROC               glGenBuffers               = (PFNGLGENBUFFERSPROC)               opengl[0].glGenBuffers;
	PFNGLGENVERTEXARRAYSPROC          glGenVertexArrays          = (PFNGLGENVERTEXARRAYSPROC)          opengl[0].glGenVertexArrays;
	PFNGLGETATTRIBLOCATIONPROC        glGetAttribLocation        = (PFNGLGETATTRIBLOCATIONPROC)        opengl[0].glGetAttribLocation;
	PFNGLBINDVERTEXARRAYPROC          glBindVertexArray          = (PFNGLBINDVERTEXARRAYPROC)          opengl[0].glBindVertexArray;
	PFNGLENABLEVERTEXATTRIBARRAYPROC  glEnableVertexAttribArray  = (PFNGLENABLEVERTEXATTRIBARRAYPROC)  opengl[0].glEnableVertexAttribArray;
	PFNGLVERTEXATTRIBPOINTERPROC      glVertexAttribPointer      = (PFNGLVERTEXATTRIBPOINTERPROC)      opengl[0].glVertexAttribPointer;
	PFNGLBINDBUFFERPROC               glBindBuffer               = (PFNGLBINDBUFFERPROC)               opengl[0].glBindBuffer;
	PFNGLBUFFERDATAPROC               glBufferData               = (PFNGLBUFFERDATAPROC)               opengl[0].glBufferData;
	PFNGLGETVERTEXATTRIBPOINTERVPROC  glGetVertexAttribPointerv  = (PFNGLGETVERTEXATTRIBPOINTERVPROC)  opengl[0].glGetVertexAttribPointerv;
	PFNGLUSEPROGRAMPROC               glUseProgram               = (PFNGLUSEPROGRAMPROC)               opengl[0].glUseProgram;
	PFNGLDELETEVERTEXARRAYSPROC       glDeleteVertexArrays       = (PFNGLDELETEVERTEXARRAYSPROC)       opengl[0].glDeleteVertexArrays;
	PFNGLDELETEBUFFERSPROC            glDeleteBuffers            = (PFNGLDELETEBUFFERSPROC)            opengl[0].glDeleteBuffers;
	PFNGLDELETEPROGRAMPROC            glDeleteProgram            = (PFNGLDELETEPROGRAMPROC)            opengl[0].glDeleteProgram;
	PFNGLDELETESHADERPROC             glDeleteShader             = (PFNGLDELETESHADERPROC)             opengl[0].glDeleteShader;
	PFNGLGETUNIFORMLOCATIONPROC       glGetUniformLocation       = (PFNGLGETUNIFORMLOCATIONPROC)       opengl[0].glGetUniformLocation;
	PFNGLUNIFORMMATRIX4FVPROC         glUniformMatrix4fv         = (PFNGLUNIFORMMATRIX4FVPROC)         opengl[0].glUniformMatrix4fv;
	PFNGLUNIFORMMATRIX3FVPROC         glUniformMatrix3fv         = (PFNGLUNIFORMMATRIX3FVPROC)         opengl[0].glUniformMatrix3fv;
	PFNGLUNIFORMMATRIX2X3FVPROC       glUniformMatrix2x3fv       = (PFNGLUNIFORMMATRIX2X3FVPROC)       opengl[0].glUniformMatrix2x3fv;
	PFNGLGENERATEMIPMAPPROC           glGenerateMipmap           = (PFNGLGENERATEMIPMAPPROC)           opengl[0].glGenerateMipmap;
	PFNGLACTIVETEXTUREPROC            glActiveTexture            = (PFNGLACTIVETEXTUREPROC)            opengl[0].glActiveTexture;
}
#endif
