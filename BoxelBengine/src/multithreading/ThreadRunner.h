#pragma once

#include <atomic>
#include <thread>

enum class ThreadRunnerState {
  WAITING,
  RUNNING,
  PAUSED,
  STOPPING,
  STOPPED,
};

class ThreadRunner {
public:
  ThreadRunner();
  ~ThreadRunner();

  //executes state transitions and does some bookkeeping
  ThreadRunnerState start();
  ThreadRunnerState pause();
  ThreadRunnerState resume();
  ThreadRunnerState stop();
  ThreadRunnerState join();
  
  ThreadRunnerState get_state();

private:
  //to be overloaded, actually executes specific thread code
  int execute();
  //state is shared between ThreadRunner object and th
  std::atomic<ThreadRunnerState> state;
  std::thread th;
};
