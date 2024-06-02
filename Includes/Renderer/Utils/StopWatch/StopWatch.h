//
// Created by wpsimon09 on 02/06/24.
//

#ifndef PABLO_RENDERER_STOPWATCH_H
#define PABLO_RENDERER_STOPWATCH_H

#include "chrono"
using namespace std::chrono;

class StopWatch {
private:
    inline static time_point<steady_clock> start;
    inline static time_point<steady_clock> end;
    inline static double elapsed;
public:
    static void Start() {start = std::chrono::steady_clock::now();}

    static void End() {end = std::chrono::steady_clock::now(); elapsed = (end-start).count();}

    static double GetTimeInSec() {return elapsed;}



};


#endif //PABLO_RENDERER_STOPWATCH_H
