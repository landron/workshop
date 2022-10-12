/*
	Purpose: Equivalent Binary Trees
	https://tour.golang.org/concurrency/8

	"constructs a randomly-structured (but always sorted) binary tree"
		this condition is ignored by this implementation

		This is the "simplified" version of the unsorted one, which works in any condition.
*/
package main

import (
	"fmt"

	"golang.org/x/tour/tree"
)

// Walk walks the tree t sending all values
// from the tree to the channel ch.
/*
	This is horrible, but it works: the binary tree is always sorted!
*/
func Walk(t *tree.Tree, ch chan int) {
	var Walk_rec func(t *tree.Tree, ch chan int)

	Walk_rec = func(t *tree.Tree, ch chan int) {
		left, right := -1, -1
		if t.Left != nil {
			left = t.Left.Value
		}
		if t.Right != nil {
			right = t.Right.Value
		}

		if t.Value < left {
			if left < right {
				ch <- t.Value
				Walk_rec(t.Left, ch)
				Walk_rec(t.Right, ch)
			} else {
				if t.Value < right {
					ch <- t.Value
					Walk_rec(t.Right, ch)
					Walk_rec(t.Left, ch)
				} else {
					if t.Right != nil {
						Walk_rec(t.Right, ch)
					}
					ch <- t.Value
					Walk_rec(t.Left, ch)
				}
			}
		} else {
			if t.Value < right {
				if t.Left != nil {
					Walk_rec(t.Left, ch)
				}
				ch <- t.Value
				Walk_rec(t.Right, ch)
			} else {
				if left < right {
					if t.Left != nil {
						Walk_rec(t.Left, ch)
					}
					Walk_rec(t.Right, ch)
					ch <- t.Value
				} else {
					if t.Right != nil {
						Walk_rec(t.Right, ch)
					}
					if t.Left != nil {
						Walk_rec(t.Left, ch)
					}
					ch <- t.Value
				}
			}
		}
	}
	Walk_rec(t, ch)

	// only the sender can do it
	close(ch)
}

func Print(t *tree.Tree) {
	ch := make(chan int)
	go Walk(t, ch)
	first := true
	for i := range ch {
		if !first {
			fmt.Printf(", ")
		}
		first = false
		fmt.Printf("%v", i)
	}
	fmt.Println()
}

// Same determines whether the trees
// t1 and t2 contain the same values.
/*
	The Walk cannot be interrupted: it would block in channel sending.
*/
func Same(t1, t2 *tree.Tree) bool {
	ch1 := make(chan int)
	go Walk(t1, ch1)
	ch2 := make(chan int)
	go Walk(t2, ch2)
	result := true
	for i := range ch1 {
		j := <-ch2
		if i != j {
			//	cannot exit here, unfortunately
			result = false
		}
	}
	return result
}

func main() {
	Print(tree.New(1))
	Print(tree.New(3))
	fmt.Printf("Trees must be the same: %v!\n", Same(tree.New(1), tree.New(1)))
	fmt.Printf("Trees must be different: %v!\n", !Same(tree.New(2), tree.New(1)))
}
