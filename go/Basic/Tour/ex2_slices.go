/*
	https://tour.golang.org/moretypes/18

	> go get golang.org/x/tour/pic
	This works! Awesome!

	* a slice of slices
	* name return values can be used

	Troubleshooting
	ex2_slices.go:17:8: no required module provides package golang.org/x/tour/pic: go.mod file not found in current directory or any parent directory; see 'go help modules'
		=>
	go mod init main
	go mod tidy

	TODO: generate an image file !
		The image can be shown in the page's (tour) player.
		Not in terminals.
*/
package main

//import "fmt"
import "golang.org/x/tour/pic"

//	https://stackoverflow.com/questions/25459474/go-tour-slices-exercise-logic
func GeneratePixel_3(x, y int) uint8 {
	return uint8((x ^ y) * (x ^ y))
}

//	https://gist.github.com/tetsuok/2280162
func GeneratePixel_2(x, y int) uint8 {
	switch {
	case y%15 == 0:
		return 240
	case y%3 == 0:
		return 120
	case y%5 == 0:
		return 150
	default:
		return 100
	}
}

//	Interesting functions include (x+y)/2, x*y, and x^y.
func GeneratePixel_1(x, y int) uint8 {
	//return uint8((x+y)/2)
	//return uint8(x*y)
	return uint8(x ^ y)
}

func GeneratePixel(x, y int) uint8 {
	return GeneratePixel_3(x, y)
}

func Pic(dx, dy int) [][]uint8 {
	picture := make([][]uint8, dy)
	for i := range picture {
		picture[i] = make([]uint8, dx)
		for j := range picture[i] {
			picture[i][j] = GeneratePixel(i, j)
		}
	}
	//fmt.Println(picture)
	return picture
}

func main() {
	pic.Show(Pic)
}
