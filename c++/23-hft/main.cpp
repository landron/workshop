/*
1. A Lock-Free SPSC Queue: Implement a ring buffer using std::atomic and test it
for "jitter" (variance in latency). SPSC = Single Producer Single Consumer, a
common pattern in HFT for passing data between threads without locks.
2. A Lock-Free MPMC Queue: Implement a multi-producer multi-consumer queue using
std::atomic and test it for "jitter". MPMC = Multiple Producers Multiple
Consumers, a more complex pattern that allows multiple threads to produce and
    consume data concurrently.
*/
#include <print>

#include "spsc.h"

int main() {
    std::println("Hello High-frequency trading!");

    SPSCQueue<int, 1024> queue;
}
