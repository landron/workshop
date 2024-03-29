/*
	Purpose: https://go.dev/tour/generics/2
*/
package main

import (
	"fmt"
	"sort"

	"golang.org/x/exp/constraints"
)

// List represents a singly-linked list that holds
// values of any type.
// comparable: delete by val, sort
// type Interface any
// type Interface comparable
type Interface interface {
	comparable
	//sort.Interface
	constraints.Ordered
}

type List[T Interface] struct {
	next *List[T]
	val  T
}

func NewList[T Interface](s []T) *List[T] {
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
	for next := list; next != nil; next = next.next {
		if next != list {
			fmt.Printf(", ")
		}
		fmt.Printf("%v", next.val)
	}
	fmt.Println()
}

func (list *List[T]) Delete(val T) *List[T] {
	next := list
	var prev *List[T]
	for next != nil {
		if next.val == val {
			if prev == nil {
				//prev = list
				list = list.next
			} else {
				prev.next = next.next
			}
			break
		}
		prev, next = next, next.next
	}
	return list
}

func (list *List[T]) Append(val T) *List[T] {
	var prev *List[T]
	for next := list; next != nil; next = next.next {
		prev = next
	}
	to_add := new(List[T])
	to_add.val = val
	if prev == nil {
		list = to_add
	} else {
		prev.next = to_add
	}
	return list
}

func (list *List[T]) Slice() []T {
	sl := make([]T, 0)
	for next := list; next != nil; next = next.next {
		sl = append(sl, next.val)
	}
	return sl
}

/*
	https://gosamples.dev/generics-sort-slice/
*/
func sortSlice[T constraints.Ordered](s []T) {
	sort.Slice(s, func(i, j int) bool {
		return s[i] < s[j]
	})
}

func (list *List[T]) Sort() {
	sl := list.Slice()
	// sl.Sort()
	sortSlice(sl)
	i := 0
	for next := list; next != nil; next = next.next {
		next.val = sl[i]
		i++
	}
}

func main() {
	l1 := NewList([]string{"foo", "bar", "baz", "nin"})
	l1.Print()
	l1 = l1.Delete("baz")
	l1.Print()
	l1 = l1.Delete("nin")
	l1.Print()
	fmt.Println(l1.Slice())
	l1 = l1.Append("bin")
	l1 = l1.Append("kal")
	l1.Print()
	l1.Append("cope")
	l1.Sort()
	l1.Print()
}
