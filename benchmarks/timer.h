#include <chrono>

class Timer {
  // Reference: https://www.youtube.com/watch?v=YG4jexlSAjc&ab_channel=TheCherno
 private:
  std::chrono::time_point<std::chrono::high_resolution_clock> startTime;

 public:
  Timer();
  void start();
  void stop();
  ~Timer();
};