# cpp-timeout
A timeout class for c++

## Usage



```
#include <iostream>
#include <chrono>
#include <thread>
#include "Timer.h"

int main() {
    bool running = true;
    
    Timer t1;
    t1.setTimeout([&]() {
        // triggered after 2000 milliseconds
        std::cout << "Executed timeout handler!";
        running = false;
    }, 2000);

    int frameTime = 16;
    while (running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(frameTime));
        t1.update(frameTime);
    }
    std::cout << "Bye!";
}
```
