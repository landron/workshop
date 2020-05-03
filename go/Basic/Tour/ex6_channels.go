/*
	Exercise: Equivalent Binary Trees
	https://tour.golang.org/concurrency/8
*/
package main

//	fmt wants alphabetical order
import (
	"fmt"
	"golang.org/x/tour/tree"
	"reflect"
	"sort"
)

func Walk_rec(t *tree.Tree, ch chan int) {
	if t.Left != nil {
		Walk_rec(t.Left, ch)
	}
	if t.Right != nil {
		Walk_rec(t.Right, ch)
	}
	ch <- t.Value
}

// Walk walks the tree t sending all values
// from the tree to the channel ch.
func Walk(t *tree.Tree, ch chan int) {
	Walk_rec(t, ch)
	close(ch)
}

func get_tree_values(t *tree.Tree) []int {
	var s []int
	ch := make(chan int)
	go Walk(t, ch)
	for i := range ch {
		//fmt.Println(i)
		s = append(s, i)
	}
	sort.Ints(s)
	return s
}

// Same determines whether the trees
// t1 and t2 contain the same values.
func Same(t1, t2 *tree.Tree) bool {
	s1 := get_tree_values(t1)
	s2 := get_tree_values(t2)
	return reflect.DeepEqual(s1, s2)
}

func main() {
	s := get_tree_values(tree.New(1))
	fmt.Println(s)
	fmt.Printf("Trees must be the same: %v!\n", Same(tree.New(1), tree.New(1)))
	fmt.Printf("Trees must be different: %v!\n", !Same(tree.New(2), tree.New(1)))
}
