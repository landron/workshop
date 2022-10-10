/*
	Purpose:	implement rot13 reader
*/
package main

import (
	//"errors"
	"fmt"
	"io"
	"os"
	"strings"
)

type rot13Reader struct {
	r io.Reader
}

func (src *rot13Reader) Read(b []byte) (n int, err error) {
	// return 0, errors.New("Not implemented")
	n, err = src.r.Read(b)
	if err != nil {
		return -1, err
	}
	//fmt.Println(n, err, b)

	for i, v := range b {
		if v != ' ' {
			next := v - 13
			if v > 'a' {
				if v-13 < 'a' {
					next = 'z' - (12 - (v - 'a'))
				}
			} else {
				if v-13 < 'A' {
					next = 'Z' - (12 - (v - 'A'))
				}
			}
			b[i] = next
		}
	}

	return n, nil
}

func main() {
	s := strings.NewReader("Lbh penpxrq gur pbqr!")
	r := rot13Reader{s}
	io.Copy(os.Stdout, &r)
	fmt.Println()
}
