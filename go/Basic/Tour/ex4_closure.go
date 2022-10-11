/*
	https://tour.golang.org/moretypes/26
*/
package main

import "fmt"

// fibonacci is a function that returns
// a function that returns an int.
func fibonacci1() func() int {
	x, y := -1, -1
	return func() int {
		if x == -1 {
			if y == -1 {
				y = 1
				return 0
			} else {
				x = 0
				return 1
			}
		}
		x, y = y, x+y
		return y
	}
}

func fibonacci2() func() int {
	x, y := -1, 1
	return func() int {
		x, y = y, x+y
		return y
	}
}

func fibonacci3() func() int {
	x, y := 0, 1
	return func() int {
		next := x
		x, y = y, x+y
		return next
	}
}

func fibonacci() func() int {
	return fibonacci3()
}

func main() {
	f := fibonacci()
	for i := 0; i < 10; i++ {
		fmt.Println(f())
	}
}
