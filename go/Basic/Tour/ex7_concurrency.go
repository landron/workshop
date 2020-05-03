/*
	Exercise: Web Crawler
	https://tour.golang.org/concurrency/10

	https://stackoverflow.com/questions/18207772/how-to-wait-for-all-goroutines-to-finish-without-using-time-sleep
		use sync.WaitGroup
*/
package main

import (
	"fmt"
	"sync"
)

type Fetcher interface {
	// Fetch returns the body of URL and
	// a slice of URLs found on that page.
	Fetch(url string) (body string, urls []string, err error)
}

/*
	Cache of seen values
	(even those that cannot be solved)
*/
type Cache struct {
	// no need for values (now)
	v   map[string]struct{}
	mux sync.Mutex
}

func (c *Cache) Add(key string) bool {
	c.mux.Lock()
	// Lock so only one goroutine at a time can access the map c.v.
	defer c.mux.Unlock()
	_, ok := c.v[key]
	if ok {
		fmt.Println("-- Hit:", key)
		return false
	}
	c.v[key] = struct{}{}
	return true
}

// Crawl uses fetcher to recursively crawl
// pages starting with url, to a maximum of depth.
func Crawl_rec(url string, depth int, fetcher Fetcher,
	cache Cache, quit_parent chan struct{}) {
	defer func(quit chan struct{}) {
		quit <- struct{}{}
	}(quit_parent)

	if depth <= 0 {
		return
	}
	if !cache.Add(url) {
		return
	}
	body, urls, err := fetcher.Fetch(url)
	if err != nil {
		fmt.Println(err)
		return
	}
	fmt.Printf("found: %s %q\n", url, body)
	quit_children := make(chan struct{})
	for _, u := range urls {
		go Crawl_rec(u, depth-1, fetcher, cache, quit_children)
	}
	for i := 0; i < len(urls); i++ {
		<-quit_children
	}
}

func Crawl_conc(url string, depth int, fetcher Fetcher) {
	cache := Cache{v: make(map[string]struct{})}
	quit := make(chan struct{})
	go Crawl_rec(url, depth, fetcher, cache, quit)
	<-quit
}

func main() {
	//Crawl("https://golang.org/", 4, fetcher)
	Crawl_conc("https://golang.org/", 4, fetcher)
}

// fakeFetcher is Fetcher that returns canned results.
type fakeFetcher map[string]*fakeResult

type fakeResult struct {
	body string
	urls []string
}

func (f fakeFetcher) Fetch(url string) (string, []string, error) {
	if res, ok := f[url]; ok {
		return res.body, res.urls, nil
	}
	return "", nil, fmt.Errorf("not found: %s", url)
}

// fetcher is a populated fakeFetcher.
var fetcher = fakeFetcher{
	"https://golang.org/": &fakeResult{
		"The Go Programming Language",
		[]string{
			"https://golang.org/pkg/",
			"https://golang.org/cmd/",
		},
	},
	"https://golang.org/pkg/": &fakeResult{
		"Packages",
		[]string{
			"https://golang.org/",
			"https://golang.org/cmd/",
			"https://golang.org/pkg/fmt/",
			"https://golang.org/pkg/os/",
		},
	},
	"https://golang.org/pkg/fmt/": &fakeResult{
		"Package fmt",
		[]string{
			"https://golang.org/",
			"https://golang.org/pkg/",
		},
	},
	"https://golang.org/pkg/os/": &fakeResult{
		"Package os",
		[]string{
			"https://golang.org/",
			"https://golang.org/pkg/",
		},
	},
}
