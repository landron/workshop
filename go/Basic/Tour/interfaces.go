/*
	* unattached interface call => crash
	* empty interface
*/
package main

import "fmt"

type I interface {
	M()
}

type Impl struct {
	S string
}

func (t Impl) M() {
	fmt.Println(t.S)
}

func main() {
	var i I
	describe(i)

	// false => panic!
	if true {
		var t Impl
		t.S = "What a test!"
		i = t
		describe(i)
	}

	i.M()
}

func describe(i interface{}) {
	fmt.Printf("(%v, %T)\n", i, i)
}
