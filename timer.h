//
//
//

#ifndef ICC_JUNK_TIMER_H
#define ICC_JUNK_TIMER_H

#include <chrono>

class Timer {
    using the_clock = std::chrono::steady_clock;
    static std::chrono::time_point<the_clock> now () {
        return the_clock::now();
    }
    
    std::chrono::time_point<the_clock> _start; // = chrono::high_resolution_clock::now();
    std::chrono::time_point<the_clock> _stop;   // = chrono::high_resolution_clock::now();

public:
    void start() {
        _start = now();
    }

    void stop() {
        _stop = now();
    }
    
    /// returns elapsed time in seconds
    double elapsed() const {
        return (double)std::chrono::duration_cast<std::chrono::milliseconds>(_stop - _start).count() / 1000.;
    }
};

// Local Variables:
// mode: c++
// c-basic-offset: 4
// tab-width: 4
// indent-tabs-mode: nil
// End:

#endif
