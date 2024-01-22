package main

import (
	"errors"
	"fmt"
	"unsafe"
)

// #cgo LDFLAGS: -ldl
// #include <dlfcn.h>
// #include <stdlib.h>
import "C"

func Open(libName string) error {
	name := C.CString(libName)
	defer C.free(unsafe.Pointer(name))

	if err := withOSLock(func() error {
		handle := C.dlopen(name, C.int(defaultLibraryLoadFlags))
		if handle == nil {
			return dlError()
		}
		_handle = handle
		return nil
	}); err != nil {
		return err
	}
	return nil
}

func Lookup(symbol string) error {
	sym := C.CString(symbol)
	defer C.free(unsafe.Pointer(sym))

	var pointer unsafe.Pointer
	if err := withOSLock(func() error {
		// Call dlError() to clear out any previous errors.
		_ = dlError()
		pointer = C.dlsym(_handle, sym)
		if pointer == nil {
			return fmt.Errorf("symbol %q not found: %w", symbol, dlError())
		}
		return nil
	}); err != nil {
		return err
	}
	return nil
}

func Close() error {
	if _handle == nil {
		return nil
	}
	if err := withOSLock(func() error {
		if C.dlclose(_handle) != 0 {
			return dlError()
		}
		_handle = nil
		return nil
	}); err != nil {
		return err
	}
	return nil
}

func dlError() error {
	lastErr := C.dlerror()
	if lastErr == nil {
		return nil
	}
	return errors.New(C.GoString(lastErr))
}
