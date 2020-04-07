/*
   https://tour.golang.org/moretypes/23
*/
package main

import (
	"golang.org/x/tour/wc"
	"strings"
)

func WordCount(s string) map[string]int {
	count := make(map[string]int)
	for _, val := range strings.Fields(s) {
		now := count[val]
		count[val] = now + 1
	}
	return count
}

func main() {
	wc.Test(WordCount)
}
