/*
   $ go version
   go version go1.18.5 linux/amd64

   https://go.dev/tour

   go help
   go fmt hello.go
   go build hello.go
   hello.exe

   instead of build:
   	go env -w GOBIN=/somewhere/else/bin
   	go install hello.go
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
	fmt.Printf("Current time is %v.\n", time.Now().Format(time.RFC850))
	fmt.Println(1+rand.Intn(100), "is a random number.")

	python := "awesome!" // not a const
	fmt.Println("How is python?", python)
}
