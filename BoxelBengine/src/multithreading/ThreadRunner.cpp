#include <iostream>
#include <thread>
#include <chrono>
#include <ratio>

#include "ThreadRunner.h"

ThreadRunner::ThreadRunner() {
  state = ThreadRunnerState::WAITING;
}

ThreadRunner::~ThreadRunner() {
  //delete th;
}

//int default_thread(std::atomic<ThreadRunnerState>& my_state) {
int default_thread() {
  ThreadRunnerState my_state = ThreadRunnerState::STOPPED;
  while(my_state == ThreadRunnerState::RUNNING || my_state == ThreadRunnerState::PAUSED) {
    while(my_state == ThreadRunnerState::RUNNING) {
      std::this_thread::sleep_for(std::chrono::duration<float,std::milli>(100));
    }
    std::cout << "default thread paused" << std::endl;
    std::this_thread::sleep_for(std::chrono::duration<float,std::milli>(1000));
  }
  my_state = ThreadRunnerState::STOPPED;
  return 0;
}


//returns int error code
int ThreadRunner::execute() {
  std::cout << "calling non-overloaded thread execution" << std::endl;
  //th = std::thread(default_thread,state);
  th = std::thread(default_thread);
  return 0;
}

ThreadRunnerState ThreadRunner::start() {
  if (state != ThreadRunnerState::WAITING)
    return state;
  state = ThreadRunnerState::RUNNING;
  execute();
  return state;
}

ThreadRunnerState ThreadRunner::pause() {
  if (state != ThreadRunnerState::RUNNING)
    return state;
  state = ThreadRunnerState::PAUSED;
  return state;
}

ThreadRunnerState ThreadRunner::resume() {
  if (state != ThreadRunnerState::PAUSED)
    return state;
  state = ThreadRunnerState::RUNNING;
  return state;
}

ThreadRunnerState ThreadRunner::stop() {
  if (!(state == ThreadRunnerState::RUNNING || state == ThreadRunnerState::PAUSED))
    return state;
  state = ThreadRunnerState::STOPPING;
  return state;
}

ThreadRunnerState ThreadRunner::join() {
  th.join();
  state = ThreadRunnerState::STOPPED;
  return state;
}

ThreadRunnerState ThreadRunner::get_state() {
  return state;
}
