/*
 *          Copyright 2022, Vitali Baumtrok.
 * Distributed under the Boost Software License, Version 1.0.
 *     (See accompanying file LICENSE or copy at
 *        http://www.boost.org/LICENSE_1_0.txt)
 */

// Package win32ogl provides funtions for OpenGL applications for windows.
package win32ogl

// #cgo CFLAGS: -DUNICODE
// #cgo LDFLAGS: -luser32 -lgdi32 -lOpenGL32
// #include "win32ogl.h"
import "C"
import (
	"errors"
	"fmt"
	"strconv"
	"unsafe"
)

// Context is the OpenGL context.
type Context struct {
	Dc unsafe.Pointer
	Rc unsafe.Pointer
}

// DummyWindow is a window with OpenGL 1.1 context.
type DummyWindow struct {
	data    unsafe.Pointer
	Context Context
}

// OpenGL holds OpenGL functions.
type OpenGL struct {
	Funcs *C.win32ogl_opengl_t
	data  C.win32ogl_opengl_t
}

type Updatable interface {
	Update()
}

// MainLoop processes window events.
type MainLoop struct {
	count  int
	upds   []Updatable
	unused []int
}

// AddUpdatable adds an Updatable to main loop. Updatable is called, when event queue has no events.
func (loop *MainLoop) AddUpdatable(upd Updatable) int {
	if len(loop.unused) == 0 {
		loop.upds = append(loop.upds, upd)
		return len(loop.upds) - 1
	}
	indexLast := len(loop.unused) - 1
	indexObj := loop.unused[indexLast]
	loop.unused = loop.unused[:indexLast]
	loop.upds[indexObj] = upd
	loop.count++
	return indexObj
}

// RemoveUpdatable makes Updatable no more identified by id.
func (loop *MainLoop) RemoveUpdatable(id int) {
	loop.upds[id] = nil
	loop.unused = append(loop.unused, id)
	loop.count--
}

// RemoveAllUpdatable removes all Updatable.
func (loop *MainLoop) RemoveAllUpdatable() {
	if loop.count > 0 {
		for i := 0; i < len(loop.upds) && loop.upds[i] != nil; i++ {
			loop.RemoveUpdatable(i)
		}
	}
}

// ProcessEvents processes events and blocks until
func (loop *MainLoop) ProcessEvents() {
	
}

// Instance returns HINSTANCE. HINSTANCE is the instance handle of this executable.
func Instance() (unsafe.Pointer, error) {
	var instance unsafe.Pointer
	var errC C.win32ogl_error_t
	var errIsC C.int
	C.win32ogl_instance(&instance, &errC, &errIsC)
	if errIsC == 0 {
		return instance, nil
	}
	return instance, toError(errC)
}

// Init initializes dummy window and its OpenGL context. Parameter instance is the instance handle of this executable.
func (dummy *DummyWindow) Init(instance unsafe.Pointer) error {
	var errC C.win32ogl_error_t
	var errIsC C.int
	C.win32ogl_dummy_init(&dummy.data, instance, &errC, &errIsC)
	if errIsC == 0 {
		C.win32ogl_context(dummy.data, &dummy.Context.Dc, &dummy.Context.Rc)
		return nil
	}
	return toError(errC)
}

// Destroy releases all resources associated with dummy window.
func (dummy *DummyWindow) Destroy() error {
	var errC C.win32ogl_error_t
	var errIsC C.int
	if dummy.data != nil {
		C.win32ogl_dummy_destroy(dummy.data, &errC, &errIsC)
		dummy.data = nil
	}
	if errIsC == 0 {
		return nil
	}
	return toError(errC)
}

// MakeCurrent makes OpenGL context current.
func (ctx *Context) MakeCurrent() error {
	var errC C.win32ogl_error_t
	var errIsC C.int
	C.win32ogl_context_make_current(ctx.Dc, ctx.Rc, &errC, &errIsC)
	if errIsC == 0 {
		return nil
	}
	return toError(errC)
}

// Release makes OpenGL context no longer current.
// If any other context is current, it stays current.
func (ctx *Context) Release() error {
	var errC C.win32ogl_error_t
	var errIsC C.int
	C.win32ogl_context_release(ctx.Rc, &errC, &errIsC)
	if errIsC == 0 {
		return nil
	}
	return toError(errC)
}

// SwapBuffers swaps the front and back buffers.
func (ctx *Context) SwapBuffers() error {
	var errC C.win32ogl_error_t
	var errIsC C.int
	C.win32ogl_context_swap_buffers(ctx.Dc, &errC, &errIsC)
	if errIsC == 0 {
		return nil
	}
	return toError(errC)
}

// LoadFunctions loads OpenGL functions. An OpenGL context must have been set current before.
func (opengl *OpenGL) LoadFunctions() error {
	var errC C.win32ogl_error_t
	var errIsC C.int
	C.win32ogl_opengl(&opengl.data, &errC, &errIsC)
	if errIsC == 0 {
		opengl.Funcs = &opengl.data
		return nil
	}
	return toError(errC)
}

func toError(errC C.win32ogl_error_t) error {
	var errTypeC C.int
	var errNumC C.int
	var errWin32 C.win32ogl_ul_t
	var errStrC C.win32ogl_lpcstr
	var errStr string
	C.win32ogl_error(&errC, &errTypeC, &errNumC, &errWin32, &errStrC)
	switch errNumC {
	case 1:
		errStr = "get instance handle failed"
	case 2:
		errStr = "register dummy class failed"
	case 3:
		errStr = "create dummy window failed"
	case 4:
		errStr = "get dummy device context failed"
	case 5:
		errStr = "choose dummy pixel format failed"
	case 6:
		errStr = "set dummy pixel format failed"
	case 7:
		errStr = "create dummy render context failed"
	case 8:
		errStr = "make dummy context current failed"
	case 9:
		errStr = "release dummy context failed"
	case 10:
		errStr = "delete dummy render context failed"
	case 11:
		errStr = "destroy dummy window failed"
	case 12:
		errStr = "unregister dummy class failed"
	case 13:
		errStr = "swap dummy buffer failed"
	case 14:
		errStr = "memory allocation failed"
	case 15:
		errStr = "load wgl function failed"
	case 16:
		errStr = "load OpenGL function failed"
	}
	errStr = errStr + " (" + strconv.FormatUint(uint64(errNumC), 10)
	if errWin32 == 0 {
		errStr = errStr + ")"
	} else {
		errStr = errStr + ", " + strconv.FormatUint(uint64(errWin32), 10) + ")"
	}
	if errStrC != nil {
		if errTypeC == 0 {
			errStr = errStr + "; " + C.GoString(errStrC)
		} else {
			errStr = errStr + ": " + C.GoString(errStrC)
		}
	}
	return errors.New(errStr)
}

//export goDebug
func goDebug(a, b C.int, c, d C.win32ogl_ul_t) {
	fmt.Println(a, b, c, d)
}
