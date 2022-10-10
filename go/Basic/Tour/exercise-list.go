/*
	Purpose: https://go.dev/tour/generics/2

	WIP
*/
package main

import "fmt"

// List represents a singly-linked list that holds
// values of any type.
type List[T any] struct {
	next *List[T]
	val  T
}

func NewList[T any](s []T) *List[T] {
	var first, prev *List[T]
	for _, val := range s {
		next := new(List[T])
		next.val = val
		if first == nil {
			first = next
		}
		if prev != nil {
			prev.next = next
		}
		prev = next
	}
	return first
}

func (list *List[T]) Print() {
	next := list
	for next != nil {
		fmt.Println(next.val)
		next = next.next
	}
}

func main() {
	l1 := NewList([]string{"foo", "bar", "baz", "nin"})
	l1.Print()
}
