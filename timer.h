#pragma once

#include <chrono>

enum class TimerState {
    kRunning,
    kPaused,
};

class Timer {
  public:
    // Constructs timer with the given initial state
    Timer(TimerState initial_state);

    // Resets timer and sets state (running if unspecified)
    void Reset(TimerState new_state = TimerState::kRunning);

    // Places timer into the paused state
    void Pause();

    // Places timer into the running state without resetting the total duration
    void Resume();

    double GetSeconds();
    double GetMilliseconds();

  private:
    using high_res_clock = std::chrono::high_resolution_clock;

    double _prev_duration;
    TimerState _state;
    high_res_clock::time_point _start_time_point;
    high_res_clock::time_point _end_time_point;

    // Returns the amount of time in seconds from start to end
    double ComputeDuration(high_res_clock::time_point start, high_res_clock::time_point end);
};
