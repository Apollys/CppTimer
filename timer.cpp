#include "timer.h"

Timer::Timer(TimerState initial_state)
    : _prev_duration(0.), _state(initial_state), _start_time_point(high_res_clock::now()) {}

void Timer::Reset(TimerState new_state) {
    _prev_duration = 0.;
    _state = new_state;
    _start_time_point = high_res_clock::now();
}

void Timer::Pause() {
    if (_state == TimerState::kRunning) {
        _end_time_point = high_res_clock::now();
        _prev_duration += ComputeDuration(_start_time_point, _end_time_point);
        _state = TimerState::kPaused;
    }
}

void Timer::Resume() {
    if (_state == TimerState::kPaused) {
        _state = TimerState::kRunning;
        _start_time_point = high_res_clock::now();
    }
}

double Timer::GetSeconds() {
    if (_state == TimerState::kRunning) {
        return _prev_duration + ComputeDuration(_start_time_point, high_res_clock::now());
    }
    return _prev_duration;
}

double Timer::GetMilliseconds() {
    return GetSeconds() * 1000.0;
}

double Timer::ComputeDuration(high_res_clock::time_point start, high_res_clock::time_point end) {
    using DurationType = std::chrono::duration<double>;
    DurationType total_duration = std::chrono::duration_cast<DurationType>(end - start);
    return total_duration.count();
}
