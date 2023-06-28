#include "timer.h";

Timer::Timer() {
  startTime = std::chrono::high_resolution_clock::now();
}

void Timer::stop() {
  auto endTime = std::chrono::high_resolution_clock::now();
  auto start =
      std::chrono::time_point_cast<std::chrono::microseconds>(startTime)
          .time_since_epoch()
          .count();
  auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTime)
                 .time_since_epoch()
                 .count();
  auto duration = end - start;
  double ms = duration * 0.001;
}

Timer::~Timer() {
  stop();
}