package main

import (
	"fmt"
	"runtime"
	"unsafe"
)

/*
#cgo linux LDFLAGS: -Wl,--export-dynamic -Wl,--unresolved-symbols=ignore-in-object-files
#cgo darwin LDFLAGS: -Wl,-undefined,dynamic_lookup
#cgo CFLAGS: -DNVML_NO_UNVERSIONED_FUNC_DEFS=1
#include <dlfcn.h>
#include <stdlib.h>
#include <test.h>
*/
import "C"

const (
	RTLD_LAZY     = C.RTLD_LAZY
	RTLD_NOW      = C.RTLD_NOW
	RTLD_GLOBAL   = C.RTLD_GLOBAL
	RTLD_LOCAL    = C.RTLD_LOCAL
	RTLD_NODELETE = C.RTLD_NODELETE
	RTLD_NOLOAD   = C.RTLD_NOLOAD
)

const (
	defaultLibraryLoadFlags = RTLD_LAZY
)

var (
	_handle unsafe.Pointer
)

func main() {
	{
		err := Open("./test2.so")
		if err != nil {
			panic(err.Error())
		}

		err = Lookup("add")
		if err != nil {
			fmt.Printf("add: %s\n", err.Error())
		}

		r := C_Add(1, 2)
		fmt.Printf("C return: %v, lib: %s\n", r, "test2.so")
		Close()
	}

	// {
	// 	err := Open("./test1.so")
	// 	if err != nil {
	// 		panic(err.Error())
	// 	}

	// 	r := C_Add(1, 2)
	// 	fmt.Printf("C return: %v, lib: %s\n", r, "test2.so")
	// 	Close()
	// }
}

func withOSLock(action func() error) error {
	runtime.LockOSThread()
	defer runtime.UnlockOSThread()

	return action()
}

type Return int32

var cgoAllocsUnknown = new(struct{})

func C_Add(a, b uint32) Return {
	cA := (C.int)(a)
	cB := (C.int)(b)

	__ret := C.add(cA, cB)
	__v := (Return)(__ret)
	return __v
}
