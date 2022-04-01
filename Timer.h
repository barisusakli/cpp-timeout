#pragma once

#include <vector>

class Timer {
    struct Timeout {
        Timeout(std::function<void()> _fn, int _timeleft) :
            fn(_fn), timeleft(_timeleft) { }
        std::function<void()> fn;
        int timeleft;       
    };
    std::vector<Timeout> _timeouts;
public:
    // call once per frame with time passed
    void update(float frameTime) {
        auto size = _timeouts.size();
        if (!size) return;
        for (int i = size - 1; i >= 0; i--) {
            auto& timeout = _timeouts[i];
            timeout.timeleft -= frameTime;
            if (timeout.timeleft <= 0) {
                timeout.fn();
                _timeouts.pop_back();
            } 
        }
    }

    void setTimeout(std::function<void()> function, int delay) {
        _timeouts.emplace_back(function, delay);
        // sort so the timeouts that have the least amount of time left are at the end
        std::sort(_timeouts.begin(), _timeouts.end(), [](const Timeout& t1, const Timeout& t2) {
            return t1.timeleft > t2.timeleft;
        });
    }    
};
