package main

import (
	"fmt"
	"math"
)

type ErrNegativeSqrt float64

func (e ErrNegativeSqrt) Error() string {
	return fmt.Sprint("cannot Sqrt negative number:", float64(e))
}

func Sqrt(x float64) (float64, error) {
	if x < 0 {
		return 0, ErrNegativeSqrt(x)
	}
	if x == 0 {
		return 0, nil
	}
	sqrt := 1.0 // Not 0: it will be used as denominator
	for ; math.Abs(sqrt*sqrt-x) >= 0.001; sqrt -= (sqrt*sqrt - x) / (2 * sqrt) {
	}
	return sqrt, nil
}

func PrintSqrt(x float64, e error) {
	if e != nil {
		fmt.Println(e)
	} else {
		fmt.Println(x)
	}
}

func main() {
	PrintSqrt(Sqrt(2))
	PrintSqrt(Sqrt(0.64))
	PrintSqrt(Sqrt(0))
	PrintSqrt(Sqrt(-2))
}
