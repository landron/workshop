// $ go install ex2_slices.go
// ex2_slices.go:17:8: no required module provides package golang.org/x/tour/pic: go.mod file not found in current directory or any parent directory; see 'go help modules'
//	=>
// go mod init main
// go mod tidy
//
// also commit go.sum
// TODO: why ? https://github.com/golang/go/wiki/Modules#should-i-commit-my-gosum-file-as-well-as-my-gomod-file
module main

go 1.18

require golang.org/x/tour v0.1.0
