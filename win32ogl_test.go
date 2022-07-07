/*
 *          Copyright 2022, Vitali Baumtrok.
 * Distributed under the Boost Software License, Version 1.0.
 *     (See accompanying file LICENSE or copy at
 *        http://www.boost.org/LICENSE_1_0.txt)
 */

package win32ogl

import (
	"testing"
)

func TestDummy(t *testing.T) {
	instance, err := Instance()
	if err == nil {
		var dummy DummyWindow
		err = dummy.Init(instance)
		if err == nil {
			err = dummy.Context.MakeCurrent()
			if err == nil {
				var ogl OpenGL
				err = ogl.LoadFunctions()
				if err != nil {
					t.Error(err.Error())
				}
				err = dummy.Context.Release()
			}
			if err != nil {
				t.Error(err.Error())
			}
			err = dummy.Destroy()
		}
	}
	if err != nil {
		t.Error(err.Error())
	}
	if instance == nil {
		t.Error("instance is nil")
	}
}
