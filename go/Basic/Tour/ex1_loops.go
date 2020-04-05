/*
   https://tour.golang.org/flowcontrol/8

   "If you are interested in the details of the algorithm, the z² − x above
    is how far away z² is from where it needs to be (x), and the division by 2z
    is the derivative of z², to scale how much we adjust z by how quickly z²
    is changing. This general approach is called Newton's method."
*/
package main

import (
	"fmt"
	"math"
)

func Sqrt(x float64) float64 {
	sqrt := 1.0 // Not 0: it will be used as denominator
	for ; math.Abs(sqrt*sqrt-x) >= 0.001; sqrt -= (sqrt*sqrt - x) / (2 * sqrt) {
	}
	return sqrt
}

func main() {
	fmt.Println(2, Sqrt(2))
	fmt.Println(1, Sqrt(1))
	fmt.Println(16, Sqrt(16))
    fmt.Println(7, Sqrt(7))
    fmt.Println(8, Sqrt(8))
    fmt.Println(9, Sqrt(9))
}
