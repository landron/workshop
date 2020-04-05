/*
   This is my first go program
       go1.14.1 windows/amd64

   https://tour.golang.org/

   go help
   go fmt hello.go
   go build hello.go
   hello.exe
*/
package main

import (
	"fmt"
	"math/rand"
	"time"
)

/*
   Printf vs Println
*/
func main() {
	rand.Seed(time.Now().UTC().UnixNano())

	fmt.Printf("Hello, world!\n\t李宇 speaking ...\n")

	fmt.Println("The time is", time.Now())
	fmt.Println(1+rand.Intn(100), "is a random number.")

    python := "awesome!"  // not a const
    fmt.Println("How is python?", python)
}
