/*
	Exercise: Web Crawler
	https://tour.golang.org/concurrency/10

	https://stackoverflow.com/questions/18207772/how-to-wait-for-all-goroutines-to-finish-without-using-time-sleep
	https://stackoverflow.com/questions/13217547/tour-of-go-exercise-10-crawler
		using sync.WaitGroup seems the better solution

	TODO
		* add a command line paramater to switch between solutions
		* export some statistics to have some results assertions (4 found, 1 not found, 6 hits)
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
func Crawl_rec1(url string, depth int, fetcher Fetcher, cache Cache,
	quit_parent chan struct{}) {

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
		go Crawl_rec1(u, depth-1, fetcher, cache, quit_children)
	}
	for i := 0; i < len(urls); i++ {
		<-quit_children
	}
}

// Wait for work to finish: sync goroutines with channels (one for each goroutine)
func Crawl_solution1(url string, depth int, fetcher Fetcher) {
	quit := make(chan struct{})

	cache := Cache{v: make(map[string]struct{})}
	go Crawl_rec1(url, depth, fetcher, cache, quit)
	<-quit
}

// Crawl uses fetcher to recursively crawl
// pages starting with url, to a maximum of depth.
func Crawl_rec2(url string, depth int, fetcher Fetcher, cache Cache,
	work_done *sync.WaitGroup) {

	defer func(work *sync.WaitGroup) {
		work.Done()
	}(work_done)

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

	for _, u := range urls {
		work_done.Add(1)
		go Crawl_rec2(u, depth-1, fetcher, cache, work_done)
	}
}

// Wait for work to finish: sync.WaitGroup
/*
	Warnings:
		* WaitGroup must be pointer, otherwise it will create copies when
		calling functions and deadlock
		* Add must be called before calling the goroutine
			see comments: https://stackoverflow.com/a/18207832/1032277

	Other solutions/variants
		* each goroutine with its own WaitGroup => no arguments needed
		https://gist.github.com/danimal141/09ed828ce4d676faa6fa9f19aeea2867

	Reference
		https://stackoverflow.com/questions/18207772/how-to-wait-for-all-goroutines-to-finish-without-using-time-sleep
*/
func Crawl_solution2(url string, depth int, fetcher Fetcher) {
	// var quit sync.WaitGroup
	// quit := new(sync.WaitGroup)
	quit := &sync.WaitGroup{}

	cache := Cache{v: make(map[string]struct{})}
	quit.Add(1)
	go Crawl_rec2(url, depth, fetcher, cache, quit)
	quit.Wait()
}

// Crawl uses fetcher to recursively crawl
// pages starting with url, to a maximum of depth.
func Crawl3(url string, depth int, fetcher Fetcher, cache Cache) {
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

	var work_done sync.WaitGroup
	for _, u := range urls {
		work_done.Add(1)
		go func(u string) {
			defer work_done.Done()
			Crawl3(u, depth-1, fetcher, cache)
		}(u)
	}
	work_done.Wait()
}

/*
	like Crawl_solution2, but creating one sync.WaitGroup
	for each goroutine group creation
*/
func Crawl_solution3(url string, depth int, fetcher Fetcher) {
	cache := Cache{v: make(map[string]struct{})}
	Crawl3(url, depth, fetcher, cache)
}

//	Like Crawl_solution2, but keeping functions declarations (parameters)
//	from the exercise.
func Crawl4(url string, depth int, fetcher Fetcher) {
	cache := &Cache{v: make(map[string]struct{})}
	done := &sync.WaitGroup{}

	var worker func(url string, depth int, fetcher Fetcher,
		cache *Cache, done *sync.WaitGroup)

	worker = func(url string, depth int, fetcher Fetcher,
		cache *Cache, done *sync.WaitGroup) {
		defer done.Done()

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

		for _, u := range urls {
			done.Add(1)
			go worker(u, depth-1, fetcher, cache, done)
		}
	}

	done.Add(1)
	go worker(url, depth, fetcher, cache, done)
	done.Wait()
}

/*
	Other solutions/variants
		* each goroutine with its own WaitGroup => no arguments needed
		https://gist.github.com/danimal141/09ed828ce4d676faa6fa9f19aeea2867
*/
func main() {
	// Crawl_solution1("https://golang.org/", 4, fetcher)

	// Crawl_solution3("https://golang.org/", 4, fetcher)
	// Crawl_solution2("https://golang.org/", 4, fetcher)
	Crawl4("https://golang.org/", 4, fetcher)
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
