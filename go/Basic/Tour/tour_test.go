/*
	go test tour_test.go

	go test tour_test.go ex4_closure.go

	TODO:	move assert_b, expectEqual to some package
*/
package main

import (
	"fmt"
	"path"
	"runtime"
	"testing"
)

//	TODO: use some common library
//	#debug
func assert_b(err bool, msg string) {
	/*
		only to test things
			https://golang.org/doc/faq#assertions
	*/
	if !err {
		panic(fmt.Sprintf("fatal \"%s!\"", msg))
	}
}

/*
	see server_test.go
*/
func expectEqual(t *testing.T, expected interface{}, actual interface{}) {
	if expected != actual {
		_, file, line, _ := runtime.Caller(1)
		t.Fatalf("Expected '%v' to be '%v' but it wasn't. See '%s' at line %d.",
			actual, expected, path.Base(file), line)
	}
}

func TestFibonacci(t *testing.T) {
	f1 := fibonacci1()
	f2 := fibonacci2()
	f3 := fibonacci3()
	prev, curr := -1, 1
	for i := 0; i < 13; i++ {
		prev, curr = curr, prev+curr
		expectEqual(t, f1(), curr)
		expectEqual(t, f2(), curr)
		expectEqual(t, f3(), curr)
	}
}
